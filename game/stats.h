#ifndef STATS_DOT_H
#define STATS_DOT_H

#include <vector>
#include "GameLogic.h"

void AccumulateWins(PlayerV & players, std::vector<int> & wins, int & cth);
void PrintStats(PlayerV & players, std::vector<int>  wins, int  cth, int games, int totalTurns);

#endif
