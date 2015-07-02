#ifndef DANS_XML_DOT_H
#define DANS_XML_DOT_H

#include <iostream>
#include <tinyxml2.h>

#include <unistd.h>
#include <time.h>
#include <sys/time.h>

void XMLSaveFileInit(string filename="gamesave.xml", int argc, char * argv[]) ;
void XMLSaveFileFinish();
void StartGame(int number, int players);
void EndGame();
void SaveTurn(int attacker, int victim, string die1, string die2, string sub1, string sub2);



#endif
