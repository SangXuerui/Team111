#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SKILLS 4
#define NAME_LENGTH 32

typedef struct {
    char name[NAME_LENGTH];
    int power;
    int accuracy;
    char type[16];
} Skill;

typedef struct {
    char name[NAME_LENGTH];
    int max_hp;
    int current_hp;
    int attack;
    int defense;
    int speed;
    Skill skills[MAX_SKILLS];
    int skill_count;
} Pokemon;

typedef enum { BATTLE_SELECT, BATTLE_END } BattleState;
typedef enum { RESULT_P1_WIN, RESULT_P2_WIN, RESULT_DRAW } BattleResult;

typedef struct {
    Pokemon p1;
    Pokemon p2;
    int turn;
    BattleState state;
    BattleResult result;
} Battle;

void init_pokemon(Pokemon* p, const char* name, int hp, int atk, int def, int spd) {
    strcpy(p->name, name);
    p->max_hp = hp;
    p->current_hp = hp;
    p->attack = atk;
    p->defense = def;
    p->speed = spd;
    p->skill_count = 0;
}

void add_skill(Pokemon* p, const char* name, int power, int accuracy, const char* type) {
    if (p->skill_count < MAX_SKILLS) {
        strcpy(p->skills[p->skill_count].name, name);
        p->skills[p->skill_count].power = power;
        p->skills[p->skill_count].accuracy = accuracy;
        strcpy(p->skills[p->skill_count].type, type);
        p->skill_count++;
    }
}

void show_hp_bar(Pokemon* p, int bar_length) {
    int filled = (p->current_hp * bar_length) / p->max_hp;
    printf("[");
    for (int i = 0; i < bar_length; i++) {
        printf(i < filled ? "#" : "-");
    }
    printf("]");
}

void create_pikachu(Pokemon* p) {
    init_pokemon(p, "皮卡丘", 100, 55, 40, 90);
    add_skill(p, "十万伏特", 40, 90, "电");
    add_skill(p, "电光一闪", 30, 100, "一般");
    add_skill(p, "铁尾", 35, 75, "钢");
}

void create_charizard(Pokemon* p) {
    init_pokemon(p, "喷火龙", 120, 65, 55, 60);
    add_skill(p, "喷射火焰", 45, 90, "火");
    add_skill(p, "龙爪", 40, 85, "龙");
    add_skill(p, "空气斩", 35, 80, "飞行");
}

void create_blastoise(Pokemon* p) {
    init_pokemon(p, "水箭龟", 130, 50, 70, 45);
    add_skill(p, "水炮", 50, 80, "水");
    add_skill(p, "咬住", 30, 100, "恶");
    add_skill(p, "火箭头槌", 35, 95, "一般");
}

void create_venusaur(Pokemon* p) {
    init_pokemon(p, "妙蛙花", 140, 45, 65, 40);
    add_skill(p, "飞叶快刀", 40, 95, "草");
    add_skill(p, "日光束", 55, 75, "草");
    add_skill(p, "睡眠粉", 25, 85, "草");
}

void create_zapdos(Pokemon* p) {
    init_pokemon(p, "雷电鸟", 110, 60, 50, 80);
    add_skill(p, "打雷", 50, 75, "电");
    add_skill(p, "啄钻", 35, 95, "飞行");
    add_skill(p, "电磁波", 20, 90, "电");
}

void create_mewtwo(Pokemon* p) {
    init_pokemon(p, "超梦", 115, 75, 45, 95);
    add_skill(p, "精神强念", 50, 90, "超能力");
    add_skill(p, "暗影球", 45, 85, "幽灵");
    add_skill(p, "波导弹", 40, 95, "格斗");
}

void create_gengar(Pokemon* p) {
    init_pokemon(p, "耿鬼", 95, 70, 35, 100);
    add_skill(p, "影子球", 45, 90, "幽灵");
    add_skill(p, "污泥炸弹", 40, 85, "毒");
    add_skill(p, "噩梦", 30, 80, "幽灵");
}

int select_pokemon() {
    int choice;
    printf("\n========== 宝可梦选择 ==========\n");
    printf("  1. 皮卡丘 (速度快，防御低)\n");
    printf("  2. 喷火龙 (能力均衡)\n");
    printf("  3. 水箭龟 (防御高，速度慢)\n");
    printf("  4. 妙蛙花 (HP 高，速度慢)\n");
    printf("  5. 雷电鸟 (攻击高，速度较快)\n");
    printf("  6. 超梦 (特攻型，速度快)\n");
    printf("  7. 耿鬼 (速度最快，防御低)\n");
    printf("\n");
    while (1) {
        printf("选择你的宝可梦 (1-7): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("无效输入!\n");
            continue;
        }
        if (choice >= 1 && choice <= 7) return choice;
        printf("无效输入!\n");
    }
}

void show_battle(Battle* b) {
    printf("\n=== 第 %d 回合 ===\n", b->turn);
    printf("%s HP: ", b->p1.name);
    show_hp_bar(&b->p1, 20);
    printf(" (%d/%d)\n", b->p1.current_hp, b->p1.max_hp);
    printf("%s HP: ", b->p2.name);
    show_hp_bar(&b->p2, 20);
    printf(" (%d/%d)\n", b->p2.current_hp, b->p2.max_hp);
}

