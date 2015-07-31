#ifndef CLI_UTILS
#define CLI_UTILS

#include <string>
#include "player.h"

int GetEyeStrat(std::string s);
int GetVictimStrat(std::string s);
void usage(char progname[]);
void ParseEyeArgs(int argc, char * argv[], int &  position, int & player, int & strategy);
int GetGamesArg(int argc, char * argv[], int & position);


#endif
