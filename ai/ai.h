#ifndef AI_H
#define AI_H

#include "../core/pokemon_types.h"

typedef struct {
    int skill_index;
    float score;
} AIDecision;

int ai_select_skill(Pokemon* ai_pokemon, Pokemon* opponent);

#endif
