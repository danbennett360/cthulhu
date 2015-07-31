#ifndef PLAYER_DOT_H
#define PLAYER_DOT_H

#include "dice.h"
#include <iostream>
#include <string>
#include <vector>



// per the rules, but we may wish to play with this.
const int START_SANITY = 3;
const std::string PLAYER_VERSION = "1.0";


// stratigies for when we roll an eye.
const int RANDOM = 10;
const int DOUG = 11;
const int FANATIC = 12;
const int PACIFIST = 13; 

const int ATTACKER = 100;
const int DEFENDER = 101;

class PlayerT {
    public:
        PlayerT(int strat1=RANDOM, int strat2 = RANDOM);
	int ID();
	void EyeStrategy(int);
	void VictimStrategy(int);
	std::string EyeStrategy();
	std::string VictimStrategy();
	bool IsSane();
	int Sanity();
	void GetToken();   // the player gets a token
	void GiveToken();  // the player gives a token away
        StateT DecideResult(int role, int opponentTokens, int cthulhuToken);
	void Reset();
	int SelectVictim(std::vector<PlayerT> players, int cthulhuToken);
    private:
        int sanity;
	int id;
	bool isSane;
	int eyeStrategy, victimStrategy;
	static int maxID;
};

std::ostream & operator << (std::ostream & s, PlayerT  & p);

#endif
