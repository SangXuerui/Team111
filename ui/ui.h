#ifndef UI_H
#define UI_H

#include "../core/pokemon_types.h"

void show_hp_bar(Pokemon* p, int bar_length);
void show_pokemon_info(Pokemon* p);
void show_battle_status(Battle* b);
int select_pokemon_menu(void);
int select_skill_menu(Pokemon* p);
void show_damage_message(const DamageResult* result, const char* skill_name);
void show_effective_message(float effectiveness);
void clear_screen(void);

#endif
