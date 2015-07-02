#ifndef DICE_DOT_H
#define DICE_DOT_H

#include <iostream>
#include <string>
#include <vector>

const std::string DICE_VERSION = "1.0";

enum StateT {YellowSign, Tentacle, ElderSign, Cthulhu, Eye};
const int STATES = 5;

typedef std::vector<StateT> StateVectorT;
class DieT {
   public:
       DieT(); 
       StateT State();
       void Roll();
       void Change(StateT value);
       void ClearHistory(void);
       StateVectorT GetHistory();
       void RecordHistory();
       void StopRecordingHistory();
   private:
       bool keepHistory;
       StateT state;
       StateVectorT history;
};


// this is just a little misnamed
// To be used when a player rolls the Eye and needs to pick
// another side.  
// Will return one of the other sides at random.
StateT RandomSidePick();


std::string StateTToString(StateT t);
char StateTToChar(StateT t);
StateT CharToStateT(char c);

std::ostream& operator<<( std::ostream& s, StateT& t );
#endif
