#include "WarOfNoatum.h"

void WarNoatum()
{
	time_t rawtime;
	tm* timeinfo;
	int minDefine = 5;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int hourNotice = warsTimer[eNoatum].Hour;
	int minNotice;

	if (!warsTimer[eNoatum].Minute)
		minNotice = 60 - minDefine;
	else if (warsTimer[eNoatum].Minute < 5)
	{
		hourNotice = warsTimer[eNoatum].Hour - 1;
		minNotice = (60 - minDefine) + warsTimer[eNoatum].Minute;
	}
	else
		minNotice = warsTimer[eNoatum].Minute - minDefine;

	if (CastleServer == 0 && (timeinfo->tm_hour == hourNotice && timeinfo->tm_min == minNotice))
	{
		sprintf(temp, g_pMessageStringTable[_DN_Castle_will_be_open], minNotice);
		SendNotice(temp);
		CastleState = 1;

		for (int j = 0; j < MAX_USER; j++)
		{
			if (pUser[j].Mode == USER_PLAY)
				SendClientSignalParm(j, ESCENE_FIELD, 940, CastleState);
		}
		return;
	}


	if (CastleServer == 1 && (timeinfo->tm_hour == warsTimer[eNoatum].Hour && timeinfo->tm_min >= warsTimer[eNoatum].Minute))
	{
		ClearAreaGuild(1036, 1672, 1144, 1764, g_pGuildZone[4].ChargeGuild);

		ClearAreaTeleport(1129, 1705, 1129, 1709, 1057, 1742);
		ClearAreaTeleport(1116, 1705, 1116, 1709, 1057, 1742);
		ClearAreaTeleport(1094, 1688, 1094, 1692, 1057, 1742);
		ClearAreaTeleport(1087, 1609, 1087, 1713, 1057, 1742);
		ClearAreaTeleport(1050, 1690, 1050, 1690, 1057, 1742);
		ClearAreaTeleport(1046, 1690, 1047, 1691, 1057, 1742);
		ClearAreaTeleport(1124, 1708, 1124, 1708, 1057, 1742);

		SetCastleDoor(3);

		for (int i = 0; i < 3; ++i)
		{
			GenerateMob(i + TORRE_NOATUM1, 0, 0);
			LiveTower[i] = 1;
		}

		sprintf(temp, g_pMessageStringTable[_DN_Castle_opened]);
		SendNotice(temp);
		CastleState = 2;
		return;
	}

	int minFinish = warsTimer[eNoatum].Minute;
	int hourFinish = warsTimer[eNoatum].Hour + 1;
	
	if (hourFinish >= 24)
		hourFinish = 0;

	if (CastleServer == 2 && (timeinfo->tm_hour == hourFinish && timeinfo->tm_min == (minFinish -minDefine)))
	{
		sprintf(temp, g_pMessageStringTable[_DN_Castle_will_be_closed], minDefine);
		SendNotice(temp);
		CastleState = 3;
	}

	if (CastleState == 3 && timeinfo->tm_hour == hourFinish && timeinfo->tm_min == minFinish)
	{
		sprintf(temp, g_pMessageStringTable[_DN_Castle_closed]);
		SendNotice(temp);
		FinishCastleWar();
	}

	/*if (CastleServer == 1 && (timeinfo->tm_hour == 21))
	{
		if (CastleState || timeinfo->tm_min >= 5)
		{
			if (CastleState != 1 || timeinfo->tm_min <= 5 || timeinfo->tm_min >= 10)
			{
				if (CastleState != 2 || timeinfo->tm_min <= 50)
				{
					if (CastleState == 3 && timeinfo->tm_min > 55)
					{
						sprintf(temp, g_pMessageStringTable[_DN_Castle_closed], timeinfo->tm_hour - 17);
						SendNotice(temp);
						FinishCastleWar();
					}
				}
				else
				{
					sprintf(temp, g_pMessageStringTable[_DN_Castle_will_be_closed], timeinfo->tm_hour - 17);
					SendNotice(temp);
					CastleState = 3;
				}
			}
			else
			{
				ClearAreaGuild(1036, 1672, 1144, 1764, g_pGuildZone[4].ChargeGuild);

				ClearAreaTeleport(1129, 1705, 1129, 1709, 1057, 1742);
				ClearAreaTeleport(1116, 1705, 1116, 1709, 1057, 1742);
				ClearAreaTeleport(1094, 1688, 1094, 1692, 1057, 1742);
				ClearAreaTeleport(1087, 1609, 1087, 1713, 1057, 1742);
				ClearAreaTeleport(1050, 1690, 1050, 1690, 1057, 1742);
				ClearAreaTeleport(1046, 1690, 1047, 1691, 1057, 1742);
				ClearAreaTeleport(1124, 1708, 1124, 1708, 1057, 1742);

				SetCastleDoor(3);

				for (int i = 0; i < 3; ++i)
				{
					GenerateMob(i + TORRE_NOATUM1, 0, 0);
					LiveTower[i] = 1;
				}

				sprintf(temp, g_pMessageStringTable[_DN_Castle_opened], timeinfo->tm_hour - 17);
				SendNotice(temp);
				CastleState = 2;
			}
		}
		else
		{
			sprintf(temp, g_pMessageStringTable[_DN_Castle_will_be_open], timeinfo->tm_hour - 17);
			SendNotice(temp);
			CastleState = 1;

			for (int j = 0; j < MAX_USER; j++)
			{
				if (pUser[j].Mode == USER_PLAY)
					SendClientSignalParm(j, ESCENE_FIELD, 940, CastleState);
			}
		}
	} */
}

