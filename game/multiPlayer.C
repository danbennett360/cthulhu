#include <iostream>
#include "dice.h"
#include "player.h"
#include "GameLogic.h"
#include <cstdlib>
#include <string.h>

#include <vector>
#include "cliUtils.h"
#include "stats.h"

using namespace std;

const string PROGRAM_VERSION = "1.5";

const int MAX_TOKENS = 18;              // game defined.
const int MAX_PLAYERS = MAX_TOKENS / 3; // game defined.

bool VERBOSE = false;

void CreatePlayers(PlayerV & players, int actualPlayers, vector<int> is, vector<int> vs);
void PrintPlayers(PlayerV & players, int cth);
void ResetGame(PlayerV & players, int &  cthulhuTokens);

int PlayAGame(PlayerV & players, int & cthulhuTokens, DieT & die);

int main(int argc, char * argv[]) {
    PlayerV players;
    vector<int> iStrat, vStrat;
    vector<int> wins;
    int cthulhuWins = 0;
    int totalTurns = 0;
    int actualPlayers = 3;
    int i;
    int games;
    int turns;
    int num;

    for (i=0;i<MAX_PLAYERS;i++) {
       iStrat.push_back(RANDOM);
       vStrat.push_back(RANDOM);
       wins.push_back(0);
    }

    i = 1;
    while (i < argc ) {
       if (!strcmp(argv[i],"--eye")) {
           i++;
	   if (i+1 < argc) {
	       num =  atoi(argv[i])-1;
	       i++;
	       iStrat[num] = GetStrat(argv[i]);
	       i++;
	   } else {
	       cout << " --eye requires two parameters [num] and [D,P,F, R]"
	            << endl;
	   }
       } else if (!strcmp(argv[i],"--victim")) {
           i++;
       } else if (!strcmp(argv[i],"--players")) {
           i++;
	   if (i < argc) {
	       int num;
	       num  = atoi(argv[i]);
	       i++;

	       if (num >= 2 and num <=  MAX_PLAYERS) {
	          actualPlayers = num;
	       }
	   } else {
	       cout << " --players requirs an int argument" << endl;
	   }
       } else if (!strcmp(argv[i],"--verbose")) {
           i++;
           VERBOSE = true;
       } else if (!strcmp(argv[i],"--games")) {
           i++;
	   if (i < argc) {
	       games = atoi(argv[i]) ;
	       i++;
	   } else {
	       cout << "--games requires an integer argument" << endl;
	   }
       } else {
           cout << "Can't deal with arg "
	        << i << " which is " << argv[i] << endl;
           i++;
       }

    }

    int cthulhuTokens;
    DieT die;

    // hit the random number generator
    srand(time(NULL));

    // create players
    CreatePlayers(players, actualPlayers, iStrat, vStrat);

    for(i=0;i<games;i++) {
        ResetGame(players, cthulhuTokens);
        turns = PlayAGame(players, cthulhuTokens, die);

	AccumulateWins(players, wins, cthulhuWins);
        if (VERBOSE) {
	    cout << "-----------------------------------------------------";
	    cout << endl << endl;
	}

	totalTurns += turns;
	//cout <<  totalTurns << endl;
    }

    if (games > 1) {
        PrintStats(players, wins, cthulhuWins, games, totalTurns);
    }
          
    return 0;
}


int PlayAGame(PlayerV & players, int & cthulhuTokens, DieT & die){
     int numberSane;
     int caster = 0;
     int turn = 0;

     numberSane = CountSane(players);
     // while there are sane players.
     while (numberSane > 1) {
	 turn ++;
         if (VERBOSE) {
             cout << "A new turn, the caster is: " << players[caster] << endl;
	 }
         TakeATurn(players,cthulhuTokens, caster, die);
	 caster = (caster+1) % players.size();
         numberSane = CountSane(players);
	 if (VERBOSE) {
	     cout << "End of turn " << turn << " Sane Count " 
	          << numberSane << endl;
	     PrintPlayers(players, cthulhuTokens);
	     cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	     cout << endl;
	 }
     }

     if (VERBOSE) {
         cout << endl << endl;
         cout << "The game was " << turn << " turns long" << endl;
         cout << endl;
     }

     return turn;
}

void ResetGame(PlayerV & players, int &  cthulhuTokens){
    int i;

    cthulhuTokens = 0;
    for(i=0;i<players.size();i++) {
        players[i].Reset();
    }
    return;
}

void CreatePlayers(PlayerV & players, int actualPlayers, vector<int> is, vector<int> vs){
    int i;

    for(i=0;i<actualPlayers;i++) {

        PlayerT a(is[i], vs[i]);
	players.push_back(a);
    }

    return;
}

void PrintPlayers(PlayerV & players, int cth) {
    int i;

    for(i=0;i<players.size(); i++) {
         cout << players[i] << "[" << players[i].EyeStrategy() << ", " 
	      << players[i].VictimStrategy() << "]" << endl;
    }
    cout << "Cthulhu " << cth << endl;

    return;
}
