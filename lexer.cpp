#include "lexer.h"

std::vector <Lex> Lexer::analyze()
{
    char c;
    do
    {
        switch(Cur_State)
        {
        case STL_NULL:
            {
                c = buf.gc();
                switch (c)
                {
                    case '\\': Cur_State = STL_SLSH;         break;
                    case '*' : Cur_State = STL_SPRK;         break;
                    case '\0': Cur_State = STL_END;          break;
                    case '?' : lexs.push_back(Lex(LEX_1IT)); break;
                    case '.' : lexs.push_back(Lex(LEX_DOT)); break;
                    case '(' : lexs.push_back(Lex(LEX_OPE)); break;
                    case ')' : lexs.push_back(Lex(LEX_CLO)); break;
                    case '|' : lexs.push_back(Lex(LEX_OR )); break;
                    default  : lexs.push_back(Lex(LEX_SYM, (c >= 0 ? c : 256 + c))); //! Russian language support.
                }
                //std::cout << buf.nextc() << std::endl;
                if ((c != '\\') && (c != '*'))
                {
                    if ( (buf.nextc() != '*') && (buf.nextc() != '\0') &&
                         (buf.nextc() != '?') && (buf.nextc() != '(') &&
                                                 (buf.nextc() != ')') && (buf.nextc() != '|'))
                    {
                        int counter = 0;
                        while (lexs[lexs.size() - 1].gettype() == LEX_OPE)
                        {
                            counter++;
                            lexs.pop_back();
                        }
                        if (lexs.size() && (lexs[lexs.size() - 1].gettype() != LEX_OR))
                        {
                            lexs.push_back(Lex(LEX_CON));
                        }
                        for (int i = 0; i < counter; i++)
                        {
                            lexs.push_back(Lex(LEX_OPE));
                        }
                    }
                }
                break;
            }
        case STL_SLSH:
            {
                c = buf.gc();
                switch (c)
                {
                case '*' : case '|' :
                case '(' : case ')' :
                case '+' : case '?' :
                case '{' : case '}' :
                case '[' : case ']' :
                case '-' : case '\\':
                    {
                        lexs.push_back(Lex(LEX_SYM, c));
                        Cur_State = STL_NULL;
                        break;
                    }
                default: Cur_State = STL_ERR;
                }
                if ( (buf.nextc() != '*') && (buf.nextc() != '\0') &&
                         (buf.nextc() != '?') &&  (buf.nextc() != '(') &&
                                                 (buf.nextc() != ')') && (buf.nextc() != '|'))
                    {
                        int counter = 0;
                        while (lexs[lexs.size() - 1].gettype() == LEX_OPE)
                        {
                            counter++;
                            lexs.pop_back();
                        }
                        if (lexs.size())
                        {
                            lexs.push_back(Lex(LEX_CON));
                        }
                        for (int i = 0; i < counter; i++)
                        {
                            lexs.push_back(Lex(LEX_OPE));
                        }
                    }
                break;
            }
        case STL_SPRK:
            {
                if (buf.nextc() == '?')
                {
                    c = buf.gc();
                    lexs.push_back(Lex(LEX_LIT));
                }
                else
                {
                    lexs.push_back(Lex(LEX_GIT));
                }
                if ( (buf.nextc() != '*') && (buf.nextc() != '\0') &&
                         (buf.nextc() != '?') &&  (buf.nextc() != '(') &&
                                                 (buf.nextc() != ')') && (buf.nextc() != '|'))
                    {
                        int counter = 0;
                        while (lexs[lexs.size() - 1].gettype() == LEX_OPE)
                        {
                            counter++;
                            lexs.pop_back();
                        }
                        if (lexs.size())
                        {
                            lexs.push_back(Lex(LEX_CON));
                        }
                        for (int i = 0; i < counter; i++)
                        {
                            lexs.push_back(Lex(LEX_OPE));
                        }
                    }
                Cur_State = STL_NULL;
                break;
            }
        default: Cur_State = STL_ERR;
        }
    } while ((Cur_State != STL_END) && (Cur_State != STL_ERR));
    if (Cur_State == STL_ERR)
    {
        throw std::invalid_argument("Error occurred in Lexer!");
    }
    lexs.push_back(Lex(LEX_END));
    return lexs;
}
