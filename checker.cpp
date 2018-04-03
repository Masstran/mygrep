#include "checker.h"

Checker::Checker(const char *s, int flag) : search_flag(flag)
{
    Lexer l(s);
    Parser p(l.analyze());
    rules = p.parse();
    finstate = p.getfinstate();
}

int Checker::check(const std::string &s, int curstate, int curpos, int level)
{
    int inputsize = s.size();
    int retvalue;
    for (auto mp = rules[curstate].begin(); mp != rules[curstate].end(); mp++)
    {
        switch ((*mp).first)
        {
        case -1: case 258: case 259:
            {
                for (auto vp = (*mp).second.begin(); vp < (*mp).second.end(); vp++)
                {
                    retvalue = check(s, *vp, curpos, level + 1);
                    if (retvalue)
                    {
                        return retvalue;
                    }
                }
                break;
            }
        case 257:
            {
                if (curpos == inputsize)
                {
                    break;
                }
                for (auto vp = (*mp).second.begin(); vp < (*mp).second.end(); vp++)
                {
                    retvalue = check(s, *vp, curpos + 1, level + 1);
                    if (retvalue)
                    {
                        return retvalue;
                    }
                }
                break;
            }
        default:
            {
                if ((curpos == inputsize) || ((*mp).first != s[curpos]))
                {
                    break;
                }
                for (auto vp = (*mp).second.begin(); vp < (*mp).second.end(); vp++)
                {
                    retvalue = check(s, *vp, curpos + 1, level + 1);
                    if (retvalue)
                    {
                        return retvalue;
                    }
                }
            }
        }
    }
    if (search_flag)
    {
        retvalue = (curstate == finstate) ? (curpos + 1) : 0;
    }
    else
    {
        retvalue = (curstate == finstate)&&(curpos == inputsize);
    }
    return retvalue;
}


