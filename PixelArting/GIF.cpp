#include "GIF.h"

inline Byte::Byte()
{
	byte = 0;
}

inline void Byte::setBit1(unsigned char number)
{
	byte |= (1 << number);
}

inline void Byte::setBit0(unsigned char number)
{
	byte &= ~(1 << number);
}

inline void Byte::setBit(bool bit, unsigned char number)
{
	if (bit == 0)
		setBit0(number);
	else setBit1(number);
}

inline bool Byte::getBit(int number)
{
	return (bool((1 << number) & byte));
}

inline void GIF::DataSubBlock::read(ifstream& file)
{
	file.read((char*)&blockSize, sizeof(blockSize));
	file.read((char*)&dataValues, blockSize.byte * sizeof(Byte));
}

inline void GIF::Header::read(ifstream& file)
{
	file.read((char*)signateure, sizeof(signateure));
	file.read((char*)version, sizeof(version));
}

inline bool GIF::LogicalScreenDescriptor::bGlobalColorTable()
{
	return packedFields.getBit(7);
}

inline unsigned char GIF::LogicalScreenDescriptor::globalColorTableSize()
{
	return (packedFields.byte & 0x07);
}

inline void GIF::LogicalScreenDescriptor::read(ifstream& file)
{
	file.read((char*)this, sizeof(LogicalScreenDescriptor));
}

void GIF::GlobalColorTable::printTable()
{
	for (int i = 0; i <= 255; ++i)
	{
		cout << (int)table[i].R << "\t" << (int)table[i].G << "\t" << (int)table[i].B << endl;
	}
}

void GIF::GlobalColorTable::read(ifstream& file, LogicalScreenDescriptor& LSD)
{
	if (LSD.bGlobalColorTable())
	{
		size = (int)pow(2, LSD.globalColorTableSize() + 1);
		for (int count = 0; count < size; ++count)
			table[count].read(file);
	}
}

inline bool GIF::ImageDescriptor::bLocalColorTable()
{
	return packedFields.getBit(7);
}

inline unsigned char GIF::ImageDescriptor::localColorTableSize()
{
	return (packedFields.byte & 0x07);
}

inline void GIF::ImageDescriptor::read(ifstream& file)
{
	file.read((char*)this, sizeof(ImageDescriptor));
}

inline unsigned short GIF::ImageDescriptor::GetImageWidth()
{
	return imageWidth;
}

inline unsigned short GIF::ImageDescriptor::GetImageHeight()
{
	return imageHeight;
}

inline void GIF::GraphicControlExtension::read(ifstream& file)
{
	file.read((char*)this, sizeof(GraphicControlExtension));
}

inline unsigned short GIF::GraphicControlExtension::getDelayTime()
{
	return delayTime;
}

void GIF::CommentExtension::read(ifstream& file)
{
	while (1)
	{
		file.read((char*)&blockTerminator, sizeof(Byte));
		if (blockTerminator == 0x00)
			break;
		DataSubBlock subBlock;
		subBlock.blockSize = blockTerminator;
		file.read((char*)&subBlock.dataValues, subBlock.blockSize.byte * sizeof(Byte));
		commentData.push_back(subBlock);
	}

}

void GIF::PlainTextExtension::read(ifstream& file)
{
	file.read((char*)&blockSize, sizeof(blockSize));
	file.read((char*)&textGridLeftPosition, sizeof(textGridLeftPosition));
	file.read((char*)&textGridTopPosition, sizeof(textGridTopPosition));
	file.read((char*)&textGridWidth, sizeof(textGridWidth));
	file.read((char*)&textGridHeight, sizeof(textGridHeight));
	file.read((char*)&characterCellWidth, sizeof(characterCellWidth));
	file.read((char*)&characterCellHeight, sizeof(characterCellHeight));
	file.read((char*)&textForegroundColorIndex, sizeof(textForegroundColorIndex));
	file.read((char*)&textBackgroundColorIndex, sizeof(textBackgroundColorIndex));
	while (1)
	{
		file.read((char*)&blockTerminator, sizeof(Byte));
		if (blockTerminator == 0x00)
			break;
		DataSubBlock subBlock;
		subBlock.blockSize = blockTerminator;
		file.read((char*)&subBlock.dataValues, subBlock.blockSize.byte * sizeof(Byte));
		plainTextData.push_back(subBlock);
	}
}

void GIF::ApplicationExtension::read(ifstream& file)
{
	file.read((char*)&blockSize, sizeof(blockSize));
	file.read((char*)&applicationIdentifier, sizeof(applicationIdentifier));
	file.read((char*)&aplicationAuthenticationCode, sizeof(aplicationAuthenticationCode));
	while (1)
	{
		file.read((char*)&blockTerminator, sizeof(Byte));
		if (blockTerminator == 0x00)
			break;
		DataSubBlock subBlock;
		subBlock.blockSize = blockTerminator;
		file.read((char*)&subBlock.dataValues, subBlock.blockSize.byte * sizeof(Byte));
		applicationData.push_back(subBlock);
	}
}

