#include "dice.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX_VALUE = 12;

DieT::DieT(void) {
    keepHistory = false;
    Roll();
    return;
}

StateT DieT::State(void) {
    return state;
}

void DieT::Roll(void) {
    int value;
    value = rand() % MAX_VALUE;
    switch (value) {
       case 0: state = Cthulhu; 
               break;
       case 1: state = Eye; 
               break;
       case 2: state = ElderSign; 
               break;
       case 3:
       case 4:
       case 5:
       case 6: state = Tentacle;
               break;
       default: state = YellowSign; 
               break;
    }

    if (keepHistory) {
        history.push_back(state);
    }

    return;
}

void DieT::Change(StateT value) {
    state = value;
    if (keepHistory) {
        history.push_back(state);
    }
    return;
}

void DieT::ClearHistory(void) {
    history.clear();
    return;
}


StateVectorT  DieT:: GetHistory(void) {
     return history;
}

void DieT::RecordHistory() {
    keepHistory = true;
    return;
}

void DieT::StopRecordingHistory() {
    keepHistory = false;
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

char StateTToChar(StateT t) {
     switch (t) {
         case YellowSign: return 'Y';
	 case Tentacle:   return 'T';
	 case ElderSign:  return 'E';
	 case Cthulhu:    return 'C';
	 case Eye:        return 'S';
     }
}

StateT CharToStateT(char c) {
    switch(c) {
       case 'Y': return YellowSign;
       case 'T': return Tentacle;
       case 'E': return ElderSign;
       case 'C': return Cthulhu;
       case 'S': return Eye;
       default:
          cout <<"ERROR ERROR ERROR Invalid character in CharToStateT" << endl;
	  return Eye;
    }
}


ostream& operator<<( ostream& s, StateT& t ){
     cout << StateTToString(t);
     return s;
}

StateT RandomSidePick() {
     return StateT(rand()%(STATES-1));
}