int select_skill(Pokemon* p) {
    int choice;
    printf("\n%s 的技能:\n", p->name);
    for (int i = 0; i < p->skill_count; i++) {
        printf("  %d. %s (威力:%d, 命中:%d%%)\n", i+1, p->skills[i].name, p->skills[i].power, p->skills[i].accuracy);
    }
    while (1) {
        printf("选择 (1-%d): ", p->skill_count);
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("无效输入!\n");
            continue;
        }
        if (choice >= 1 && choice <= p->skill_count) return choice - 1;
        printf("无效输入!\n");
    }
}

int check_hit(int accuracy) {
    return (rand() % 100 + 1) <= accuracy;
}

int calc_dmg(Pokemon* atk, Pokemon* def, Skill* skill) {
    if (!check_hit(skill->accuracy)) return 0;
    float base = (float)atk->attack * skill->power / def->defense;
    float rnd = 0.85f + (float)rand() / RAND_MAX * 0.15f;
    return (int)(base * rnd);
}

void attack(Battle* b, int is_p1, int skill_idx) {
    Pokemon* atk = is_p1 ? &b->p1 : &b->p2;
    Pokemon* def = is_p1 ? &b->p2 : &b->p1;
    Skill* skill = &atk->skills[skill_idx];
    printf("\n%s 使用了 %s!\n", atk->name, skill->name);
    if (!check_hit(skill->accuracy)) {
        printf("攻击未命中!\n");
        return;
    }
    int dmg = calc_dmg(atk, def, skill);
    if (dmg > 0) {
        def->current_hp -= dmg;
        if (def->current_hp < 0) def->current_hp = 0;
        printf("造成 %d 点伤害!\n", dmg);
    }
}

BattleResult check_win(Battle* b) {
    if (b->p1.current_hp <= 0 && b->p2.current_hp <= 0) return RESULT_DRAW;
    if (b->p1.current_hp <= 0) return RESULT_P2_WIN;
    if (b->p2.current_hp <= 0) return RESULT_P1_WIN;
    return RESULT_DRAW;
}

void run_battle(Battle* b) {
    printf("\n=== 战斗开始! ===\n%s 对 %s\n\n", b->p1.name, b->p2.name);
    while (1) {
        show_battle(b);
        printf(">>> 玩家 1 回合\n");
        int p1_skill = select_skill(&b->p1);
        printf(">>> 玩家 2 回合\n");
        int p2_skill = rand() % b->p2.skill_count;
        printf("玩家 2 选择了 %s!\n", b->p2.skills[p2_skill].name);
        printf("\n--- 攻击阶段 ---\n");
        if (b->p1.speed >= b->p2.speed) {
            attack(b, 1, p1_skill);
            BattleResult r = check_win(b);
            if (r != RESULT_DRAW) { printf("%s 获胜!\n", r == RESULT_P1_WIN ? b->p1.name : b->p2.name); return; }
            attack(b, 0, p2_skill);
            r = check_win(b);
            if (r != RESULT_DRAW) { printf("%s 获胜!\n", r == RESULT_P1_WIN ? b->p1.name : b->p2.name); return; }
        } else {
            attack(b, 0, p2_skill);
            BattleResult r = check_win(b);
            if (r != RESULT_DRAW) { printf("%s 获胜!\n", r == RESULT_P1_WIN ? b->p1.name : b->p2.name); return; }
            attack(b, 1, p1_skill);
            r = check_win(b);
            if (r != RESULT_DRAW) { printf("%s 获胜!\n", r == RESULT_P1_WIN ? b->p1.name : b->p2.name); return; }
        }
        b->turn++;
    }
}

int main() {
    Pokemon player1, player2;
    Battle battle;

    printf("=== 宝可梦对战游戏 v1.0 ===\n");

    int p1_choice = select_pokemon();
    if (p1_choice == 1) create_pikachu(&player1);
    else if (p1_choice == 2) create_charizard(&player1);
    else if (p1_choice == 3) create_blastoise(&player1);
    else if (p1_choice == 4) create_venusaur(&player1);
    else if (p1_choice == 5) create_zapdos(&player1);
    else if (p1_choice == 6) create_mewtwo(&player1);
    else create_gengar(&player1);

    int p2_choice = (rand() % 7) + 1;
    if (p2_choice == 1) create_pikachu(&player2);
    else if (p2_choice == 2) create_charizard(&player2);
    else if (p2_choice == 3) create_blastoise(&player2);
    else if (p2_choice == 4) create_venusaur(&player2);
    else if (p2_choice == 5) create_zapdos(&player2);
    else if (p2_choice == 6) create_mewtwo(&player2);
    else create_gengar(&player2);

    printf("\n玩家 1 选择了：%s\n", player1.name);
    printf("玩家 2 选择了：%s\n", player2.name);

    battle.p1 = player1;
    battle.p2 = player2;
    battle.turn = 1;

    run_battle(&battle);

    printf("\n按回车键退出...");
    while (getchar() != '\n');
    getchar();

    return 0;
}
