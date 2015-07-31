#include <iostream>
#include <fstream>
#include "dice.h"
#include "player.h"
#include "GameLogic.h"

#include <cstdlib>

bool VERBOSE = true;
// a demo program to replay a save file.

using namespace std;

int main(int argc, char * argv[]) {
   string fileName;
   ifstream inFile;
   string line;

   int gamesToPlay = 0;


   if (argc > 1) {
       fileName = argv[1];
   } else {
       cout << "Enter the save file name -> ";
       cin >> fileName;
   }

   cout << "Opening Save file " << fileName << endl;
   inFile.open(fileName.c_str());

   if (!inFile) {
       cout << "Failed to open " << fileName << endl;
       return -1;
   }

   getline(inFile,line);

   // first line Games: #
   // parse out the number of games;
   gamesToPlay = atoi(line.substr(6,line.size()).c_str());
   cout << "There are " << gamesToPlay << " games in the file " << endl;

   int game = 0;
   getline(inFile, line);
   while (game < gamesToPlay) {
       // get the game id line.
       int gameID, players;
       int tmp1, tmp2;
       string word;

       tmp1 = line.find(':');
       tmp2 = line.find(',');
       gameID = atoi(line.substr(tmp1+1, tmp2-tmp1).c_str());
       tmp1 = tmp2+1;
       tmp2 = line.find(',',tmp1);
       players = atoi(line.substr(tmp1, tmp2-tmp1).c_str());
       cout << "\tThis is game " << gameID << " and there are " 
            << players << " players." << endl;
      
      // now read the turns;
      bool gameOver = false;
      int casterID, victimID;
      int turn;
      StateT casterRoll, victimRoll;
      StateT casterChoice, victimChoice;

      vector<PlayerT> player;
      PlayerT a;
      player.push_back(a);
      player.push_back(a);

      DieT die;
      int cth = 0;

      // reset the players
      for(int i=0;i<2;i++) {
         player[i].Reset();
      }

cout << "Here " << endl;

      cth = 0;

      cout << "\t\tScore " << endl;
      cout << "\t\t  Player 1: " << player[0].Sanity() << endl ;
      cout << "\t\t  Player 2: " << player[1].Sanity() << endl ;
      cout << "\t\t  Cthulhu: " << cth << endl;


      while (!gameOver) {

          getline(inFile, line);
          tmp1 = line.find(':');
          word = line.substr(0,tmp1); 
	  if (word == "turn") {
	     // get the turn
	     tmp2 = line.find(',');
	     turn = atoi(line.substr(tmp1+1,tmp2-tmp1).c_str());
	     // get the caster id
	     tmp1 = tmp2+1;
	     tmp2 = line.find(',',tmp1);
	     casterID = atoi(line.substr(tmp1,tmp2-tmp1).c_str());
	     // get the victim id
	     tmp1 =  tmp2+1;
	     tmp2 = line.find(',',tmp1);
	     victimID = atoi(line.substr(tmp1,tmp2-tmp1).c_str());

	     // ok so now tmp2 will be the comma after the victim id
	     tmp1 = tmp2+1;
	     // so tmp1 is the first result.
	     casterRoll = CharToStateT(line[tmp1]);
	     tmp1++;
	     if (line[tmp1] == ':') {
	        // we got an eye
		tmp1++;
		casterChoice = CharToStateT(line[tmp1]);
		tmp1++;
	     }


	     tmp1++;

             // tmp1 will now be on the victim roll
	     victimRoll = CharToStateT(line[tmp1]);
	     tmp1++;
	     if (line[tmp1] == ':') {
	        // we got an eye
		tmp1++;
		victimChoice = CharToStateT(line[tmp1]);
		tmp1++;
	     }

             cout << endl;
	     cout << "\tTaking turn " << turn << endl;
	     cout << "\tCaster ID: " << casterID;
	     cout << ", Victim ID: " << victimID << endl;
	     cout << "\tCaster Roll: " << StateTToString(casterRoll) << endl;
	     if (Eye == casterRoll) {
	         cout <<"\tCaster chooses: " 
		      << StateTToString(casterChoice) << endl;
             }
	     cout << "\tVictim Roll: " << StateTToString(victimRoll) << endl;
	     if (Eye == victimRoll) {
	         cout <<"\tVictim chooses: " 
		      << StateTToString(victimChoice) << endl;
	     }
	     cout << endl;

	     // now simulate the turn
	     if (casterRoll == Eye) {
	        die.Change(casterChoice);
	     } else {
	        die.Change(casterRoll);
	     }

             cout << "\tSimulating Attack " << endl;
	     CasterAction(player,casterID-1,victimID-1, die, cth);
	     cout << "\t\tScore " << endl ;
	     cout << "\t\t  Player 1: " << player[0].Sanity() << endl;
	     cout << "\t\t  Player 2: " << player[1].Sanity() << endl;
	     cout << "\t\t  Cthulhu: " << cth << endl;



	     if (victimRoll == Eye) {
	        die.Change(victimChoice);
	     } else {
	        die.Change(victimRoll);
	     }

             cout << "\tSimulating Response" << endl;
	     VictimAction(player,casterID-1,victimID-1, die, cth);

	     cout << "\t\tScore "<< endl ;
	     cout << "\t\t  Player 1: " << player[0].Sanity() << endl ;
	     cout << "\t\t  Player 2: " << player[1].Sanity() << endl ;
	     cout << "\t\t  Cthulhu: " << cth << endl;

	     if (!player[0].IsSane() ) {
	        if (!player[1].IsSane() ) {
		    cout << "\t\tCthulhu Wins" << endl;
		} else {
		    cout << "\t\tPlayer 2 Wins " << endl;
		} 
	     } else if (!player[1].IsSane()) {
	        cout << "\tPlayer 1 Wins" << endl;
	     }

	  } else {
	     cout << "==========================================" << endl;
	     cout << endl;
	     gameOver = true;
	     game ++;
	  }
      }
   }


   return 0;
}
