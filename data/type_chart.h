#ifndef TYPE_CHART_H
#define TYPE_CHART_H

#include "../core/pokemon_types.h"

void init_type_chart(void);
float get_type_effectiveness(PokemonType attack_type, PokemonType defend_type);
const char* get_type_name(PokemonType type);
PokemonType get_pokemon_type_from_name(const char* name);

#endif
