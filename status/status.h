#ifndef STATUS_H
#define STATUS_H

#include "../core/pokemon_types.h"

void apply_status(Pokemon* target, StatusCondition status, int chance);
void handle_status_damage(Pokemon* p);
void handle_status_turn(Pokemon* p);
int is_asleep(Pokemon* p);
int is_paralyzed_can_act(Pokemon* p);
const char* get_status_name(StatusCondition status);

#endif
