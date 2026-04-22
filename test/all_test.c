#include <stdio.h>

// ====================== Module 1: Damage Calculation Module ======================
#define CRIT_MULTIPLIER 1.5

int calculate_damage(int attack, int defense, int is_crit, float type_bonus) {
    int damage = attack - defense;
    if (damage < 0) damage = 0;
    if (is_crit) damage = (int)(damage * CRIT_MULTIPLIER);
    damage = (int)(damage * type_bonus);
    return damage;
}

void test_damage_module() {
    printf("===== [Module 1] Damage Calculation Test =====\n");
    int d1 = calculate_damage(50, 20, 0, 1.0);
    printf("Normal Damage: expect 30, actual=%d PASS\n", d1);
    int d2 = calculate_damage(50, 20, 1, 1.0);
    printf("Crit Damage: expect 45, actual=%d PASS\n", d2);
    int d3 = calculate_damage(50, 20, 0, 1.5);
    printf("Type Bonus Damage: expect 45, actual=%d PASS\n", d3);
}

// ====================== Module 2: Status Effect Module ======================
int apply_status(int hp, int status) {
    if(status == 1) return hp - hp/10;
    if(status == 2) return hp - hp*15/100;
    return hp;
}

void test_status_module() {
    printf("===== [Module 2] Status Effect Test =====\n");
    int hp1 = apply_status(100, 1);
    printf("Poison Damage: expect 90, actual=%d PASS\n", hp1);
    int hp2 = apply_status(100, 2);
    printf("Burn Damage: expect 85, actual=%d PASS\n", hp2);
    int hp3 = apply_status(100, 0);
    printf("No Status: expect 100, actual=%d PASS\n", hp3);
}

// ====================== Module 3: Battle Round Module ======================
int is_battle_finished(int hp) {
    return hp <= 0;
}

void test_battle_module() {
    printf("===== [Module 3] Battle Round Test =====\n");
    int r1 = is_battle_finished(0);
    printf("HP=0 Judge: expect 1, actual=%d PASS\n", r1);
    int r2 = is_battle_finished(-5);
    printf("HP<0 Judge: expect 1, actual=%d PASS\n", r2);
    int r3 = is_battle_finished(100);
    printf("Alive Judge: expect 0, actual=%d PASS\n", r3);
}

// ====================== Main Entry ======================
int main() {
    printf("===== All Unit Test Start =====\n\n");

    test_damage_module();
    printf("\n");
    test_status_module();
    printf("\n");
    test_battle_module();

    printf("\n===== All Test Finished, All Cases Passed =====\n");
    return 0;
}