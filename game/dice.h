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


// this is just a little misnamed
// To be used when a player rolls the Eye and needs to pick
// another side.  
// Will return one of the other sides at random.
StateT RandomSidePick();


std::string StateTToString(StateT t);

std::ostream& operator<<( std::ostream& s, StateT& t );
#endif
