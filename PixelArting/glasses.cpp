#include "glasses.h"

All_glasses::All_glasses()
{
	//белое стекло
	glasses[Glass_types::WHITE].glass_name = "white_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::WHITE].block[i][j].set(255, 255, 255, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::WHITE].block[i][j].set(255, 255, 255, 155);
			}
			else
			{
				glasses[Glass_types::WHITE].block[i][j].set(255, 255, 255, 102);
			}
		}
	}
	//оранжевое стекло
	glasses[Glass_types::ORANGE].glass_name = "orange_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::ORANGE].block[i][j].set(215, 127, 52, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::ORANGE].block[i][j].set(215, 127, 52, 155);
			}
			else
			{
				glasses[Glass_types::ORANGE].block[i][j].set(215, 127, 52, 102);
			}
		}
	}
	//сиреневое стекло (НЕ ДОСТАТОЧНО ДАННЫХ ДЛЯ РЕВЕРСА, ПРЕДПОЛОЖИТЕЛЬНЫЕ ЗНАЧЕНИЯ - (178,75,215)
	glasses[Glass_types::MAGENTA].glass_name = "magenta_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::MAGENTA].block[i][j].set(178, 75, 215, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::MAGENTA].block[i][j].set(178, 75, 215, 155);
			}
			else
			{
				glasses[Glass_types::MAGENTA].block[i][j].set(178, 75, 215, 102);
			}
		}
	}
	//светло синее стекло
	glasses[Glass_types::LIGHT_BLUE].glass_name = "light_blue_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::LIGHT_BLUE].block[i][j].set(102, 153, 216, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::LIGHT_BLUE].block[i][j].set(102, 153, 216, 155);
			}
			else
			{
				glasses[Glass_types::LIGHT_BLUE].block[i][j].set(102, 153, 216, 102);
			}
		}
	}
	//желтое стекло
	glasses[Glass_types::YELLOW].glass_name = "yellow_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::YELLOW].block[i][j].set(228, 228, 52, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::YELLOW].block[i][j].set(228, 228, 52, 155);
			}
			else
			{
				glasses[Glass_types::YELLOW].block[i][j].set(228, 228, 52, 102);
			}
		}
	}
	//лаймовое стекло
	glasses[Glass_types::LIME].glass_name = "lime_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::LIME].block[i][j].set(127, 204, 25, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::LIME].block[i][j].set(127, 204, 25, 155);
			}
			else
			{
				glasses[Glass_types::LIME].block[i][j].set(127, 204, 25, 102);
			}
		}
	}
	//розовое стекло
	glasses[Glass_types::PINK].glass_name = "pink_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::PINK].block[i][j].set(242, 127, 165, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::PINK].block[i][j].set(242, 127, 165, 155);
			}
			else
			{
				glasses[Glass_types::PINK].block[i][j].set(242, 127, 165, 102);
			}
		}
	}
	//серое стекло
	glasses[Glass_types::GRAY].glass_name = "gray_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::GRAY].block[i][j].set(76, 76, 76, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::GRAY].block[i][j].set(76, 76, 76, 155);
			}
			else
			{
				glasses[Glass_types::GRAY].block[i][j].set(76, 76, 76, 102);
			}
		}
	}
	//светло серое стекло
	glasses[Glass_types::LIGHT_GRAY].glass_name = "light_gray_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::LIGHT_GRAY].block[i][j].set(153, 153, 153, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::LIGHT_GRAY].block[i][j].set(153, 153, 153, 155);
			}
			else
			{
				glasses[Glass_types::LIGHT_GRAY].block[i][j].set(153, 153, 153, 102);
			}
		}
	}
	//бирюзовое серое стекло
	glasses[Glass_types::CYAN].glass_name = "cyan_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::CYAN].block[i][j].set(76, 127, 153, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::CYAN].block[i][j].set(76, 127, 153, 155);
			}
			else
			{
				glasses[Glass_types::CYAN].block[i][j].set(76, 127, 153, 102);
			}
		}
	}
	//фиолетовое стекло
	glasses[Glass_types::PURPLE].glass_name = "purple_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::PURPLE].block[i][j].set(127, 63, 178, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::PURPLE].block[i][j].set(127, 63, 178, 155);
			}
			else
			{
				glasses[Glass_types::PURPLE].block[i][j].set(127, 63, 178, 102);
			}
		}
	}
	//синее стекло(КАКОГО_ТО ФИГА ОТЛИЧАЕТСЯ ОТ ОСТАЛЬНЫХ)
	glasses[Glass_types::BLUE].glass_name = "blue_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::BLUE].block[i][j].set(51, 76, 178, 180);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::BLUE].block[i][j].set(51, 76, 178, 141);
			}
			else
			{
				glasses[Glass_types::BLUE].block[i][j].set(51, 76, 178, 102);
			}
		}
	}
	//коричневое стекло
	glasses[Glass_types::BROWN].glass_name = "brown_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::BROWN].block[i][j].set(102, 76, 51, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::BROWN].block[i][j].set(102, 76, 51, 155);
			}
			else
			{
				glasses[Glass_types::BROWN].block[i][j].set(102, 76, 51, 102);
			}
		}
	}
	//зеленое стекло
	glasses[Glass_types::GREEN].glass_name = "green_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::GREEN].block[i][j].set(102, 127, 52, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::GREEN].block[i][j].set(102, 127, 52, 155);
			}
			else
			{
				glasses[Glass_types::GREEN].block[i][j].set(102, 127, 52, 102);
			}
		}
	}
	//красное стекло
	glasses[Glass_types::RED].glass_name = "red_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::RED].block[i][j].set(153, 51, 51, 223);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::RED].block[i][j].set(153, 51, 51, 172);
			}
			else
			{
				glasses[Glass_types::RED].block[i][j].set(153, 51, 51, 127);
			}
		}
	}
	//черное стекло
	glasses[Glass_types::BLACK].glass_name = "black_stained_glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15)
			{
				glasses[Glass_types::BLACK].block[i][j].set(25, 25, 25, 163);
			}
			else if ((i == 2 && j == 12) || (i == 3 && j == 13) || (i == 11 && j == 2) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::BLACK].block[i][j].set(25, 25, 25, 155);
			}
			else
			{
				glasses[Glass_types::BLACK].block[i][j].set(25, 25, 25, 102);
			}
		}
	}
	//прозрачное стекло
	glasses[Glass_types::CLEAR].glass_name = "glass";
	for (int i = 0; i <= 15; ++i)
	{
		for (int j = 0; j <= 15; ++j)
		{
			if ((i == 15 && j >= 0 && j <= 14) || (j == 0 && i >= 4) || (j == 0 && i == 2) || (i == 2 && j == 12) || (i == 3 && j == 13) || (i == 12 && j == 3) || (i == 13 && j == 4))
			{
				glasses[Glass_types::CLEAR].block[i][j].set(208, 234, 233, 1);
			}
			else if ((j == 0 && (i == 0 || i == 1 || i == 3)) || (i == 0 && (j == 1 || j == 3 || j == 14 || j == 15)) || (j == 15 && (i == 1 || i == 14 || i == 15)) || (i == 11 && j == 2))
			{
				glasses[Glass_types::CLEAR].block[i][j].set(168, 208, 217, 1);
			}
			else if (j == 15 && (i == 13 || i == 12 || i == 11 || i == 9))
			{
				glasses[Glass_types::CLEAR].block[i][j].set(123, 174, 183, 1);
			}
			else if (i == 0 || j == 15)
			{
				glasses[Glass_types::CLEAR].block[i][j].set(139, 193, 205, 1);
			}
			else
			{
				glasses[Glass_types::CLEAR].block[i][j].set(255, 255, 255, 0);
			}
		}
	}
}
