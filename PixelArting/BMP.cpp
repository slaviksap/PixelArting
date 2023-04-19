#include "BMP.h"

unsigned char roundoff(double x)
{
	unsigned char int_part = (unsigned char)x;
	if (x - int_part >= 0.5)
		return int_part + 1;
	else return int_part;
}

bool almost_equal(const RGB& left, const RGB& right, unsigned char accur)
{
	if (abs((int)left.R - (int)right.R) > accur)
		return false;
	if (abs((int)left.G - (int)right.G) > accur)
		return false;
	if (abs((int)left.B - (int)right.B) > accur)
		return false;
	return true;
}

int distance(const RGB& left, const RGB& right)
{
	return (left.R - right.R) * (left.R - right.R) + (left.G - right.G) * (left.G - right.G) + (left.B - right.B) * (left.B - right.B);
}

bool almost_equal(const Block& left, const Block& right, unsigned char accur)
{
	for (int i = 0; i <= 15; ++i)
		for (int j = 0; j <= 15; ++j)
		{
			if (!almost_equal(left.get(i, j), right.get(i, j), accur))
				return false;
		}
	return true;
}

int distance(const Block& left, const Block& right)
{
	int res = 0;
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			res += distance(left.block[i][j], right.block[i][j]);
		}
	}
	return res;
}

void load_base_blocks_from_image()
{
	ifstream data;
	ofstream base_blocks_data;
	//ifstream blocks_names;
	data.open("data.bmp", ios::binary);
	base_blocks_data.open("base_blocks_data.txt", ios::binary);
	//blocks_names.open("blocks_data.txt");
	BITMAPFILEHEADER head;
	BITMAPINFOHEADER info;
	data.read((char*)(&head), sizeof(BITMAPFILEHEADER));
	data.read((char*)(&info), sizeof(BITMAPINFOHEADER));
	data.seekg(-2, ios::cur);
	while (!data.eof())
	{
		Art_element element;
		element.block.read(data);
		if (data.eof())
			break;
		cout << "Enter block name\n";
		cin >> element.block_name;
		element.write(base_blocks_data);
	}
	data.close();
	base_blocks_data.close();
}

void show_elements()
{
	ifstream data;
	data.open("combined_blocks_data.txt", ios::binary);
	ofstream average_data;
	average_data.open("average_color_blocks_data.txt", ios::binary);
	while (!data.eof())
	{
		Art_element element;
		data.read((char*)(&element), sizeof(element));
		if (data.eof())
			break;
		if (strcmp(element.glass_name, "none") != 0 && strcmp(element.glass_name, "glass") != 0)
		{
			average_data.write(element.block_name, sizeof(element.block_name));
			average_data.write(element.glass_name, sizeof(element.glass_name));
			RGB rgb = element.block.medium_color();
			average_data.write((char*)&rgb, sizeof(RGB));
		}
	}
	data.close();
}

void write_combined_block(Art_element element, Glass& glass, ofstream& file)
{
	element.add_glass(glass);
	element.write(file);
}

void load_blocks(ifstream& file, vector<Art_element>& array)
{
	while (!file.eof())
	{
		Art_element element;
		file.read((char*)(&element), sizeof(element));
		if (file.eof())
			break;
		array.push_back(element);
	}
}

void create_combinations()
{
	All_glasses glasses;
	ofstream all_blocks;
	all_blocks.open("combined_blocks_data.txt", ios::binary);
	ifstream base_blocks;
	base_blocks.open("base_blocks_data.txt", ios::binary);
	vector<Art_element> array;
	load_blocks(base_blocks, array);
	int counter = 0;
	for (auto iter = array.begin(); iter != array.end(); iter++)
	{
		iter->write(all_blocks);
		for (int glass_type = Glass_types::WHITE; glass_type <= Glass_types::CLEAR; ++glass_type)
		{
			write_combined_block(*iter, glasses.glasses[glass_type], all_blocks);
		}
		++counter;
		cout << counter << endl;
	}
	all_blocks.close();
	base_blocks.close();
}

