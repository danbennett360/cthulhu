#ifndef DICE_DOT_H
#define DICE_DOT_H

#include <iostream>
#include <string>

enum StateT {YellowSign, Tentacle, ElderSign, Cthulhu, Eye};
const int STATES = 5;

class DieT {
   public:
       DieT(); 
       StateT State();
       void Roll();
   private:
       int state;
};

std::string StateTToString(StateT t);

std::ostream& operator<<( std::ostream& s, StateT& t );
#endif
