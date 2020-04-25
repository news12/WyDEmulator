#include "main.h"

int HKD_ChangeTabColor(char* msg)
{
	char keyColor[3];
	int color = 0xFFCCCCCC;

	memcpy(keyColor, &msg[0], 2);
	//keyColor[3] = '\0';
	if (!strcmp(keyColor, "o."))
	{
		color = TNColor::Orange;
	}
	if (!strcmp(keyColor, "b."))
	{
		color = TNColor::Blue;
	}
	if (!strcmp(keyColor, "y."))
	{
		color = TNColor::Yellow;
	}
	if (!strcmp(keyColor, "g."))
	{
		color = TNColor::GreenYellow;
	}
	if (!strcmp(keyColor, "p."))
	{
		color = TNColor::DeepPink;
	}
	if (!strcmp(msg, "Ajudante para iniciantes"))
		color = TNColor::Blue;

	if (!strcmp(msg, "EternalWYD"))
		color = TNColor::Orange;

	return color;
}

