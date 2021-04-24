# HUSTCS

![GitHub repo size](https://img.shields.io/github/repo-size/HUSTERGS/HUSTCS?style=flat-square)
![GitHub last commit](https://img.shields.io/github/last-commit/HUSTERGS/HUSTCS?style=flat-square)
![GitHub license](https://img.shields.io/github/license/HUSTERGS/HUSTCS?style=flat-square)

文件存留

可以使用[GitZip](http://kinolien.github.io/gitzip/)来下载单个文件/文件夹

**由于一些课程包含了老师提供的文档或者题目，若有侵权请联系删除**

## 文件列表
### 大一上:
- [C语言实验](https://github.com/HUSTERGS/HUSTCS/tree/master/C%E8%AF%AD%E8%A8%80%E5%AE%9E%E9%AA%8C)

### 大二上:
- [数据结构实验](https://github.com/HUSTERGS/HUSTCS/tree/master/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%AE%9E%E9%AA%8C)

### 大二下:
- [数据结构课设](https://github.com/HUSTERGS/HUSTCS/tree/master/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E8%AF%BE%E8%AE%BE)
- [汇编实验](https://github.com/HUSTERGS/HUSTCS/tree/master/%E6%B1%87%E7%BC%96)
- [数字逻辑实验](https://github.com/HUSTERGS/HUSTCS/tree/master/%E6%95%B0%E5%AD%97%E9%80%BB%E8%BE%91)
- [计算机系统基础实验](https://github.com/HUSTERGS/HUSTCS/tree/master/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%B3%BB%E7%BB%9F%E5%9F%BA%E7%A1%80)


### 大三上：
- [计算机组成原理实验](https://github.com/HUSTERGS/HUSTCS/tree/master/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BB%84%E6%88%90%E5%8E%9F%E7%90%86)
- [计算机操作系统实验](https://github.com/HUSTERGS/HUSTCS/tree/master/%E8%AE%A1%E7%AE%97%E6%9C%BA%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F%E5%AE%9E%E9%AA%8C)
- [大数据导论]([https://github.com/HUSTERGS/HUSTCS/tree/master/%E5%A4%A7%E6%95%B0%E6%8D%AE%E5%AF%BC%E8%AE%BA](https://github.com/HUSTERGS/HUSTCS/tree/master/大数据导论))
  * `大数据报告.docx`: 课程报告(删去了同组人员)
  > 基于之前[新加坡的暑期项目](https://github.com/Langford-tang/University-Logo-Deep-Learning-Community-Detection)，个人感觉参考价值不大
- [软件工程课设](https://github.com/HUSTERGS/SoftwareEngineeringProject/)
  * `2019《软件工程》项目任务书（2017级）.docx`: 任务书
  * `《软件工程》项目报告撰写内容及规范化参考样本.docx`: 报告样本
  * 项目链接: [数独App](https://github.com/HUSTERGS/SoftwareEngineeringProject)
  > 做的实在不太行，参考价值不大，没有提供报告，只有任务书以及报告样本
- [计算机网络实验](https://github.com/HUSTERGS/Computer_Network)

### 大三下：
- [函数式编程实验](https://github.com/HUSTERGS/SML_HUST)
- [Java实验](https://github.com/HUSTERGS/Java_HUST) (不含平时作业)
- [数据库系统原理实验](https://github.com/HUSTERGS/Database_HUST) (写的稀烂)
- [机器学习](https://github.com/HUSTERGS/ML_HUST/)
- [计算机组成原理课设](https://github.com/HUSTERGS/HUSTCS/tree/master/计算机组成原理课设)(没有完成后续流水中断以及动态分支预测)

### 大四上
- [系统能力综合训练-虚拟机-riscv](https://github.com/HUSTERGS/PA)

### 杂项

- [CSP Python题解](https://github.com/HUSTERGS/CSP)（部分）
- [华科相关常用网站列表以及简略介绍](https://github.com/HUSTERGS/HUSTCS/blob/master/网站列表.md)

----

### 关于子模块(git submodule)

一些内容使用submodule进行管理。有以下几个可选方式

- clone时就初始化所有的模块，获得所有内容

  在clone的时候增加`--recurse-submodules`选项

  ```sh
  git clone --recurse-submodules git@github.com:HUSTERGS/HUSTCS.git
  ```

- clone之后再初始化所有的模块

  ```sh
  git clone git@github.com:HUSTERGS/HUSTCS.git
  cd ./HUSTCS
  git submodule update --init
  ```

- clone后单独初始化某一个模块

  ```sh
  git clone git@github.com:HUSTERGS/HUSTCS.git
  cd ./HUSTCS
  git submodule update --init Java课程实验 # 此处以Java课程实验为例，其他submodule类似
  ```

- 直接访问子模块对应的仓库，clone或者下载即可

## 相关仓库

- [HUSTER-CS](https://github.com/AlexFanw/HUSTER-CS) [@AlexFanw](https://github.com/AlexFanw/)

- [awesome-hust](https://github.com/recolic/awesome-hust) [@recolic ](https://github.com/recolic/) (强烈推荐)

- [HUST-Homeworks](https://github.com/husixu1/HUST-Homeworks) [@husixu1](https://github.com/husixu1)

