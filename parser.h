#ifndef _PARSER_H
#define _PARSER_H

#include <map>
#include <vector>
#include <fstream>
#include "lexer.h"


class Parser //! This is really important class. It checks grammatic and creates automation from it. I use here 3 additional to lexer symbols: -1 = eps with high priority; 258 = eps with no priority; 259 = eps with low priority.
{
    const std::vector <Lex> input = {}; //! Vector of lexemes
    int curlex = 0; //! Current lexeme
    std::map <int, std::map<int, std::vector<int>>> output = {}; //! output automation <CUR, sym, NEXT>
    int state = 0; //! Current state for output automation.
    //int tmpstate = -1; //! Saved state for realization of '?'.
    //vector <int> flag = {}; //! Flag for '*' to consider priorities.
    int finstate = -1; //!Final state (further required)
    //vector <int> itstack = {}; //! Iteration stack.
    //vector <int> orstack = {}; //! Or stack.
    int S(); //! First state (S) (term symbol)
    int E(); //! State E for |
    int T(); //! State T for &
    int F(); //! State F for ? and * and *?
    int P(); //! State P for symbols and dot.
public:
    Parser(const std::vector <Lex> &i) : input(i), state(0) {}; //!
    std::map <int, std::map<int, std::vector<int>>> & parse();
    int getfinstate() const {return finstate;}
};

#endif // _PARSER_H
