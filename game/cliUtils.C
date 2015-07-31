#include "cliUtils.h"

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int GetEyeStrat(string s){
    if (s == "D" or s == "d") {
        return DOUG;
    }  else if (s == "F" or s == "f") {
        return FANATIC;
    }  else if (s == "P" or s == "p") {
        return PACIFIST;
    }  else if (s == "R" or s == "r") {
        return RANDOM;
    } else  {
        cout << "Unknown player strategy, Suppored D,F, Given " << s << endl;
        return RANDOM;
    }
}

int GetVictimStrat(string s) {
    return RANDOM;
}


void usage(char progname[]) {
    cout << endl;
    cout << "Usage " << progname << endl;
    cout << "\t --eye n o" << endl;
    cout << "\t\t n is the player number 1, 2, ... 6 " << endl;
    cout << "\t\t o is the eye replacement strategy" << endl;
    cout << "\t\t\t R ... Random " << endl;
    cout << "\t\t\t D ... Doug " << endl;
    cout << "\t\t\t F ... Fanatic " << endl;
    cout << "\t\t\t P ... Pacifist " << endl;
    cout << "\t --victim n o" << endl;
    cout << "\t\t n is the player number 1, 2, ... 6 " << endl;
    cout << "\t\t o is the victim selectionstrategy" << endl;
    cout << "\t\t\t R ... Random " << endl;
    cout << "\t --players n" << endl;
    cout << "\t\t n is the number of players, 2 to 6" << endl;
    cout << "\t --verbose " << endl;
    cout << "\t\t Turn on verbose output " << endl;
    cout << "\t --games n" << endl;
    cout << "\t\t n is the number of games to play (1000 default)" << endl;
    cout << "\t --help " << endl;
    cout << "\t\t  this help page" << endl;
    cout << endl;
    return;
}

// should have a check for valid player and strategy
void ParseEyeArgs(int argc, char * argv[], int &  position, int & player, int & strategy) {
    // assume argv[position] == "--eye"
    int num;

    position ++;
    if (position+1 < argc) {
        player = atoi(argv[position]) - 1;
	if (player < 0 or player > 6) {
	    cerr << "--eye " << argv[position] << " is wrong." << endl;
	    cerr << "\t the number should be between 1 and 6" << endl;
	    usage(argv[0]);
	    exit(-1);
	}
	position ++;
	// check is handleled in routine, RANDOM by default
	strategy = GetEyeStrat(argv[position]);
	position ++;
    } else {
        cerr << "--eye  requires a player number and a strategy" << endl;
	usage(argv[0]);
	exit(-1);
    }

    return;
}

int GetGamesArg(int argc, char * argv[], int & position){
     int games;

     position++;
     if (position < argc) {
         games = atoi(argv[position]) ;
         position++;
         if (games < 1) {
             games = 1;
         }
     } else {
         cout << "--games requires an integer argument" << endl;
     }
     return games;
}

