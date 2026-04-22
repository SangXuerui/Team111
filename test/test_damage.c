#include <stdio.h>
#include "../battle.h"

#define CRIT_MULTIPLIER 1.5
int calculate_damage(int attack, int defense, int is_crit, float type_bonus) {
    int damage = attack - defense;
    if (damage < 0) damage = 0;
    if (is_crit) damage = (int)(damage * CRIT_MULTIPLIER);
    damage = (int)(damage * type_bonus);
    return damage;
}

int main() {
    printf("===== 【模块1】伤害计算模块测试 =====\n");
    int d1 = calculate_damage(50, 20, 0, 1.0);
    printf("普通伤害计算：期望30，实际=%d → %s\n", d1, d1 == 30 ? "通过" : "失败");
    int d2 = calculate_damage(50, 20, 1, 1.0);
    printf("暴击伤害计算：期望45，实际=%d → %s\n", d2, d2 == 45 ? "通过" : "失败");
    int d3 = calculate_damage(50, 20, 0, 1.5);
    printf("属性克制伤害：期望45，实际=%d → %s\n", d3, d3 == 45 ? "通过" : "失败");
    return 0;
}