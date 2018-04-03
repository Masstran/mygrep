#include "parser.h"

int Parser::S()
{
    if (!E())
    {
        return 0;
    }
    if (input[curlex++].gettype() != LEX_END)
    {
        return 0;
    }
    finstate = state;
    return 1;
}

int Parser::E()
{
    int curstate = state;
    std::vector <int> states = {};
    do
    {
        if (curstate != state)
        {
            output[curstate][258].push_back(state);
        }
        if (!T())
        {
            return 0;
        }
        states.push_back(state);
        state++;
    } while(input[curlex++].gettype() == LEX_OR);
    for (auto vp = states.begin(); vp < states.end(); vp++)
    {
        output[*vp][258].push_back(state);
    }
    curlex--;
    return 1;
}

int Parser::T()
{
    do
    {
        if (!F())
        {
            return 0;
        }
    } while(input[curlex++].gettype() == LEX_CON);
    curlex--;
    return 1;
}

int Parser::F()
{
    int curstate = state;
    if (!P())
    {
        return 0;
    }
    type_of_lex lextype = input[curlex++].gettype();
    if (lextype == LEX_1IT)
    {
        output[curstate][258].push_back(state);
        return 1;
    }
    if (lextype == LEX_GIT)
    {
        output[curstate][259].push_back(state+1);
        output[state][-1].push_back(curstate);
        output[state][258].push_back(state+1);
        state++;
        return 1;
    }
    if (lextype == LEX_LIT)
    {
        output[curstate][-1].push_back(state+1);
        output[state][259].push_back(curstate);
        output[state][258].push_back(state+1);
        state++;
        return 1;
    }
    curlex--;
    return 1;
}

int Parser::P()
{
    type_of_lex lextype = input[curlex++].gettype();
    if (lextype == LEX_SYM)
    {
        auto vp = output[state][input[curlex - 1].getinfo()].begin();
        output[state][input[curlex - 1].getinfo()].insert(vp, state + 1);
        state++;
        return 1;
    }
    if (lextype == LEX_DOT)
    {
        auto vp = output[state][257].begin();
        output[state][257].insert(vp, state + 1);
        state++;
        return 1;
    }
    if (lextype == LEX_OPE)
    {
        if (!E())
        {
            return 0;
        }
        if (input[curlex++].gettype() != LEX_CLO)
        {
            return 0;
        }
        return 1;
    }
    return 0;
}

std::map <int, std::map<int, std::vector<int>>> & Parser::parse()
{
    if (S())
    {
        return output;
    }
    else
    {
        throw std::invalid_argument("Bad grammatic!\n");
    }
}
