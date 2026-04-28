#ifndef POKEMON_H
#define POKEMON_H

#include "../core/pokemon_types.h"

// 基础操作
void pokemon_init(Pokemon* p, const char* name, int hp, int atk, int def, int spd, int level);
void pokemon_add_skill(Pokemon* p, const char* name, int power, int accuracy, int pp,
                       PokemonType type, StatusCondition status, int status_chance, int crit_rate);
void pokemon_reset_pp(Pokemon* p);
int pokemon_is_alive(const Pokemon* p);

// 工厂函数
void create_pikachu(Pokemon* p, int level);
void create_charizard(Pokemon* p, int level);
void create_blastoise(Pokemon* p, int level);
void create_venusaur(Pokemon* p, int level);
void create_zapdos(Pokemon* p, int level);
void create_mewtwo(Pokemon* p, int level);
void create_gengar(Pokemon* p, int level);
void create_dragonite(Pokemon* p, int level);
void create_gyarados(Pokemon* p, int level);

// 根据ID创建
typedef void (*PokemonCreator)(Pokemon*, int);
PokemonCreator get_pokemon_creator(int id);

#endif
