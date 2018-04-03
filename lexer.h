#ifndef _LEXER_H
#define _LEXER_H

#include <vector>
#include <string>
#include <stdexcept>

enum type_of_lex
{
    LEX_NULL,//! Default type.
    LEX_SYM, //! Just terminal symbol.
    LEX_DOT, //! '.'
    LEX_1IT, //! 1 iteration = '?'
    LEX_GIT, //! Greedy iteration = '*'
    LEX_LIT, //! Lazy iteration = '*?'
    LEX_OPE, //! '('
    LEX_CLO, //! ')'
    LEX_OR,  //! '|'
    LEX_CON, //! Concatenation.
    LEX_END, //! The end.
};

enum lex_states
{
    STL_NULL,//! Default state.
    STL_SPRK,//! If '*' symbol detected.
    STL_SLSH,//! If '\' symbol detected.
    STL_ERR, //! If any error occurred.
    STL_END, //! End state.
};

class Lex //! Lexeme with information about it.
{
    type_of_lex t_lex; //!Type of lexeme.
    int         i_lex; //!Info about this lexeme (used only for LEX_SYM with 0..256 - ASCII code + 257 - any symbol).
public:
    Lex (type_of_lex t = LEX_NULL, int i = 0) : t_lex(t), i_lex(i) {};
    type_of_lex gettype() const {return t_lex;}
    int getinfo() const {return i_lex;}
};

class buffer //! Smart string buffer. Will return symbol if needed and can peek to the next symbol.
{
    std::string buf;
    unsigned int cur;
public:
    buffer (const std::string& s = "") : buf(s), cur(0) {};
    char gc() {return buf[cur++];}
    char nextc() {return (cur > buf.size()) ? '\0' : buf[cur];}
};

class Lexer  //! Lexical Analyzer. Turns grammatic to vector of lexemes.
{
    int Cur_State = STL_NULL;//! Current state
    std::vector <Lex> lexs = {}; //! Lex vector, the goal of lexer.
    buffer buf = buffer(); //! Buffer with regular expression in it.
public:
    Lexer (const char *s)
    {
        lexs = {};
        buf = buffer(s);
    }
    std::vector <Lex> analyze ();
};

#endif // _LEXER_H
