#include <iostream>
#include <fstream>
#include "dice.h"
#include "player.h"
#include "GameLogic.h"
#include "stats.h"

#include "cliUtils.h"

#include <cstdlib>
#include <cmath>
#include <string.h>
#include <vector>

using namespace std;

int MAX_PLAYERS=2;

bool VERBOSE = false;
int ITERATIONS = 1000;

const string PROGRAM_VERSION = "1.5";

int PlayAGame(PlayerV &  players, int  & winner, DieT & die);

int main(int argc, char * argv[]) {
     // get a few players

     int p1Strat= RANDOM, p2Strat = RANDOM;
     int i;
     //bool doXMLSave = false;
     bool doRAWSave = false;
     //string XMLSaveFile;
     string RAWSaveFile = "SaveGame.raw";
     ofstream saveFile;
     StateVectorT rolls;

     i=1;
     while (i< argc) {
         if( !strcmp(argv[i],"--eye")) {
	     int num, strat;
	     ParseEyeArgs(argc, argv, i, num, strat);
	     if (num == 0) {
	         p1Strat = strat;
	     } else  if (num == 1) {
	         p2Strat = strat; 
	     }
	 } else if (!strcmp(argv[i],"--verbose")) {
             VERBOSE = true;
	     i++;
	 } else if (!strcmp(argv[i],"--games")) {
	     ITERATIONS = GetGamesArg(argc, argv, i);
	 /*} else if (!strcmp(argv[i],"--raw") ) {
	     if (argc >= i+1) {
	         doRAWSave = true;
		 i++;
		 RAWSaveFile = argv[i];
		 i++;
	     } else {
	         cout << "-raw requires a filename, none supplied" << endl;
		 i++;
	     }
	 */
	 } else {
	     cout << "Can't deal with arg " << i << " which is " << argv[i] << endl;
	     i++;
	 }
     }

     DieT die;
     PlayerV players;
     int cthulhuTokens;

     PlayerT a(p1Strat), b(p2Strat);
     players.push_back(a);
     players.push_back(b);

     int totalTurns = 0;

     vector<int> wins;
     int cthulhuWins = 0;

     for(int i =0;i<=MAX_PLAYERS; i++) {
         wins.push_back(0);
     }

     int turns;
     int winner;

     srand(time(NULL));

     if (doRAWSave) {
         saveFile.open(RAWSaveFile.c_str());
         saveFile << "Games: " << ITERATIONS << endl;
     }

     for(int k = 0; k < ITERATIONS; k++) {
         winner = 0;
         for(int i = 0; i < MAX_PLAYERS; i++) {
            players[i].Reset();
         }

         // the die will return the game state
         if (doRAWSave) {
             die.ClearHistory();
	     die.RecordHistory();
	 }

         turns =  PlayAGame(players, winner, die);

         // clean up the die.
         if (doRAWSave) {
	     die.StopRecordingHistory();
	     rolls = die.GetHistory();
	     die.ClearHistory();

	     // game:#, players
	     saveFile << "game:" << k;
	     saveFile <<"," << 2 << endl;

	     // turn:#, attackID, defendID, attackroll[:sub], defendroll[:sub]
	     int i = 0;
	     int simTurn = 1;
	     int cast = 1,vict = 2, tmp;
	     while (i < rolls.size() ) {
	         saveFile << "turn:" << simTurn << ",";
		 saveFile << cast << "," << vict << ",";

		 // output attach roll
		 saveFile << StateTToChar(rolls[i]);
		 // oh, if it was eye, print the sub.
		 if (rolls[i] == Eye) {
		    i++;
		    saveFile << ":" << StateTToChar(rolls[i]);
		 }
		 i++;
		 saveFile << ",";

		 saveFile << StateTToChar(rolls[i]);
		 if (rolls[i] == Eye) {
		    i++;
		    saveFile << ":" << StateTToChar(rolls[i]);
		 }
		 i++;

		 saveFile << endl;

		 tmp = cast;
		 cast = vict;
		 vict = tmp;
		 simTurn ++;
	     }
	 }

         AccumulateWins(players, wins, cthulhuWins);

	 totalTurns += turns;
	 //cout << totalTurns << endl;
	 if (VERBOSE) {
             cout << "_______________________________________________" << endl;
	     cout << endl;
	 }
     }
     if(ITERATIONS > 1) {
         PrintStats(players, wins, cthulhuWins, ITERATIONS, totalTurns);
     }

     if (doRAWSave) {
         saveFile.close();
     }

     return 0;
}

int PlayAGame(PlayerV & players, int  & winner, DieT & die) {
     int caster =0, 
         victim = 1;
     int turns = 0;
     int cthulhu = 0;

     int i,tmp;
     int saneCount = CountSane(players);

     if (VERBOSE) {
         for(i=0; i< MAX_PLAYERS;i++) {
             cout << players[i]  << ", " << players[i].EyeStrategy() << endl;
	 }

         cout << endl;
     }

     while (saneCount > 1) {
         turns ++;

         TakeATurn(players,cthulhu, caster, die);

	 saneCount = CountSane(players);

         if (VERBOSE) { 
	     cout << " End of turn " << turns << " saneCount = "
	      << saneCount << endl;
	     cout << endl << endl;
         }
	 caster = (caster+1) % players.size();
     }

     if (saneCount == 0) {
         if (VERBOSE) {
	     cout << "Cthulhu";
	 }
	 winner = MAX_PLAYERS;
     } else {
         int tmp;
	 winner = FindWinner(players);
	 if (VERBOSE) {
	    cout << "Player " << players[winner].ID();
	 }
     }
     if (VERBOSE)  {
         cout << " wins in " << turns << " turns." << endl;
     }

     return turns;
}
