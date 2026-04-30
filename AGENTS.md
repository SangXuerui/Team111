# AGENTS.md - 宝可梦对战游戏

## 项目概述
基于C语言的命令行宝可梦对战游戏，实现属性克制、状态异常、暴击等核心战斗机制。玩家选择宝可梦与AI对战。

## 技术栈
- 语言：C99/C11
- 构建：GCC/MSVC + Make（可选）
- 测试：CUnit + GitHub Actions CI

## 目录结构
pokemon-battle/
	src/
		main.c              # 程序入口，UI集成，战斗流程编排
		battle.c            # 战斗引擎核心（回合控制、胜负判定）
		battle.h
		damage.c            # 伤害计算模块（公式、属性克制、暴击）
		damage.h
		status.c            # 状态异常模块（中毒/烧伤/睡眠/麻痹）
		status.h
		pokemon_factory.c   # 宝可梦工厂（创建实例、属性计算）
		pokemon_factory.h
		pokemon_core.h      # 核心数据结构（Pokemon、Skill枚举）
		ai.c                # AI决策（技能选择策略）
		ai.h
		platform_io.c       # 平台IO抽象层
	tests/
		test_damage.c       # 伤害计算单元测试
		test_status.c       # 状态异常单元测试
		test_battle.c       # 战斗流程集成测试
	github/workflows/ci.yml
	Makefile
	README.md

## 核心模块职责
| 模块 | 文件 | 核心函数 | 职责 |
| 战斗引擎 | battle.c | `run_battle()`, `execute_turn()` | 战斗循环、回合顺序、胜负判定 |
| 伤害计算 | damage.c | `calc_dmg()`, `check_hit()`, `check_crit()` | 伤害公式、命中/暴击判定、属性克制 |
| 状态系统 | status.c | `apply_status()`, `handle_status_damage()`, `handle_status_turn()` | 状态附加、每回合效果、自然解除 |
| 宝可梦工厂 | pokemon_factory.c | `create_pokemon()`, `create_from_template()` | 实例化宝可梦、等级属性计算 |
| AI系统 | ai.c | `ai_select_skill()`, `calc_skill_value()` | 技能评估、最优选择 |
| 平台IO | platform_io.c | `clear_screen()`, `set_color()`, `get_input()` | 跨平台终端控制 |

## 编码规范
### 命名约定
// 类型：PascalCase + _t后缀
typedef struct BattleEngine_t BattleEngine_t;
// 函数：snake_case，动词开头
int calculate_damage(Pokemon_t* attacker, Pokemon_t* defender, Skill_t* skill);
// 常量：UPPER_SNAKE_CASE
#define MAX_SKILLS 4
#define SLEEP_MIN_TURNS 3
// 宏：UPPER_SNAKE_CASE
#define CHECK_PTR(ptr) if ((ptr) == NULL) return -1;

### 内存管理
// 动态分配必须配对free，使用后置标签模式
Pokemon_t* create_pokemon(void) {
    Pokemon_t* p = malloc(sizeof(Pokemon_t));
    if (!p) goto error;
    // 初始化...
    return p;
error:
    free(p);
    return NULL;
}

### 错误处理
// 返回int表示成功(0)或错误码(-1, -2...)
// 使用assert进行调试期检查
int battle_execute_turn(Battle_t* b, int skill_idx) {
    assert(b != NULL);
    assert(skill_idx >= 0 && skill_idx < MAX_SKILLS);
    // ...
}

### 注释规范
/
 * @brief 计算技能伤害
 * @param attacker 攻击方指针，不可为NULL
 * @param defender 防御方指针，不可为NULL
 * @param skill 技能指针，不可为NULL
 * @param out_crit 输出暴击标志，可为NULL
 * @return 伤害值，0表示未命中或无效
 */
int calculate_damage(Pokemon_t* attacker, Pokemon_t* defender, 
                     Skill_t* skill, int* out_crit);

## 禁止操作清单
### 绝对禁止
- 在头文件中定义函数实现（inline静态函数除外）
- 使用 `goto` 跨函数跳转
- 忽略编译器警告（必须 `-Wall -Wextra -Werror`）
- 硬编码魔法数字（必须使用 `#define`）
- `scanf` 不检查返回值
- 直接操作 `stdout`/`stdin` 而不通过平台抽象层

### 条件禁止
- 全局变量：仅允许只读常量表，状态变量必须封装
- 递归：深度不超过3层
- 动态内存：每个分配必须有对应的释放路径

## 测试要求
# 运行所有测试
make test
# 运行单个测试
./tests/test_damage --verbose

### 测试覆盖率目标
- 核心模块（伤害计算、状态）：≥90%
- 战斗流程：≥70%
- 平台IO层：≥50%

## AI辅助开发指南
### 生成代码前必须确认
1. 该函数属于哪个模块？
2. 是否需要添加对应的单元测试？
3. 是否使用了平台抽象层API？
4. 是否添加了必要的注释和断言？

### 新增功能的标准步骤
1. 在对应模块的头文件中声明函数
2. 在 `.c` 文件中实现，添加断言检查
3. 在 `tests/` 下添加单元测试
4. 更新 `.github/workflows/ci.yml`（如需要）
5. 更新 README.md 和本文档

### 响应模板
当被要求添加新功能时，AI应输出：
【模块归属】：[模块名]
【新增文件】：[文件名]（如需要）
【函数签名】：[返回类型 函数名(参数列表)]
【测试用例】：[至少2个测试场景]
【依赖关系】：[依赖的现有模块]