void test_setup()
{
	ifstream data;
	data.open("combined_blocks_data.txt", ios::binary);
	ofstream mcfunction;
	mcfunction.open("C:\\Users\\slavi\\AppData\\Roaming\\.minecraft\\saves\\Sphere test world\\datapacks\\My_datapack\\data\\custom\\functions\\test_paliter.mcfunction");
	vector<Art_element> array;
	load_blocks(data, array);
	int counter = 0;
	int xpos = 0;
	int zpos = 10;
	int ypos = 0;
	for (auto iter = array.begin(); iter != array.end(); iter++)
	{
		mcfunction << "setblock " + to_string(xpos) + " " + to_string(zpos) + " " + to_string(ypos) + " minecraft:" + iter->block_name << endl;
		if (strcmp(iter->glass_name, "none") != 0)
		{
			mcfunction << "setblock " + to_string(xpos) + " " + to_string(zpos + 1) + " " + to_string(ypos) + " minecraft:" + iter->glass_name << endl;
		}
		++ypos;
		if (ypos == 18)
		{
			ypos = 0;
			++xpos;
		}
	}
}

void art_from_pixelstacker_image()
{
	ifstream image;
	ofstream mcfunction;
	ifstream data;
	image.open("Images\\shrek.bmp", ios::binary);
	mcfunction.open("C:\\Users\\slavi\\AppData\\Roaming\\.minecraft\\saves\\Sphere test world\\datapacks\\My_datapack\\data\\custom\\functions\\shrek_art.mcfunction");
	data.open("combined_blocks_data.txt", ios::binary);
	BITMAPFILEHEADER head;
	BITMAPINFOHEADER info;
	image.read((char*)(&head), sizeof(BITMAPFILEHEADER));
	image.read((char*)(&info), sizeof(BITMAPINFOHEADER));
	vector <Art_element> array;
	load_blocks(data, array);
	int width = info.width;
	int height = info.height;
	int base_xpos = 500;
	int base_ypos = 500;
	int xpos = base_xpos;
	int zpos = 24;
	int ypos = base_ypos;
	int strings_counter = 0;
	while (!image.eof())
	{
		xpos = base_xpos;
		vector <RGB> pixels;
		//читываем строку толщиной 16 пикселей
		for (int counter = 0; counter < 16 * width; ++counter)
		{
			RGB rgb;
			image.read((char*)&rgb, sizeof(RGB));
			if (image.eof())
				break;
			pixels.push_back(rgb);
		}

		//образуем и вписываем в арт пиксель
		for (int count = 0; count < width / 16; ++count)
		{
			//создаем блок пикселей
			Block block;
			for (int i = 0; i <= 15; ++i)
			{
				for (int j = 0; j <= 15; ++j)
				{
					block.block[i][j] = pixels[i * width + 16 * count + j];
				}
			}
			//ищем похожий элемент
			auto iter = array.begin();
			int max_dist = INT_MAX;
			auto dist_iter = iter;
			while (iter != array.end())
			{
				if (almost_equal(iter->block, block, 2))
				{
					int dist = distance(iter->block, block);
					if (dist < max_dist)
					{
						max_dist = dist;
						dist_iter = iter;
					}
				}
				iter++;
			}
			if (max_dist != INT_MAX)
			{
				mcfunction << "setblock " + to_string(xpos) + " " + to_string(zpos) + " " + to_string(ypos) + " minecraft:" + dist_iter->block_name << endl;
				++strings_counter;
				if (strcmp(dist_iter->glass_name, "none") != 0)
				{
					mcfunction << "setblock " + to_string(xpos) + " " + to_string(zpos + 1) + " " + to_string(ypos) + " minecraft:" + dist_iter->glass_name << endl;
					++strings_counter;
				}
			}
			++xpos;
		}
		--ypos;
	}

	image.close();
	mcfunction.close();
}

