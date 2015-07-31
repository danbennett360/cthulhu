#include "player.h"
#include <cstdlib>

int PlayerT::maxID = 1;

using namespace std;

       PlayerT::PlayerT(int strat1/*=RANDOM*/, int strat2 /* = RANDOM*/){
          // get my id
          id = maxID;
	  // and bump the global
	  maxID++;

	  sanity = START_SANITY;
	  isSane = true;
          eyeStrategy = strat1;
	  victimStrategy = strat2;

          return;
       }

void PlayerT::EyeStrategy(int strat) {
     eyeStrategy = strat;
     return;
}

void PlayerT::VictimStrategy(int strat) {
     victimStrategy = strat;
     return;
}

int PlayerT::SelectVictim(vector<PlayerT> players,  int cthulhuToken) {
    vector<int> targets;
    int i;

    // this is the random strategy
    // find all sane players that are not the caster
    for (i=0;i<players.size();i++) {
        if (players[i].ID() != id and players[i].IsSane()) {
	    targets.push_back(i);
	}
    }

    // and return one at random.
    if (targets.size() < 1) {
        cerr << "There are no valid victims " << endl;
	return -1;
    } else {
        return targets[rand() % targets.size()];
    }
    
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

string PlayerT::VictimStrategy() {
       return "Random";
}

string PlayerT::EyeStrategy() {
     switch(eyeStrategy) {
         case DOUG:
	    return "Doug    ";
	 case FANATIC:
	    return "Fanatic ";
	    break;
	 case PACIFIST:
	    return "Pacifist";
	    break;
	 case RANDOM:
	 default:
	    return "Random  ";
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
	   case FANATIC:
	       return Cthulhu;
	       break;
	   case PACIFIST:
	       return ElderSign;
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
