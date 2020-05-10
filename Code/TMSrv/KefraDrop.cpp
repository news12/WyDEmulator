#include "KefraDrop.h"

void KefraDrop(int killer)
{
	
	DWORD premiado = 0;
	unsigned short guildKilled = pMob[killer].MOB.Guild;

	

	for (size_t i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		int PosX = pMob[i].TargetX;
		int PosY = pMob[i].TargetY;

		int sortNum = rand() % MAX_DROP_KEFRA;

		STRUCT_ITEM* drop = &dropKefra[sortNum];

		if (pMob[i].MOB.Guild == guildKilled 
			&& (PosX >= 2341 && PosX <= 2392)
			&& (PosY >= 3906 && PosY <= 3953))
		{
			if (premiado < MAX_DROP_KEFRA)
			{
				PutItem(i, drop);
				sprintf(temp, "!Você recebeu [%s] como recompensa por ajudar a matar kefra!", g_pItemList[drop->sIndex].Name);
				SendClientMsg(i, temp);
				premiado++;
				continue;
			}

			break;
		}
	}
	return;

}
