#include "dice.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

const int MAX_VALUE = 12;

DieT::DieT(void) {
    state = rand() % MAX_VALUE;
    return;
}

StateT DieT::State(void) {
    switch (state) {
       case 0: return Cthulhu;
       case 1: return Eye;
       case 2: return ElderSign;
       case 3:
       case 4:
       case 5:
       case 6: return Tentacle;
       default: return YellowSign;
    }
}

void DieT::Roll(void) {
    state = rand() % MAX_VALUE;

    return;
}

string StateTToString(StateT t){
     switch (t) {
         case YellowSign: return "Yellow Sign";
	 case Tentacle:   return "Tentacle";
	 case ElderSign:  return "Elder Sign";
	 case Cthulhu:    return "Cthulhu";
	 case Eye:        return "Eye";
     }
}

ostream& operator<<( ostream& s, StateT& t ){
     cout << StateTToString(t);
     return s;
}

StateT RandomSidePick() {
     return StateT(rand()%(STATES-1));
}

