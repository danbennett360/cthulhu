#include "cliUtils.h"

#include <string>

using namespace std;

int GetStrat(string s){
    if (s == "D" or s == "d") {
        return DOUG;
    }  else if (s == "F" or s == "f") {
        return FANATIC;
    }  else if (s == "P" or s == "p") {
        return PACIFIST;
    }  else if (s == "R" or s == "r") {
        return RANDOM;
    } else  {
        cout << "Unknown player strategy, Suppored D,F, Given " << s << endl;
        return RANDOM;
    }
}


