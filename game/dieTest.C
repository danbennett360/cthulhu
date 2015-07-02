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

    cout << "Simulation of number of sides " << endl;
    for(j=YellowSign; j <= Eye; j= StateT(j + 1)) {
       cout << "\t" << StateTToString(j) << "   " 
            << int(float(results[j])/TRIALS*12+.5) << endl;
    }

    cout << endl;
    cout << " Quick History Test " << endl;

    die.RecordHistory();
    die.Roll();
    cout << "Just rolled " << StateTToString(die.State() ) << endl;
    die.Roll();
    cout << "Just rolled " << StateTToString(die.State() ) << endl;
    die.Change(Eye);
    cout << "Just rolled " << StateTToString(die.State() ) << endl;
    die.Roll();
    cout << "Just rolled " << StateTToString(die.State() ) << endl;


    StateVectorT s;
    s = die.GetHistory();
    cout << " The last four rolls should be :" << endl;
    for (i = 0; i < s.size(); i++) {
        cout << "\t" << StateTToString(s[i]) << endl; 
    }
    cout << endl;

    cout << "The next line should be blank " << endl;

    die.ClearHistory();
    s = die.GetHistory();
    for (i = 0; i < s.size(); i++) {
        cout << StateTToString(s[i]) << " "; 
    }
    cout << endl;

    return 0;
}
