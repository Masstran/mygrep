#ifndef _CHECKER_H
#define _CHECKER_H

#include <string>
#include <vector>
#include <map>
#include "parser.h"

class Checker
{
    std::map <int, std::map<int, std::vector<int>>> rules = {};
    const int search_flag = 0;
    int finstate = 0;
public:
    Checker(const char *s, int flag);
    int check(const std::string &s, int curstate = 0, int curpos = 0, int level = 0);
};


#endif // _CHECKER_H