void GIF::LocalColorTable::printTable()
{
	for (int i = 0; i <= 255; ++i)
	{
		cout << (int)table[i].R << "\t" << (int)table[i].G << "\t" << (int)table[i].B << endl;
	}
}

void GIF::LocalColorTable::read(ifstream& file, ImageDescriptor& imagedesc)
{
	if (imagedesc.bLocalColorTable())
	{
		size = (int)pow(2, imagedesc.localColorTableSize() + 1);
		for (int count = 0; count < size; ++count)
			table[count].read(file);
	}
}

void GIF::TableBasedImageData::read(ifstream& file)
{
	file.read((char*)&lzwMinimumCodeSize, sizeof(Byte));
	while (1)
	{
		file.read((char*)&blockTerminator, sizeof(Byte));
		if (blockTerminator == 0x00)
			break;
		DataSubBlock subBlock;
		subBlock.blockSize = blockTerminator;
		file.read((char*)&subBlock.dataValues, subBlock.blockSize.byte * sizeof(Byte));
		imageData.push_back(subBlock);
	}
}

unsigned short GIF::TableBasedImageData::nextBits(unsigned char amount)
{
	unsigned short result;
	Byte Byte1;
	Byte Byte2;
	for (unsigned char bit = 0; bit < amount; ++bit)
	{
		if (bit <= 7)
		{
			Byte1.setBit(imageData[curSubBlock].dataValues[curByte].getBit(curBit), bit);
			if (curBit == 7)
			{
				curBit = 0;
				if (curByte == imageData[curSubBlock].blockSize.byte - 1)
				{
					curByte = 0;
					++curSubBlock;
				}
				else ++curByte;
			}
			else ++curBit;
		}
		else
		{
			Byte2.setBit(imageData[curSubBlock].dataValues[curByte].getBit(curBit), bit - 8);
			if (curBit == 7)
			{
				curBit = 0;
				if (curByte == imageData[curSubBlock].blockSize.byte - 1)
				{
					curByte = 0;
					++curSubBlock;
				}
				else ++curByte;
			}
			else ++curBit;
		}
	}
	result = Byte1.byte + 256 * Byte2.byte;
	return result;
}

inline bool GIF::TableBasedImageData::is_exp_of_2(int n)
{
	return (n & (n - 1)) == 0;
}

void GIF::TableBasedImageData::decrypt(vector<RGB>& image, GlobalColorTable& GCT)
{
	Dictionary dictionary;
	dictionary.initialize(GCT);
	unsigned short clear = GCT.size;
	unsigned short end = GCT.size + 1;
	int blockLength = lzwMinimumCodeSize.byte + 1;
	int index = GCT.size + 2;
	DictionaryWord curWord;
	DictionaryWord lastWord;
	bool firstLetter = true;
	while (1)
	{
		unsigned short block = nextBits(blockLength);
		//cout << block << endl;
		if (block == clear)
		{
			dictionary.initialize(GCT);
			blockLength = lzwMinimumCodeSize.byte + 1;
			index = GCT.size + 2;
			lastWord.word.clear();
			firstLetter = true;
			continue;
		}
		else if (block == end)
			break;

		if (!firstLetter)
		{
			auto iter = dictionary.dictionary.find(block);
			if (iter != dictionary.dictionary.end())
			{
				curWord = iter->second;
				curWord.addToImage(image, GCT);
				DictionaryWord newWord = lastWord + curWord.firstLetter();
				while (!dictionary.add(index, newWord))
					++index;
				++index;
			}
			else
			{
				DictionaryWord newWord = lastWord + lastWord.firstLetter();
				while (!dictionary.add(index, newWord))
					++index;
				++index;
				curWord = newWord;
				newWord.addToImage(image, GCT);
			}

		}
		else
		{
			curWord = dictionary.dictionary.find(block)->second;
			curWord.addToImage(image, GCT);
			firstLetter = false;
		}
		lastWord = curWord;
		if (is_exp_of_2(dictionary.dictionary.size()))
			++blockLength;
	}
}

