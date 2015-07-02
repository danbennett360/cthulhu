#include <iostream>
#include <fstream>
#include "dice.h"
#include "player.h"
#include "GameLogic.h"

#include <cstdlib>
#include <cmath>
#include <string.h>

using namespace std;

int MAX_PLAYERS=2;

bool VERBOSE = false;
int ITERATIONS = 1000;

const string PROGRAM_VERSION = "1.0";

void PlayAGame(PlayerT players[], int & turns, int  & winner, DieT & die);

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
         if( !strcmp(argv[i],"--p1D")) {
	     p1Strat  = DOUG;
	     i++;
	 } else if (!strcmp(argv[i],"--p2D")) {
	     p2Strat  = DOUG;
	     i++;
	 } else if (!strcmp(argv[i],"--verbose")) {
             VERBOSE = true;
	     i++;
	 } else if (!strcmp(argv[i],"--games")) {
	     i++;
	     if (argc > i) {
	        ITERATIONS = atoi(argv[i]);
		i++;
		if (ITERATIONS < 1) {
		   ITERATIONS = 1;
		}
	     } else {
	         cout << "--games requires an additional argument"
		      << ", none supplied" << endl;
	     }
	 /*} else if (!strcmp(argv[i],"-xml") ) {
	     if (argc >= i+1) {
	         doXMLSave = true;
		 i++;
		 XMLSaveFile = argv[i];
		 i++;
	     } else {
	         cout << "-xml requires a filename, none supplied" << endl;
		 i++;
	     }
	 */
	 } else if (!strcmp(argv[i],"--raw") ) {
	     if (argc >= i+1) {
	         doRAWSave = true;
		 i++;
		 RAWSaveFile = argv[i];
		 i++;
	     } else {
	         cout << "-raw requires a filename, none supplied" << endl;
		 i++;
	     }
	 } else {
	     cout << "Can't deal with arg " << i << " which is " << argv[i] << endl;
	     i++;
	 }
     }

     DieT die;
     PlayerT players[MAX_PLAYERS] = {p1Strat, p2Strat};
     int totalTurns = 0;
     int wins[MAX_PLAYERS+1];

     for(int i =0;i<=MAX_PLAYERS; i++) {
         wins[i] = 0;
     }

     int turns;
     int winner;

     srand(time(NULL));

     if (doRAWSave) {
         saveFile.open(RAWSaveFile.c_str());
     }

     saveFile << "Games: " << ITERATIONS << endl;
     for(int k = 0; k < ITERATIONS; k++) {
         turns =0;
         winner = 0;
         for(int i = 0; i < MAX_PLAYERS; i++) {
            players[i].Reset();
         }

         // the die will return the game state
         if (doRAWSave) {
             die.ClearHistory();
	     die.RecordHistory();
	 }

         PlayAGame(players, turns, winner, die);

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


	 wins[winner] ++;
	 totalTurns += turns;
	 if (VERBOSE) {
             cout << "_______________________________________________" << endl;
	     cout << endl;
	 }
     }

     for(int i =0;i<=MAX_PLAYERS; i++) {
         cout << i ;
	    if (i < MAX_PLAYERS) {
	        cout << ": (" <<  players[i].EyeStrategy()  <<") ";
	    } else { 
	        cout << ": Cthulhu " ;
	    }
	    cout  << "won " << wins[i] << "/" << ITERATIONS  << " or \t"
	          << round(float(wins[i])/ITERATIONS * 100)
	          << "%" << endl;
     }
     cout << endl;
     cout << "The average game was " << float(totalTurns) / ITERATIONS 
          << " turns" << endl;

     if (doRAWSave) {
         saveFile.close();
     }

     return 0;
}

void PlayAGame(PlayerT players[], int & turns, int  & winner, DieT & die) {
     int current =0, 
         notCurrent = 1;

     int cthulhu = 0;

     int i,tmp;
     int saneCount = MAX_PLAYERS;

     for(i=0; i< MAX_PLAYERS;i++) {
         if (VERBOSE)
         cout << players[i]  << ", " << players[i].EyeStrategy() << endl;
     }
     if (VERBOSE)
     cout << endl;

     turns = 0;

     while (saneCount > 1) {
         turns ++;
         TakeTurn(players[current],players[notCurrent], die, cthulhu);

	 saneCount = 0;
	 for(i=0;i<2;i++) {
             if (VERBOSE)
	     cout << " Player " << i+1 << " " << players[i] << endl;
	     if (players[i].IsSane()) {
                saneCount++;
	     }
	 }
         if (VERBOSE) {
	 cout << " End of turn " << turns << " saneCount = "
	      << saneCount << endl;
	 cout << endl;
	 cout << endl;
         }

	 // swap players
	 tmp = current;
	 current = notCurrent;
	 notCurrent = tmp;
     }

     if (saneCount == 0) {
         if (VERBOSE) cout << "Cthulhu wins";
	 winner = MAX_PLAYERS;
     } else {
         if (players[0].IsSane()) {
	     if (VERBOSE) cout << "Player 1 wins" ;
	     winner = 0;
	 } else {
	     if (VERBOSE) cout << "Player 2 wins" ;
	     winner = 1;
	 }
     }
     if (VERBOSE)  {
         cout << " in " << turns << " turns." << endl;
     }

     return;
}