void FinishCastleWar()
{
	SetCastleDoor(1);

	ClearAreaGuild(1036, 1672, 1144, 1764, g_pGuildZone[4].ChargeGuild);

	CastleState = 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		SendClientSignal(i, _MSG_SendCastleState, CastleState);
	}

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		SendClientSignalParm(i, ESCENE_FIELD, _MSG_SendCastleState, CastleState);
	}

	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == MOB_EMPTY)
			continue;

		if (pMob[i].MOB.Equip[0].sIndex != 219)
			continue;

		DeleteMob(i, 2);
	}

	ClearArea(1036, 1672, 1144, 1764);
}

void SetCastleDoor(int state)
{
	for (int i = 0; i < 4; i++)
	{
		int DoorId = i + 36;

		if (pItem[DoorId].ITEM.sIndex <= 0 || pItem[DoorId].ITEM.sIndex >= MAX_ITEMLIST)
			continue;

		if (pItem[DoorId].State == state)
			continue;

		int height = 0;

		UpdateItem(DoorId, state, &height);

		if (state == STATE_OPEN)
		{
			MSG_UpdateItem sm;
			memset(&sm, 0, sizeof(MSG_UpdateItem));

			sm.ID = ESCENE_FIELD;
			sm.Type = _MSG_UpdateItem;
			sm.ItemID = DoorId + 10000;
			sm.Size = sizeof(MSG_UpdateItem);
			//		sm.Height = height;
			sm.State = pItem[DoorId].State;

			GridMulticast(pItem[DoorId].PosX, pItem[DoorId].PosY, (MSG_STANDARD*)&sm, 0);
		}
		else
		{
			int keyid = BASE_GetItemAbility(&pItem[DoorId].ITEM, EF_KEYID);

			if (keyid == 15)
				CreateMob("GATE", pItem[DoorId].PosX, pItem[DoorId].PosY, "npc", 0);

			MSG_CreateItem sm;
			memset(&sm, 0, sizeof(MSG_CreateItem));

			GetCreateItem(DoorId, &sm);

			GridMulticast(pItem[DoorId].PosX, pItem[DoorId].PosY, (MSG_STANDARD*)&sm, 0);
		}
		pItem[DoorId].Delay = 0;
	}
}