void GIF::TableBasedImageData::decrypt(vector<RGB>& image, LocalColorTable& LCT)
{
	Dictionary dictionary;
	dictionary.initialize(LCT);
	unsigned short clear = LCT.size;
	unsigned short end = LCT.size + 1;
	int blockLength = lzwMinimumCodeSize.byte + 1;
	int index = LCT.size + 2;
	DictionaryWord curWord;
	DictionaryWord lastWord;
	bool firstLetter = true;
	while (1)
	{
		unsigned short block = nextBits(blockLength);
		//cout << block << endl;
		if (block == clear)
		{
			dictionary.initialize(LCT);
			blockLength = lzwMinimumCodeSize.byte + 1;
			index = LCT.size + 2;
			lastWord.word.clear();
			firstLetter = true;
			continue;
		}
		else if (block == end)
			break;

		if (!firstLetter)
		{
			auto iter = dictionary.dictionary.find(block);
			if (iter != dictionary.dictionary.end())
			{
				curWord = iter->second;
				curWord.addToImage(image, LCT);
				DictionaryWord newWord = lastWord + curWord.firstLetter();
				while (!dictionary.add(index, newWord))
					++index;
				++index;
			}
			else
			{
				DictionaryWord newWord = lastWord + lastWord.firstLetter();
				while (!dictionary.add(index, newWord))
					++index;
				++index;
				curWord = newWord;
				newWord.addToImage(image, LCT);
			}

		}
		else
		{
			curWord = dictionary.dictionary.find(block)->second;
			curWord.addToImage(image, LCT);
			firstLetter = false;
		}
		lastWord = curWord;
		if (is_exp_of_2(dictionary.dictionary.size()))
			++blockLength;
	}
}

inline GIF::DictionaryWord::DictionaryWord(unsigned char letter)
{
	word.push_back(letter);
}

inline GIF::DictionaryWord::DictionaryWord()
{

}

inline int GIF::DictionaryWord::size() const
{
	return word.size();
}

inline GIF::DictionaryWord GIF::DictionaryWord::firstLetter()
{
	return DictionaryWord(word[0]);
}

void GIF::DictionaryWord::addToImage(vector<RGB>& image, GlobalColorTable& GCT)
{
	for (unsigned char letter : word)
	{
		image.push_back(GCT[letter]);
	}
}

void GIF::DictionaryWord::addToImage(vector<RGB>& image, LocalColorTable& LCT)
{
	for (unsigned char letter : word)
	{
		image.push_back(LCT[letter]);
	}
}

void GIF::Dictionary::initialize(GlobalColorTable& GCT)
{
	dictionary.clear();
	for (int i = 0; i < GCT.size; ++i)
	{
		dictionary.insert({ i, DictionaryWord(i) });
	}
	dictionary.insert({ GCT.size, DictionaryWord() });
	dictionary.insert({ GCT.size + 1, DictionaryWord() });
}

void GIF::Dictionary::initialize(LocalColorTable& GCT)
{
	dictionary.clear();
	for (int i = 0; i < GCT.size; ++i)
	{
		dictionary.insert({ i, DictionaryWord(i) });
	}
	dictionary.insert({ GCT.size, DictionaryWord() });
	dictionary.insert({ GCT.size + 1, DictionaryWord() });
}

inline bool GIF::Dictionary::add(int number, DictionaryWord& word)
{
	return dictionary.insert({ number, word }).second;
}

void GIF::check(ifstream& file)
{
	header.read(file);
	cout << "Header\n";
	LSD.read(file);
	cout << "LogicalScreenDescriptor\n";
	GCT.read(file, LSD);
	cout << "GlobalColorTable\n";
	cout << GCT.size << endl;
	bool GIFover = false;
	while (!GIFover)
	{
		Byte blockType;
		file.read((char*)&blockType, sizeof(Byte));
		if (blockType == 0x2C)
		{
			ImageDescriptor imageDesc;
			imageDesc.read(file);
			cout << "ImageDescriptor\n";
			LocalColorTable LCT;
			if (imageDesc.bLocalColorTable())
				cout << "LocalColorTable\n";
			LCT.read(file, imageDesc);
			TableBasedImageData imageData;
			imageData.read(file);
			cout << "TableBasedImageData\n";
			vector<RGB> pixels;
			imageData.decrypt(pixels, GCT);
			cout << pixels.size() << "\t" << imageDesc.imageWidth * imageDesc.imageHeight << endl;

		}
		else if (blockType == 0x21)
		{
			Byte extensionType;
			file.read((char*)&extensionType, sizeof(Byte));
			if (extensionType == 0xF9)
			{
				GraphicControlExtension GCExtension;
				GCExtension.read(file);
				cout << "GraphicControlExtension\n";
			}
			else if (extensionType == 0xFE)
			{
				CommentExtension CExtension;
				CExtension.read(file);
				cout << "CommentExtension\n";
			}
			else if (extensionType == 0x01)
			{
				PlainTextExtension PTExtension;
				PTExtension.read(file);
				cout << "PlainTextExtension\n";
			}
			else if (extensionType == 0xFF)
			{
				ApplicationExtension AppExtension;
				AppExtension.read(file);
				cout << "ApplicationExtension\n";
			}
		}
		else if (blockType == 0x3B)
		{
			GIFover = true;
			cout << "Trailer\n";
		}
	}
}

