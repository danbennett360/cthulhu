#include <iostream>

#include <cstdlib>
#include <ctime>

#include "dice.h"

using namespace std;
const int TRIALS = 1000000;

int main() {

    int i;
    DieT die;
    StateT j;
    int results[STATES];

    for(j=YellowSign; j <= Eye; j= StateT(j + 1)) {
       results[j] = 0;
    }

    srand(time(NULL));

    for(i=0;i<TRIALS;i++) {
       die.Roll();

       results[die.State()]++;
    }

    for(j=YellowSign; j <= Eye; j= StateT(j + 1)) {
       cout << StateTToString(j) << "   " << int(float(results[j])/TRIALS*12+.5) << endl;
    }

    return 0;
}
