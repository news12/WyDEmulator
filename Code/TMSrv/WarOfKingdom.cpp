#include "WarOfKingdom.h"

void WarOfKingdom()
{
	time_t rawnow = time(NULL);
	struct tm* now = localtime(&rawnow);

	// Inicia o RvR
	if (/*now->tm_wday >= 1 && */ now->tm_wday == 6 /*&& NewbieEventServer*/)
	{
		if (now->tm_hour == 17 && now->tm_min == 55 && !g_pRvrWar.Annoucement)
		{
			SendNotice("A Guerra entre Reinos iniciará em 5 minutos. Acesse o teleporte de Noatun.");

			g_pRvrWar.Annoucement = 1;
		}
		else if (now->tm_hour == 18 && now->tm_min == 0 && !g_pRvrWar.Status)
		{
			g_pRvrWar.Status = 1;

			SendNotice("Guerra entre Reinos iniciada. Acesse o teleporte de Noatun!");

			GenerateMob(TORRE_RVR_BLUE, 0, 0);
			GenerateMob(TORRE_RVR_RED, 0, 0);

			
		}
		// Enviará uma mensagem para o servidor a cada 5 minutos a respeito dos pontos atuais
		else if (now->tm_hour == 18 && now->tm_min < 30 && !(now->tm_min % 5) && !g_pRvrWar.Annoucement_Point && g_pRvrWar.Status == 1)
		{
			MSG_ChatColor sm_mt;
			memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

			sm_mt.Size = sizeof(MSG_ChatColor);
			sm_mt.ID = 0;
			sm_mt.Type = _MSG_MagicTrumpet;

			sm_mt.Color = TNColor::CornflowerBlue;

			sprintf(sm_mt.Message, "Guerra entre Reinos");
			DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

			sprintf(sm_mt.Message, "Red: %d - Blue: %d", g_pRvrWar.Points[1], g_pRvrWar.Points[0]);
			DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

			g_pRvrWar.Annoucement_Point = 1;
		}
		else if (now->tm_hour == 18 && now->tm_min < 30 && (now->tm_min % 5) && g_pRvrWar.Annoucement_Point && g_pRvrWar.Status == 1)
			g_pRvrWar.Annoucement_Point = 0;

		else if (now->tm_hour == 18 && now->tm_min == 30 && g_pRvrWar.Status == 1)
		{
			for (INT32 i = 1000; i < 30000; i++)
			{
				if (pMob[i].GenerateIndex == TORRE_RVR_BLUE || pMob[i].GenerateIndex == TORRE_RVR_RED)
					MobKilled(i, 29999, 0, 0);
			}

			int winner = 0;
			if (g_pRvrWar.Points[0] > g_pRvrWar.Points[1])
			{
				// Inserir o log que desejar
				SendNotice("O reino blue foi o vencedora da Guerra entre Reinos");

				winner = 7;
			}
			else if (g_pRvrWar.Points[1] > g_pRvrWar.Points[0])
			{
				// Inserir o log que desejar
				SendNotice("O reino red foi o vencedora da Guerra entre Reinos");

				winner = 8;
			}
			else
			{
				SendNotice("A Guerra entre Reinos terminou em empate!");

				winner = 0;
			}

			g_pRvrWar.Points[0] = 0;
			g_pRvrWar.Points[1] = 0;
			g_pRvrWar.Bonus = winner;

			g_pRvrWar.Status = 0;
			g_pRvrWar.Annoucement = 0;

			ClearArea(1710, 1968, 1755, 1995);

			MSG_STANDARDPARM sm;
			memset(&sm, 0, sizeof(MSG_STANDARDPARM));

			sm.Type = 0x899;
			sm.ID = 0;
			sm.Parm = winner;

			DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_STANDARDPARM));

			if (winner != 0)
			{
				for (int i = 1; i < MAX_USER; i++)
				{
					if (pUser[i].Mode != USER_PLAY)
						continue;

					if (pMob[i].MOB.Clan == winner)
						pMob[i].GetCurrentScore(i);
				}
			}
		}
	}
}