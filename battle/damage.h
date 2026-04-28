#ifndef DAMAGE_H
#define DAMAGE_H

#include "../core/pokemon_types.h"

typedef struct {
    int damage;
    int is_crit;
    int is_miss;
    float effectiveness;
} DamageResult;

void damage_calc_init(Pokemon* attacker, Pokemon* defender, Skill* skill, DamageResult* result);
int check_hit(int accuracy);
int check_crit(int crit_rate);

#endif
