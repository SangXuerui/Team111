#ifndef POKEMON_DATA_H
#define POKEMON_DATA_H

#include "pokemon.h"
#include <string.h>

static inline void init_pokemon(Pokemon* p, const char* name, int hp, int atk, int def, int spd) {
    strcpy(p->name, name);
    p->max_hp = hp;
    p->current_hp = hp;
    p->attack = atk;
    p->defense = def;
    p->speed = spd;
    p->skill_count = 0;
    p->is_alive = 1;
}

static inline void add_skill(Pokemon* p, const char* name, int power, int accuracy, const char* type) {
    if (p->skill_count < MAX_SKILLS) {
        strcpy(p->skills[p->skill_count].name, name);
        p->skills[p->skill_count].power = power;
        p->skills[p->skill_count].accuracy = accuracy;
        strcpy(p->skills[p->skill_count].type, type);
        p->skill_count++;
    }
}

static inline void show_pokemon_info(const Pokemon* p) {
    printf("\n【%s】\n", p->name);
    printf("  HP: %d | 攻击：%d | 防御：%d | 速度：%d\n", 
           p->max_hp, p->attack, p->defense, p->speed);
    printf("  技能:\n");
    for (int i = 0; i < p->skill_count; i++) {
        printf("    - %s (威力:%d, 命中:%d%%, 类型:%s)\n",
               p->skills[i].name, p->skills[i].power, 
               p->skills[i].accuracy, p->skills[i].type);
    }
}

#endif // POKEMON_DATA_H
