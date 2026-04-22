#include <stdio.h>
#include "../battle.h"

int apply_status(int hp, int status) {
    if(status == 1) return hp - hp/10;
    if(status == 2) return hp - hp*15/100;
    return hp;
}

int main() {
    printf("===== 【模块2】状态异常处理模块测试 =====\n");
    int hp1 = apply_status(100, 1);
    printf("中毒每回合扣血：期望90，实际=%d → %s\n", hp1, hp1 == 90 ? "通过" : "失败");
    int hp2 = apply_status(100, 2);
    printf("烧伤每回合扣血：期望85，实际=%d → %s\n", hp2, hp2 == 85 ? "通过" : "失败");
    int hp3 = apply_status(100, 0);
    printf("正常无状态：期望100，实际=%d → %s\n", hp3, hp3 == 100 ? "通过" : "失败");
    return 0;
}