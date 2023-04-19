#pragma once
#include"BMP.h"
#include <map>
using namespace std;
#pragma pack(push,1)
class Byte
{
public:
	unsigned char byte;

	Byte();
	void setBit1(unsigned char number);
	void setBit0(unsigned char number);
	void setBit(bool bit, unsigned char number);
	bool getBit(int number);
	friend bool operator==(const Byte& left, const unsigned char& right)
	{
		return left.byte == right;
	}
	friend bool operator==(const unsigned char& left, const Byte& right)
	{
		return right.byte == left;
	}
};
#pragma pack(pop)

class GIF
{
#pragma pack(push,1)
	struct DataSubBlock
	{
		Byte blockSize;
		Byte dataValues[256];
		void read(ifstream& file);
	};
#pragma pack(pop)

#pragma pack(push,1)
	struct Header
	{
		Byte signateure[3];
		Byte version[3];

		void read(ifstream& file);
	};
#pragma pack(pop)

#pragma pack(push,1)
	struct LogicalScreenDescriptor
	{
		unsigned short LSwidth;
		unsigned short LSheight;
		Byte packedFields;
		Byte backgroundColorIndex;
		Byte PixelAspectRatio;

		bool bGlobalColorTable();
		unsigned char globalColorTableSize();
		void read(ifstream &file);
	};
#pragma pack(pop)

#pragma pack(push,1)
	struct GlobalColorTable
	{
		RGB table[256];
		int size;
		void printTable();
		void read(ifstream& file, LogicalScreenDescriptor& LSD);
		RGB operator[](int index)
		{
			return table[index];
		}
	};
#pragma pack(pop)

#pragma pack(push,1)
	struct ImageDescriptor
	{
		unsigned short imageLeftPosition;
		unsigned short imageTopPosition;
		unsigned short imageWidth;
		unsigned short imageHeight;
		Byte packedFields;

		bool bLocalColorTable();
		unsigned char localColorTableSize();
		void read(ifstream& file);
		unsigned short GetImageWidth();
		unsigned short GetImageHeight();
	};
#pragma pack(pop)

#pragma pack(push,1)
	struct GraphicControlExtension
	{
		Byte blockSize;
		Byte packedFiles;
		unsigned short delayTime;
		Byte transperentColorIndex;
		Byte blockTerminator;

		void read(ifstream& file);
		unsigned short getDelayTime();
	};
#pragma pack(pop)

#pragma pack(push,1)
	struct CommentExtension
	{
		vector<DataSubBlock> commentData;
		Byte blockTerminator;

		void read(ifstream& file);
	};
#pragma pack(pop)
#pragma pack(push,1)
	struct PlainTextExtension
	{
		Byte blockSize;
		unsigned short textGridLeftPosition;
		unsigned short textGridTopPosition;
		unsigned short textGridWidth;
		unsigned short textGridHeight;
		Byte characterCellWidth;
		Byte characterCellHeight;
		Byte textForegroundColorIndex;
		Byte textBackgroundColorIndex;
		vector<DataSubBlock> plainTextData;
		Byte blockTerminator;

		void read(ifstream& file);
	};
#pragma pack(pop)
#pragma pack(push,1)
	struct ApplicationExtension
	{
		Byte blockSize;
		Byte applicationIdentifier[8];
		Byte aplicationAuthenticationCode[3];
		vector<DataSubBlock> applicationData;
		Byte blockTerminator;

		void read(ifstream& file);
	};
#pragma pack(pop)

#pragma pack(push,1)
	struct LocalColorTable
	{
		RGB table[256];
		int size;
		void printTable();
		void read(ifstream& file, ImageDescriptor& imagedesc);
		RGB operator[](int index)
		{
			return table[index];
		}
	};
#pragma pack(pop)

	struct TableBasedImageData
	{
		Byte lzwMinimumCodeSize;
		vector<DataSubBlock> imageData;
		Byte blockTerminator;

		int curSubBlock = 0;
		unsigned char curByte = 0;
		unsigned char curBit = 0;
		void read(ifstream& file);

		unsigned short nextBits(unsigned char amount);

		bool is_exp_of_2(int n);

		void decrypt(vector<RGB>& image, GlobalColorTable& GCT);

		void decrypt(vector<RGB>& image, LocalColorTable& LCT);
	};

	

	struct DictionaryWord
	{
		vector<unsigned char> word;

		DictionaryWord(unsigned char letter);
		DictionaryWord();
		int size() const;
		friend DictionaryWord operator+(const DictionaryWord& left, const DictionaryWord& right)
		{
			DictionaryWord result;
			for (int i = 0; i < left.size(); ++i)
				result.word.push_back(left.word[i]);
			for (int i = 0; i < right.size(); ++i)
				result.word.push_back(right.word[i]);
			return result;
		}
		DictionaryWord firstLetter();
		void addToImage(vector<RGB>& image, GlobalColorTable& GCT);
		void addToImage(vector<RGB>& image, LocalColorTable& LCT);
	};

	struct Dictionary
	{
		map<int, DictionaryWord> dictionary;

		void initialize(GlobalColorTable& GCT);
		void initialize(LocalColorTable& GCT);
		bool add(int number, DictionaryWord& word);
	};

	Header header;
	LogicalScreenDescriptor LSD;
	GlobalColorTable GCT;
public:
	string blocksDataFile;
	string MCDirectory;
	void check(ifstream &file);
	void createMCGIF(string image, int x, int z, int y);
	void vectorInImage(vector<RGB>& prev, vector<RGB>& cur, int imageWidth, int imageHeight, int x, int z, int y, int imageNumber);
#pragma pack(pop)
};