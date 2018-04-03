#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "checker.h"

using namespace std;

int main(int argc, char *argv[])
{
    if ((argc <= 1) || (argc > 3))
    {
        cout << "Sorry, argument amount error.\n";
        return 1;
    }
    int srch = (argc == 3);
    Checker c(argv[1], srch);
    string s;
    while (cin >> s)
    {
        int result = c.check(s);
        if (!result)
        {
            cout << "NO\n";
        }
        else
        {
            cout << "YES";
            if (srch)
            {
                cout << ": " << s.substr(0, result - 1);
            }
            cout << endl;
        }
    }
    return 0;
}
