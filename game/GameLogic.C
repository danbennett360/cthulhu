#include "GameLogic.h"

using namespace std;
extern bool VERBOSE;

void CthulhuAction(PlayerV & players, int & cth) {
            int i;

	    for (i=0;i<players.size();i++) {
	        if (players[i].IsSane()) {
		    cth++;
		    players[i].GiveToken();
		}
	    }
	    if(VERBOSE) 
	    cout << "\tEveryone loses, except Cthulhu" << endl;
	    return;
}

void TenticleAction(PlayerT & caster, PlayerT & victim, int & cth) {

	    if (victim.Sanity() > 0) {
	        victim.GiveToken();
		if (caster.IsSane() ) {
		   caster.GetToken();
		   if(VERBOSE) 
		   cout <<"\tThe victim loses a token to the caster " << endl;
		} else {
		   cth++;
		   if(VERBOSE) 
		   cout <<"\tThe caster is insane," 
		        << " the victim loses a token to Cathuhlu" << endl;
		}
	    } else {
	        if(VERBOSE) 
	        cout << "\tThe victim is insane, so no action" << endl;
	    }
	    return;
}


void CasterAction(PlayerV & players, int caster, int victim, DieT & die, int &  cth){
    switch(die.State()) {
        case YellowSign: 
	    if (players[victim].Sanity() > 0) {
	        players[victim].GiveToken();
	        cth++;
		if(VERBOSE)
	        cout << "\tThe victim loses a token to Cthulhu" << endl;
	    } else {
	        if(VERBOSE)
	        cout << "\tThe victim is insane, so no action" << endl;
	    }
	    break;
	case Tentacle: 
	    TenticleAction(players[caster], players[victim], cth);
	    break;
	case ElderSign: 
	    if (cth > 0) {
	       cth--;
	       players[caster].GetToken();
	       if (VERBOSE)
	       cout << "\tThe caster gets at token from Cthuhlu" << endl;
	    } else {
	       if (VERBOSE) 
	          cout << "\tCthuhlu is out of tokens, no action" << endl;
	    }
	    break;
	case Cthulhu: 
            CthulhuAction(players,cth);
	    break;
	case Eye:
	    StateT newValue;
	    newValue = players[caster].DecideResult(ATTACKER, players[victim].Sanity(), cth);
	    die.Change(newValue);
	    if (VERBOSE)
	    cout << "\tThe caster selects " 
	         << StateTToString(die.State()) << endl;
            CasterAction(players,caster, victim, die, cth);
	    break;
    }
    return;
}

void VictimAction(PlayerV & players, int caster, int victim, DieT & die,  int & cth){
    switch(die.State()) {
        case YellowSign: 
	    if (players[caster].Sanity() > 0) {
	        players[caster].GiveToken();
	        cth++;
		if (VERBOSE)
	        cout << "\tThe caster loses a token to Cthulhu" << endl;
	    } else {
	        if (VERBOSE)
	        cout << "\tThe caster is insane, so no action" << endl;
	    }
	    break;
	case Tentacle: 
	    TenticleAction(players[caster], players[victim], cth);
	    break;
	case ElderSign: 
	    if (cth > 0) {
	       cth--;
	       players[victim].GetToken();
	       if(VERBOSE)
	       cout << "\tThe victim gets at token from Cthuhlu" << endl;
	    } else {
	       if (VERBOSE) 
	          cout << "\tCthuhlu is out of tokens, no action" << endl;
	    }
	    break;
	case Cthulhu: 
            CthulhuAction(players, cth);
	    break;
	case Eye:
	    die.Change(players[victim].DecideResult(DEFENDER, players[caster].Sanity(), cth));
	    if(VERBOSE)
	    cout << "\tThe victim selects " 
	         << StateTToString(die.State()) << endl;
            VictimAction(players,caster, victim, die, cth);
	    break;
    }
    return;
}

bool TakeTurn(PlayerV & players, int caster, int victim,  DieT & die, int & cthuhlu){
   if (not players[victim].IsSane() ) {
      return false;
   }

   // caster attacks
   if(VERBOSE) {
       cout << "The Caster attacks: " << endl;
       cout << "\tCaster: " << players[caster] << endl;
       cout << "\tVictim: " << players[victim] << endl;
   }

   die.Roll();

   if (VERBOSE)  {
       cout << "\tThe caster rolls a " << StateTToString(die.State()) << endl;
   }

   CasterAction(players,caster, victim, die, cthuhlu);

   if (VERBOSE)  {
       cout << endl;
   }

   // victim counterattacks
  
   if(VERBOSE) {
       cout << "The Victim counter attacks: " << endl; 
       cout << "\tVictim: " << players[victim] << endl;
       cout << "\tCaster: " << players[caster] << endl;
   }

   die.Roll();

   if (VERBOSE) {
        cout << "\tThe victim rolls a " << StateTToString(die.State()) << endl;
   }

   VictimAction(players,caster, victim, die, cthuhlu);

   if (VERBOSE) {
       cout << endl;
   }
   
   return true;
}

int CountSane (PlayerV & players) {
    int i;
    int count = 0;

    for (i=0;i<players.size(); i++) {
        if (players[i].IsSane()) {
           count ++;
        }
    }

    return count;
}

int FindWinner(PlayerV & players) {
    int i;
    int winner = -1;
    int winnerCount = 0;

    for (i=0;i<players.size(); i++) {
        if (players[i].IsSane()) {
	    winnerCount ++;
	    winner = i;
        }
    }

    if (winnerCount != 1) {
        cerr << " There is an incorrect number of winners: " << winnerCount << endl;
	winner = -1;
    }

    return winner;
}


void TakeATurn(PlayerV & players,int & cthulhu, int caster, DieT & die){

    int victim;

    // attacker select victim
    victim = players[caster].SelectVictim(players, cthulhu);

    //cout << "Caster: " << caster << " Victim: " << victim << endl;

    if (victim < 0) {
       cerr << " Bad victim " << endl;
       return;
    }
    if (VERBOSE) {
        cout << "The victim is " << players[victim] << endl;
    }

    // then take a turn
    TakeTurn(players,caster, victim, die, cthulhu);

    return;
}
