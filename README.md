团队名称：111编译先锋队

团队口号
代码为刃，逻辑为锋，编译未来。

成员角色分配
Scrum Master (SM)：桑雪瑞（GitHub ID：SangXuerui）
Product Owner (PO)：郭学博（GitHub ID：[gxb419]）
开发组成员：杨家鹏（GitHub ID：[yang172234]）

# 宝可梦对战游戏 (Pokemon Battle Game)
一个基于C语言开发的命令行宝可梦对战游戏，支持属性克制、状态异常、暴击等经典战斗机制。

1、系统架构图
参见 [architecture.puml](docs/architecture.puml)

2、核心业务模块说明
（1）战斗引擎 (Battle Engine)
- 文件: `battle.c`, `battle.h`
- 职责: 
  - 控制战斗主循环
  - 协调回合顺序
  - 调用伤害计算和状态处理
  - 判定胜负条件

（2）伤害计算模块 (Damage Calculator)
- 文件: `damage.c`, `damage.h`
- 职责:
  - 命中判定
  - 基础伤害公式计算
  - 属性克制系数计算
  - 暴击判定与修正
  - 随机波动生成

（3）状态异常系统 (Status System)
- 文件: `status.c`, `status.h`
- 职责:
  - 状态附加判定
  - 每回合状态效果处理（中毒/烧伤扣血）
  - 状态自然解除计时
  - 行动限制判定（睡眠/麻痹）

（4）宝可梦工厂 (Pokemon Factory)
- 文件: `pokemon_factory.c`, `pokemon_factory.h`
- 职责:
  - 根据模板创建宝可梦实例
  - 根据等级计算属性
  - 技能分配与PP初始化

（5）AI决策系统 (AI System)
- 文件: `ai.c`, `ai.h`
- 职责:
  - 评估技能克制效果
  - 选择最优技能
  - 考虑技能PP剩余

3、本地开发环境搭建
（1）系统要求
- 操作系统: Windows 10+ / Linux / macOS
- 编译器: GCC 4.8+ 或 MSVC 2017+
- 构建工具: Make (可选)

（2）Windows 环境搭建
（2.1）方案一：使用 MinGW-w64
1. 下载并安装 MinGW-w64
	访问: https://www.mingw-w64.org/
2. 安装完成后添加环境变量
set PATH=%PATH%;C:\mingw64\bin
3. 编译项目
gcc -o pokemon.exe main.c -Wall -Wextra
4. 运行
./pokemon.exe

（2.2）方案二：使用 Visual Studio
1. 打开开发者命令提示符
2. 编译
cl /Fe:pokemon.exe main.c
3. 运行
pokemon.exe

（3） Linux/macOS 环境搭建
1. 安装 GCC (如未安装)
Ubuntu/Debian:
sudo apt-get install gcc make
macOS:
xcode-select --install

2. 克隆或下载代码
git clone <repository-url>
cd pokemon-battle

3. 编译
gcc -o pokemon main.c -Wall -Wextra

4. 运行
./pokemon

4、跨平台编译说明
当前代码使用 ANSI 转义码实现颜色，在 Windows 10+ 需要启用虚拟终端处理：

// 在 main() 开头添加（仅Windows）
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

5、快速开始
（1）编译并运行
gcc -o pokemon main.c && ./pokemon

（2）游戏流程
- 选择你的宝可梦 (1-9)
- 观看战斗进行
- 每个回合选择技能 (1-4)
- 直到一方宝可梦HP归零

6、游戏机制
（1）属性克制
支持18种宝可梦属性，具有完整的克制/抵抗/免疫关系。

（2）状态异常
状态	效果	持续时间
睡眠	无法行动	3-5回合
麻痹	速度减半，25%无法行动	永久
中毒	每回合损失1/16 HP	永久
烧伤	攻击减半，每回合损失1/16 HP	永久

（3）伤害公式
伤害 = (攻击力 × 技能威力 / 防御力) × 属性克制 × 暴击(1.5) × 随机(0.85~1.0)

7、扩展指南
（1）添加新宝可梦
- 在 `pokemon_data.h` 中添加模板定义
- 实现创建函数
- 在 `select_pokemon()` 中添加选项

（2）添加新技能
- 定义技能参数 (威力、命中、类型、效果)
- 在宝可梦创建函数中通过 `add_skill()` 添加

（3）已知限制
- 仅支持单属性宝可梦
- 无经验值/等级成长系统
- AI策略相对简单
- 不支持交换宝可梦

8、贡献指南
-  Fork 本仓库
- 创建功能分支 (`git checkout -b feature/amazing`)
- 提交更改 (`git commit -m 'Add amazing feature'`)
- 推送到分支 (`git push origin feature/amazing`)
- 创建 Pull Request
