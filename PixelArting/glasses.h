#pragma once

#include<string>
#include <iostream>
#include<fstream>
using namespace std;
class RGBA
{
public:
	unsigned char B;
	unsigned char G;
	unsigned char R;
	unsigned char A;
	void set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		R = r;
		G = g;
		B = b;
		A = a;
	}
};
class Glass
{
public:
	string glass_name;
	RGBA block[16][16];
};
enum Glass_types
{
	WHITE, ORANGE, MAGENTA, LIGHT_BLUE, YELLOW,
	LIME, PINK, GRAY, LIGHT_GRAY, CYAN, PURPLE,
	BLUE, BROWN, GREEN, RED, BLACK,CLEAR, TONED
};
class All_glasses
{
public:
	Glass glasses[18];
public:
	All_glasses();
};