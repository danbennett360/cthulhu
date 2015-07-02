#ifndef GAME_LOGIC_DOT_H
#define GAME_LOGIC_DOT_H

#include "dice.h"
#include "player.h"

#include <string>

const std::string RULES_VERSION= "1.0";

bool TakeTurn(PlayerT  & caster, PlayerT  & victim,  DieT & die, int & cthuhlu);
void CasterAction(PlayerT & caster, PlayerT & victim, DieT & die, int &  cth);
void VictimAction(PlayerT & caster, PlayerT & victim, DieT & die,  int & cth);

#endif
