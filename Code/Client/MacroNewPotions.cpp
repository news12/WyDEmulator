#include "main.h"

INT32 HKD_Macro_NewPotions(STRUCT_ITEM* item, INT32 type)
{
	if (type == 1) // pots de hp
	{
		switch (item->sIndex)
		{
		case 404:
			return TRUE;
			break;
		case 3322:
			return TRUE;
			break;
		case 3431:
			return TRUE;
			break;
		default:
			break;
		}
	}

	else if (type == 2) // pots mp
	{
		switch (item->sIndex)
		{
		case 409:
			return TRUE;
			break;
		case 3431:
			return TRUE;
			break;
		case 3472:
			return TRUE;
			break;
		default:
			break;
		}
	}

	return FALSE;
}