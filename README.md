# 班级积分计算工具 - 项目文档

## 项目所含内容清单

- 参与情况记录文件（计算程序输入文件）
- 积分计算程序
- 项目所含头文件及源代码
- 项目文档（当前文件）
- 积分计算规则 pdf 文档

## 计算工具使用方式

### 基本操作步骤

1. 在文件 `/inputfiles/Attendence.in` 中按**输入数据填写规范**[^1]填写参与情况记录数据
2. 运行可执行文件 `/figure.exe` 
3. 查看文件 `/outputfiles/Scores.out`，此即计算后产生的积分表

###  输入数据填写规范

1. 第一行应填入一个正整数，用来表示班级内的人数，我们暂时钦定输入的整数为 `n`
2. 接下来填入一行**活动应到人数记录向量**，按顺序给出每次活动的**应到人数**，向量长度应与活动次数相同
3. 接下来填写一个包含了 `n` 行数据的矩阵，我们称为**学生活动记录矩阵**，每一行表示一名学生，每一列表示一次活动
4. 对于矩阵中的每个数据，仅填写 `0 1 2` 三者中的一个，我们暂时钦定当前正在填入第 `i` 行第 `j` 列的数据
    1. 若填入 `0`，表示所在行的学生 `i` 没有参加所在列的活动 `j`
    2. 若填入 `1`，表示所在行的学生 `i` 正常参与所在列的活动 `j`
    3. 若填入 `2`，表示所在行的学生 `j` 对所在列的活动做出额外贡献，按**积分计算规则**[^2]应当额外加五分
5. 每个被输入数据后都应该紧跟一个制表符（`tab`）（即使后面有换行）
6. 具有不同含义的数据矩阵（或向量）之间应该使用空行分隔

## 注意事项

### 编译运行环境

- 产生程序的编译器使用的 C++ 标准为 C++14
- 程序发布的目标运行环境为 windows 操作系统（x86/x64）
- 若仓库内上传的程序无法正常运行，请尝试在本地重新编译或联系仓库所有者

### 读入程序鲁棒性

- 程序可正常抵抗包含多余空格、空行的输入
- 若输入数据格式不合法（例如输入的矩阵不具有统一的列数），程序将提示错误信息
- 输入数据仅接受数字 `0` 至 `9`、` `(space)、`\n`、`\t` 这十三种字符，其他输入将被判定为非法字符提示错误信息

### 开发人员注意事项

- 源代码所在文件夹为 `/sourcecodes/`
- 自定义的头文件位置为 `/sourcecodes/headfiles/`
- 程序由代码 `figure.cpp` 编译得到
- 若要查看程序给出的错误信息，请在终端内运行



[^1]: 输入数据填写规范详见后文。  
[^2]: 积分计算规则详见文件 `/积分计算规则.pdf`。
