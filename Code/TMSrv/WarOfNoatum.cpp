#include "WarOfNoatum.h"

void WarNoatum()
{
	time_t rawtime;
	tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (CastleServer == 1 && (timeinfo->tm_hour == 21))
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
	}
}