void GIF::createMCGIF(string image, int x, int z, int y)
{
	vector<RGB> previousImage;
	vector<RGB> curImage;
	int imageNumber = 0;
	ifstream file;
	file.open(image, ios::binary);
	header.read(file);
	LSD.read(file);
	GCT.read(file, LSD);
	bool GIFover = false;
	while (!GIFover)
	{
		Byte blockType;
		file.read((char*)&blockType, sizeof(Byte));
		if (blockType == 0x2C)
		{
			++imageNumber;
			ImageDescriptor imageDesc;
			imageDesc.read(file);
			LocalColorTable LCT;
			LCT.read(file, imageDesc);
			TableBasedImageData imageData;
			imageData.read(file);
			curImage.clear();
			if (imageDesc.bLocalColorTable())
			{
				imageData.decrypt(curImage, LCT);
				cout << "local\n";
			}
			else
				imageData.decrypt(curImage, GCT);
			vectorInImage(previousImage, curImage, imageDesc.imageWidth, imageDesc.imageHeight, x, z, y, imageNumber);
			previousImage = curImage;
			cout << imageNumber;

		}
		else if (blockType == 0x21)
		{
			Byte extensionType;
			file.read((char*)&extensionType, sizeof(Byte));
			if (extensionType == 0xF9)
			{
				GraphicControlExtension GCExtension;
				GCExtension.read(file);
			}
			else if (extensionType == 0xFE)
			{
				CommentExtension CExtension;
				CExtension.read(file);
			}
			else if (extensionType == 0x01)
			{
				PlainTextExtension PTExtension;
				PTExtension.read(file);
			}
			else if (extensionType == 0xFF)
			{
				ApplicationExtension AppExtension;
				AppExtension.read(file);
			}
		}
		else if (blockType == 0x3B)
		{
			GIFover = true;
		}
	}
}

void GIF::vectorInImage(vector<RGB>& prev, vector<RGB>& cur, int imageWidth, int imageHeight, int x, int z, int y, int imageNumber)
{
	ofstream mcfunction;
	ifstream  data;
	data.open(blocksDataFile, ios::binary);
	if (imageNumber == 1)
		mcfunction.open(MCDirectory + "\\gif.mcfunction");
	else
		mcfunction.open(MCDirectory + "\\gif" + to_string(imageNumber) + ".mcfunction");
	struct Average_element
	{
	public:
		char block_name[40];
		char glass_name[40];
		RGB average_color;
	};
	vector<Average_element> array;
	while (!data.eof())
	{
		Average_element element;
		data.read((char*)(&element), sizeof(element));
		if (data.eof())
			break;
		array.push_back(element);
	}
	if (prev.empty())
	{
		for (int i = 0; i < imageHeight; ++i)
		{
			for (int j = 0; j < imageWidth; ++j)
			{
				RGB pixel = cur[i * imageWidth + j];
				auto iter = array.begin();
				int max_dist = INT_MAX;
				auto dist_iter = iter;
				while (iter != array.end())
				{
					int dist = distance(iter->average_color, pixel);
					if (dist < max_dist)
					{
						max_dist = dist;
						dist_iter = iter;
					}
					iter++;
				}
				mcfunction << "setblock " + to_string(x + i) + " " + to_string(z) + " " + to_string(y + j) + " minecraft:" + dist_iter->block_name << endl;
				if (strcmp(dist_iter->glass_name, "none") != 0)
				{
					mcfunction << "setblock " + to_string(x + i) + " " + to_string(z + 1) + " " + to_string(y + j) + " minecraft:" + dist_iter->glass_name << endl;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < imageHeight; ++i)
		{
			for (int j = 0; j < imageWidth; ++j)
			{
				if (cur[i * imageWidth + j] == prev[i * imageWidth + j])
					continue;
				RGB pixel = cur[i * imageWidth + j];
				auto iter = array.begin();
				int max_dist = INT_MAX;
				auto dist_iter = iter;
				while (iter != array.end())
				{
					int dist = distance(iter->average_color, pixel);
					if (dist < max_dist)
					{
						max_dist = dist;
						dist_iter = iter;
					}
					iter++;
				}
				mcfunction << "setblock " + to_string(x + i) + " " + to_string(z) + " " + to_string(y + j) + " minecraft:" + dist_iter->block_name << endl;
				if (strcmp(dist_iter->glass_name, "none") != 0)
				{
					mcfunction << "setblock " + to_string(x + i) + " " + to_string(z + 1) + " " + to_string(y + j) + " minecraft:" + dist_iter->glass_name << endl;
				}
			}
		}
	}
}
