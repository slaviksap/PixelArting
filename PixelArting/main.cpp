#include"BMP.h"
#include"GIF.h"
using namespace std;

int main()
{
	GIF gif;
	gif.blocksDataFile = "average_color_blocks_data.txt";
	gif.MCDirectory = "C:\\Users\\slavi\\AppData\\Roaming\\.minecraft\\saves\\Sphere test world\\datapacks\\My_datapack\\data\\gif\\functions";
	gif.createMCGIF("Images\\sonic.gif", 1450, 30, 630);
	cout << "Done!\n";
	return 0;
}