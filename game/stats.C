#include "GameLogic.h"
#include "stats.h"
#include <iostream>

using namespace std;

void AccumulateWins(PlayerV & players, vector<int> & wins, int & cth){

     int numberSane = CountSane(players);
     int i;

     if (numberSane== 0) {
         cth ++;
     } else if (numberSane ==1 ) {
         i = FindWinner(players);
         wins[i]++;
     } else {
         cerr << "Logic problem, multiple winners " << endl;
     }

     return;
}

void PrintStats(PlayerV & players, vector<int>  wins, int  cth, int games, int totalTurns){
        int i;

        cout << endl;
        cout << "\tSummary Information " << endl << endl;
        for (int i = 0; i < players.size(); i++) {
            cout << "Player " << players[i].ID() << " ["
                 << players[i].EyeStrategy() << ", "
                 << players[i].VictimStrategy() <<"] "
                 << " won: " << wins[i] << "/" << games
                 << " or \t" << wins[i] / float(games) * 100 << "%" << endl;
        }
        cout << "Cthulhu wins: " << cth << "/"  << games
             << " or " << cth / float(games) * 100 << "%" << endl;
        cout << "Average game length " << totalTurns / float(games) << endl;

        cout << endl;
 
        return;
}