void art_from_image()
{
	ifstream image;
	ofstream mcfunction;
	ifstream data;
	image.open("Images\\shrek2.bmp", ios::binary);
	mcfunction.open("C:\\Users\\slavi\\AppData\\Roaming\\.minecraft\\saves\\Sphere test world\\datapacks\\My_datapack\\data\\custom\\functions\\shrek2_art.mcfunction");
	data.open("average_color_blocks_data.txt", ios::binary);
	BITMAPFILEHEADER head;
	BITMAPINFOHEADER info;
	image.read((char*)(&head), sizeof(BITMAPFILEHEADER));
	image.read((char*)(&info), sizeof(BITMAPINFOHEADER));
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
	int width = info.width;
	int height = info.height;
	int base_xpos = 860;
	int base_ypos = 560;
	int xpos = base_xpos;
	int zpos = 24;
	int ypos = base_ypos;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			RGB pixel;
			image.read((char*)&pixel, sizeof(RGB));
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
			if (max_dist != INT_MAX)
			{
				mcfunction << "setblock " + to_string(xpos + j) + " " + to_string(zpos + i) + " " + to_string(ypos) + " minecraft:" + dist_iter->block_name << endl;
				if (strcmp(dist_iter->glass_name, "none") != 0)
				{
					mcfunction << "setblock " + to_string(xpos + j) + " " + to_string(zpos + i) + " " + to_string(ypos + 1) + " minecraft:" + dist_iter->glass_name << endl;
				}
			}
		}
		if ((width * 3) % 4 != 0)
		{
			for (int offset = 1; offset <= 4 - (width * 3) % 4; ++offset)
			{
				char liter;
				image.read((char*)&liter, sizeof(char));
			}
		}
	}

	image.close();
	mcfunction.close();
}

RGB::RGB(unsigned int r, unsigned int g, unsigned int b)
{
	R = r;
	G = g;
	B = b;
}

unsigned char RGB::max()
{
	if (R > G)
	{
		if (R > B)
			return R;
		else return B;
	}
	else if (G > B)
		return G;
	else return B;
}

void RGB::read_from_file(ifstream& file)
{
	file >> R;
	file >> G;
	file >> B;
}

void RGB::write_to_file(ofstream& file)
{
	file << R << G << B;
}

inline void RGB::read(ifstream& file)
{
	file.read((char*)&R, sizeof(unsigned char));
	file.read((char*)&G, sizeof(unsigned char));
	file.read((char*)&B, sizeof(unsigned char));
}

inline RGB Block::get(int i, int j) const
{
	return block[i][j];
}

inline void Block::set(int i, int j, unsigned short value)
{
	block[i][j] = value;
}

void Block::read_from_file(ifstream& file)
{
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			block[i][j].read_from_file(file);
		}
	}
}

void Block::read(ifstream& file)
{
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			file.read((char*)&block[i][j], sizeof(RGB));
		}
	}
}

void Block::write_to_file(ofstream& file)
{
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			block[i][j].write_to_file(file);
		}
	}
}

void Block::print()
{
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			cout << (int)block[i][j].R << " " << (int)block[i][j].G << " " << (int)block[i][j].B << endl;
		}
	}
}

RGB Block::medium_color()
{
	int s_R = 0, s_G = 0, s_B = 0;
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			s_R += block[i][j].R;
			s_G += block[i][j].G;
			s_B += block[i][j].B;
		}
	}
	return RGB(roundoff(s_R / 256.0), roundoff(s_G / 256.0), roundoff(s_B / 256.0));
}

void Art_element::write(ofstream& file)
{
	file.write(block_name, sizeof(block_name));
	file.write(glass_name, sizeof(glass_name));
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			file.write((char*)&block.block[i][j], sizeof(RGB));
		}
	}
}

void Art_element::add_glass(Glass& glass)
{
	strcpy_s(glass_name, glass.glass_name.c_str());
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			RGB D = block.block[i][j];
			RGBA S = glass.block[i][j];
			block.block[i][j].R = roundoff(S.R * (S.A / 255.0) + D.R * (1 - S.A / 255.0));
			block.block[i][j].G = roundoff(S.G * (S.A / 255.0) + D.G * (1 - S.A / 255.0));
			block.block[i][j].B = roundoff(S.B * (S.A / 255.0) + D.B * (1 - S.A / 255.0));
		}
	}
}
