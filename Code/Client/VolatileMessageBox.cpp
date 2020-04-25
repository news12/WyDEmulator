#include "main.h"

bool SetVolatileMessageBoxText(int itemID, char* text)
{
	//if (itemID == 3314)
	//{
	//	sprintf(text, "Deseja comer esse delicioso Frango Assado?");
	//	return true;
	//}

	switch (itemID)
	{
	case 3314:
		sprintf(text, "Deseja comer esse delicioso Frango Assado?");
		return true;
	case 3789:
		sprintf(text, "Deseja Equipar a Fada Eternal?");
		return true;
	default:
		break;
	}

	return false;
}

int AddVolatileMessageItem(int itemID)
{
	switch (itemID)
	{
	case 3314:
		return 1;
	case 3789:
		return 1;
	}
	return 0;
}