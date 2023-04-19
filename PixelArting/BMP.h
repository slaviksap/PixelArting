#pragma once
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include"glasses.h"

using namespace std;

#pragma pack(push,1)
struct BITMAPFILEHEADER
{
	unsigned char B;
	unsigned char M;
	unsigned int filesize;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int offset;
};
#pragma pack(pop)

#pragma pack(push,1)
struct BITMAPINFOHEADER
{
	unsigned int headersize;
	unsigned int width;
	unsigned int height;
	unsigned short colorPlanes;
	unsigned short bpp;
	unsigned int commpression;
	unsigned int imgSize;
	unsigned int horisontalresolution;
	unsigned int verticalresolution;
	unsigned int pltColors;
	unsigned int impColors;
};
#pragma pack(pop)

unsigned char roundoff(double x);

#pragma pack(push,1)
struct RGB
{
	unsigned char B;
	unsigned char G;
	unsigned char R;
	RGB(unsigned int r = 0, unsigned int g = 0, unsigned int b = 0);
	unsigned char max();
	friend RGB operator-(const RGB& left, const RGB& right)
	{
		RGB result;
		result.R = abs(left.R - right.R);
		result.G = abs(left.G - right.G);
		result.B = abs(left.B - right.B);
		return result;
	}
	friend RGB operator+(const RGB& left, const RGB& right)
	{
		RGB result;
		result.R = left.R + right.R;
		result.G = left.G + right.G;
		result.B = left.B + right.B;
		return result;
	}
	friend RGB operator*(const RGB& left, const float right)
	{
		RGB result;
		result.R = (unsigned short)(left.R * right);
		result.G = (unsigned short)(left.G * right);
		result.B = (unsigned short)(left.B * right);
		return result;
	}
	friend bool operator!=(const RGB& left, const RGB& right)
	{
		if (left.R == right.R && left.G == right.G && left.B == right.B)
			return false;
		return true;
	}
	friend bool operator==(const RGB& left, const RGB& right)
	{
		return !(left != right);
	}
	void read_from_file(ifstream& file);
	void write_to_file(ofstream& file);
	friend bool almost_equal(const RGB& left, const RGB& right, unsigned char accur);
	friend int distance(const RGB& left, const RGB& right);
	void read(ifstream& file);
};
#pragma pack(pop)

class Block
{
public:
	RGB block[16][16];

	RGB get(int i, int j) const;
	void set(int i, int j, unsigned short value);
	friend bool operator==(const Block& left, const Block& right)
	{
		for (int i = 0; i <= 15; ++i)
		{
			for (int j = 0; j <= 15; ++j)
			{
				if (left.get(i, j) != right.get(i, j))
					return false;
			}
		}
		return true;
	}
	void read_from_file(ifstream& file);
	void read(ifstream& file);
	void write_to_file(ofstream& file);
	void print();
	friend bool almost_equal(const Block& left, const Block& right, unsigned char accur);
	friend int distance(const Block& left, const Block& right);
	RGB medium_color();
};

class Art_element
{
public:
	char block_name[40];
	char glass_name[40] = "none";
	Block block;
public:
	void write(ofstream& file);
	void add_glass(Glass& glass);
};

void load_base_blocks_from_image();
void show_elements();
void write_combined_block(Art_element element, Glass& glass, ofstream& file);
void load_blocks(ifstream& file, vector<Art_element>& array);
void create_combinations();
void test_setup();
void art_from_pixelstacker_image();
void art_from_image();