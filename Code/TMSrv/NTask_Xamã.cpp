#include "ProcessClientMessage.h"

void NTask_Xamã(int a_iConn, int a_iTarget, int confirm)
{
	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	if (confirm == 0)
		return;

	int i = 0;

	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != 3170)
			continue;

		break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[3170].Name);
		SendSay(a_iTarget, temp);
		return;
	}

	if (NewbieEventServer)
	{
		if ((when.tm_hour == 12 || when.tm_hour == 20) && when.tm_min <= 9)
		{
			DoTeleport(a_iConn, 3522 + rand() % 5 - 3, 1471 + rand() % 5 - 3);

			MSG_STANDARDPARM sm;
			memset(&sm, 0, sizeof(MSG_STANDARDPARM));

			sm.Type = _MSG_StartTime;
			sm.ID = ESCENE_FIELD;
			sm.Size = sizeof(MSG_STANDARDPARM);
			sm.Parm = 1200;

			MapaMulticast(27, 11, (MSG_STANDARD*)&sm, 0);
		}
		else
		{
			SendSay(a_iTarget, g_pMessageStringTable[_NN_Night_Already]);
			return;
		}
	}
	else
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_NEWBIEEVENTSERVER]);
		return;
	}

	sprintf(temp, "etc,questColiseuN ticket xamã name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

	BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);
	SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
	return;
}
