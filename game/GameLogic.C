#include "GameLogic.h"

using namespace std;
extern bool VERBOSE;

void CthulhuAction(PlayerT & caster, PlayerT & victim, int & cth) {
	    if (caster.Sanity() > 0) {
	        caster.GiveToken();
	        cth++;
            }
	    if (victim.Sanity() > 0) {
	        victim.GiveToken();
	        cth++;
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


void CasterAction(PlayerT & caster, PlayerT & victim, DieT & die, int &  cth){
    switch(die.State()) {
        case YellowSign: 
	    if (victim.Sanity() > 0) {
	        victim.GiveToken();
	        cth++;
		if(VERBOSE)
	        cout << "\tThe victim loses a token to Cthulhu" << endl;
	    } else {
	        if(VERBOSE)
	        cout << "\tThe victim is insane, so no action" << endl;
	    }
	    break;
	case Tentacle: 
	    TenticleAction(caster, victim, cth);
	    break;
	case ElderSign: 
	    if (cth > 0) {
	       cth--;
	       caster.GetToken();
	       if (VERBOSE)
	       cout << "\tThe caster gets at token from Cthuhlu" << endl;
	    } else {
	       if (VERBOSE) 
	          cout << "\tCthuhlu is out of tokens, no action" << endl;
	    }
	    break;
	case Cthulhu: 
            CthulhuAction(caster,victim, cth);
	    break;
	case Eye:
	    StateT newValue;
	    newValue = caster.DecideResult(ATTACKER, victim.Sanity(), cth);
	    die.Change(newValue);
	    if (VERBOSE)
	    cout << "\tThe caster selects " 
	         << StateTToString(die.State()) << endl;
            CasterAction(caster, victim, die, cth);
	    break;
    }
    return;
}

void VictimAction(PlayerT & caster, PlayerT & victim, DieT & die,  int & cth){
    switch(die.State()) {
        case YellowSign: 
	    if (caster.Sanity() > 0) {
	        caster.GiveToken();
	        cth++;
		if (VERBOSE)
	        cout << "\tThe caster loses a token to Cthulhu" << endl;
	    } else {
	        if (VERBOSE)
	        cout << "\tThe caster is insane, so no action" << endl;
	    }
	    break;
	case Tentacle: 
	    TenticleAction(caster, victim, cth);
	    break;
	case ElderSign: 
	    if (cth > 0) {
	       cth--;
	       victim.GetToken();
	       if(VERBOSE)
	       cout << "\tThe victim gets at token from Cthuhlu" << endl;
	    } else {
	       if (VERBOSE) 
	          cout << "\tCthuhlu is out of tokens, no action" << endl;
	    }
	    break;
	case Cthulhu: 
            CthulhuAction(caster,victim, cth);
	    break;
	case Eye:
	    die.Change(victim.DecideResult(DEFENDER, caster.Sanity(), cth));
	    if(VERBOSE)
	    cout << "\tThe victim selects " 
	         << StateTToString(die.State()) << endl;
            VictimAction(caster, victim, die, cth);
	    break;
    }
    return;
}

bool TakeTurn(PlayerT  & caster, PlayerT & victim,  DieT & die, int & cthuhlu){
   if (not victim.IsSane() ) {
      return false;
   }

   // caster attacks
   if(VERBOSE) {
       cout << "The Caster attacks: " << endl;
       cout << "\tCaster: " << caster << endl;
       cout << "\tVictim: " << victim << endl;
   }
   die.Roll();
   if (VERBOSE) 
   cout << "\tThe caster rolls a " << StateTToString(die.State()) << endl;
   CasterAction(caster, victim, die, cthuhlu);
   if (VERBOSE) 
   cout << endl;


   // victim counterattacks
  
   if(VERBOSE) {
   cout << "The Victim counter attacks: " << endl; 
   cout << "\tVictim: " << victim << endl;
   cout << "\tCaster: " << caster << endl;
   }
   die.Roll();
   if (VERBOSE)
   cout << "\tThe victim rolls a " << StateTToString(die.State()) << endl;
   VictimAction(caster, victim, die, cthuhlu);
   if (VERBOSE)
   cout << endl;
   
   return true;
}
