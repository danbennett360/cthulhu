#include "player.h"

int PlayerT::maxID = 1;

using namespace std;

       PlayerT::PlayerT(int strat1/*=RANDOM*/){
          // get my id
          id = maxID;
	  // and bump the global
	  maxID++;

	  sanity = START_SANITY;
	  isSane = true;
          eyeStrategy = strat1;

          return;
       }

void PlayerT::Reset() {
     isSane = true;
     sanity= START_SANITY;
     return;
}

bool   PlayerT::IsSane() {
      return sanity > 0;
}

int    PlayerT::ID() {
      return id;
}

int    PlayerT::Sanity(){
       return sanity;
}

void   PlayerT::GetToken() {
       sanity++;
       return;
}

void   PlayerT::GiveToken() {
       sanity --;
       if (sanity < 0) {
          sanity = 0;
       }
       return;
}

string PlayerT::EyeStrategy() {
     switch(eyeStrategy) {
         case DOUG:
	    return "Doug";
	 case RANDOM:
	 default:
	    return "Random";
     }
}

StateT PlayerT::DecideResult(int role, int opponentTokens, int cthulhuTokens) {
       StateT rv;

       switch (eyeStrategy) {
           case DOUG:
	       if (role == ATTACKER) {
	           rv = Tentacle;
	       } else {
	           if (opponentTokens == 1) {
		       rv = YellowSign;
		   } else if (cthulhuTokens > 0) {
		       rv = ElderSign;
		   } else {
		       rv = YellowSign;
		   }
	       }
	       break;
	   case RANDOM:
	   default:
	       rv = RandomSidePick();
	       break;
       }
       return rv;
}


ostream & operator << (ostream & s, PlayerT  & p) {
     s <<"ID: " << p.ID() << ",  ";
     s << "Sanity: " << p.Sanity() << ", ";
     if (p.IsSane()) {
        s << "(Sane)";
     } else {
        s << "(Insane)";
     }

     return s;
}
