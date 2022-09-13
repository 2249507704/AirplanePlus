#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<conio.h> //_kbhit
#include<windows.h> // Sleep gotoxy
#include<iostream>
#include<graphics.h>
using namespace std;
#define high 20                     // 画面高
#define width 50                    // 画面宽
#define NUM 3                       // 敌人数量
int color(int c);                   // 给字体颜色
void gotoxy();                      // 光标移动函数 在指定位置打印东西
void HideCursor();                  // 隐藏光标
void explation();                   // 游戏提升
void welcometogame();               // 开始界面
void scoreandtips();                // 游戏侧边提示
void startup();                     // 初始化函数
void show();                        // 画飞机、子弹等的函数
void updateWithoutInput();          // 和输入无关的更新函数
void updateWithInput();             // 和用户输入有关的函数
void Pause();                       // 暂停函数
