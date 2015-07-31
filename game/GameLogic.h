#ifndef GAME_LOGIC_DOT_H
#define GAME_LOGIC_DOT_H

#include <vector>
#include "dice.h"
#include "player.h"

#include <string>

const std::string RULES_VERSION= "1.0";

typedef std::vector<PlayerT> PlayerV;
bool TakeTurn(PlayerV & players, int caster, int victim,  DieT & die, int & cthuhlu);
void CasterAction(PlayerV & players, int caster, int victim, DieT & die, int &  cth);
void VictimAction(PlayerV & players,  int caster, int victim, DieT & die,  int & cth);

int CountSane(PlayerV & players);
int FindWinner(PlayerV & players);
void TakeATurn(PlayerV & players, int & cthulu, int caster, DieT & die);

#endif
