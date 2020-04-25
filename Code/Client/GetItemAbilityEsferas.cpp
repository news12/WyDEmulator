#include "main.h"

INT32 HKD_GetItemAbility_Esferas(STRUCT_ITEM* item, INT32 effectId)
{
	if (item->sIndex == 3980 || item->sIndex == 3983 || item->sIndex == 3986)
	{
		switch (effectId)
		{
		case 2:
			return 35;

		case 60:
			return 7;
		}
	}
	else if (item->sIndex == 3981 || item->sIndex == 3984 || item->sIndex == 3987)
	{
		switch (effectId)
		{
		case 2:
			return 210;

		case 60:
			return 40;

		case 54:
			return 28;
		}
	}
	else if (item->sIndex == 3993 || item->sIndex == 3994)
	{
		switch (effectId)
		{
		case 2:
			return 750;
		case 60:
			return 125;
		case 54:
			return 20;
		}
	}
	else if (item->sIndex >= 3995 && item->sIndex <= 3996)
	{
		switch (effectId)
		{
		case 2:
			return 0;

		case 60:
			return 0;
		}
	}

	return 0;
}