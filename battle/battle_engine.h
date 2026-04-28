#ifndef BATTLE_ENGINE_H
#define BATTLE_ENGINE_H

#include "../core/pokemon_types.h"

typedef struct {
    Pokemon p1;
    Pokemon p2;
    int turn;
    BattleState state;
    BattleResult result;
} Battle;

void battle_init(Battle* b, Pokemon* p1, Pokemon* p2);
void battle_run(Battle* b);
BattleResult battle_check_winner(Battle* b);

#endif
