# 一些备忘录

### 正式比赛开始前（省赛新版）：

1. 开上位机代码后先按“fake”按钮进行上下位机通信校准，直到上位机持续正常显示“start？“
2. 下位机上电后换履带方向
3. 货物距离货架边缘约5-8mm

### 正式比赛开始前（校赛旧版，已废弃）：

1. 开上位机代码后先跑两格（防止32和nano的io信号错位）
1. 打开补光灯
2. 上电后换履带方向
2. 货物距离货架边缘约5-8mm，两侧货物尽可能靠两边（beer尽可能不要在3号位置，red尽可能不要在2号位置）

### 省赛还可以改进的部分：

1. 32和nano间加一根杜邦线，用总共两个io口来表示3种信号√
2. 32和arduino之间加六根杜邦线，直接用32来控制舵机（可以全抓或者抓已知位置）
3. 视觉（干扰物分辨、两侧物体检测错误√）
3. 爪子小舵机抖动√（原因：UNO供电不稳定）

### 机械部分：

1. 超高问题（新买补光灯管）√
2. 翻斗、挡板改装（超宽）√



### 已经改了的零件

- 翻斗侧挡板（镜像）
- 翻斗支撑臂
- 前侧抓取挡板*2
- 驾驶舱下部补光灯架
- 驾驶舱下部补光灯架_带背板
- 翻斗接收板