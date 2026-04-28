#ifndef POKEMON_TYPES_H
#define POKEMON_TYPES_H

#include "constants.h"

// ========== 属性类型 ==========
typedef enum {
    TYPE_NORMAL, TYPE_FIRE, TYPE_WATER, TYPE_GRASS, TYPE_ELECTRIC,
    TYPE_ICE, TYPE_FIGHTING, TYPE_POISON, TYPE_GROUND, TYPE_FLYING,
    TYPE_PSYCHIC, TYPE_BUG, TYPE_ROCK, TYPE_GHOST, TYPE_DRAGON,
    TYPE_DARK, TYPE_STEEL, TYPE_FAIRY, TYPE_COUNT
} PokemonType;

// ========== 状态异常 ==========
typedef enum {
    STATUS_NONE,
    STATUS_SLEEP,
    STATUS_PARALYZE,
    STATUS_POISON,
    STATUS_BURN
} StatusCondition;

// ========== 战斗结果 ==========
typedef enum {
    RESULT_P1_WIN,
    RESULT_P2_WIN,
    RESULT_DRAW,
    RESULT_ONGOING
} BattleResult;

// ========== 技能结构 ==========
typedef struct {
    char name[NAME_LENGTH];
    int power;
    int accuracy;
    int pp;
    int max_pp;
    PokemonType type;
    int status_chance;
    StatusCondition status;
    int crit_rate;
} Skill;

// ========== 宝可梦结构 ==========
typedef struct {
    char name[NAME_LENGTH];
    int max_hp;
    int current_hp;
    int attack;
    int defense;
    int speed;
    Skill skills[MAX_SKILLS];
    int skill_count;
    StatusCondition status;
    int status_turns;
    int level;
    int exp;
    int exp_to_next;
} Pokemon;

// ========== 战斗状态 ==========
typedef enum { BATTLE_SELECT, BATTLE_END } BattleState;

typedef struct {
    Pokemon p1;
    Pokemon p2;
    int turn;
    BattleState state;
    BattleResult result;
} Battle;

#endif
