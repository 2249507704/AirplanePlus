#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<conio.h> //_kbhit
#include<windows.h> // Sleep gotoxy
#include<iostream>
#include<graphics.h>
using namespace std;
#define high 20
#define width 50
#define NUM 3 
int color(int c);
void gotoxy();
void HideCursor();
void explation();
void welcometogame();
void scoreandtips();
void startup();
void show();
void updateWithoutInput();
void updateWithInput();
void Pause();              // ÔÝÍ£