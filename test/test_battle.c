#include <stdio.h>
#include "../battle.h"

int is_battle_finished(int hp) {
    return hp <= 0;
}

int main() {
    printf("===== 【模块3】战斗回合执行模块测试 =====\n");
    int r1 = is_battle_finished(0);
    printf("血量归零判断：期望1，实际=%d → %s\n", r1, r1 == 1 ? "通过" : "失败");
    int r2 = is_battle_finished(-5);
    printf("血量低于0判断：期望1，实际=%d → %s\n", r2, r2 == 1 ? "通过" : "失败");
    int r3 = is_battle_finished(100);
    printf("存活状态判断：期望0，实际=%d → %s\n", r3, r3 == 0 ? "通过" : "失败");
    return 0;
}