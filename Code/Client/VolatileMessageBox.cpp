#include "main.h"

bool SetVolatileMessageBoxText(int itemID, char* text)
{
	switch (itemID)
	{
	case 3314:
		sprintf(text, "Deseja comer esse delicioso Frango Assado?");
		return true;
	case 4038:
	case 4039:
	case 4040:
	case 4041:
	case 4042:
		sprintf(text, "Deseja Teleportar para entrada da Quest?");
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
	case 4038:
	case 4039:
	case 4040:
	case 4041:
	case 4042:
		return 1;
	}
	return 0;
}