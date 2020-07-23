#include "GuildHall.h"

void KeyTerritory(MSG_UseItem* m, STRUCT_ITEM* Item, int a_iConn)
{
	ReadTerritory();
	int GuildIndex = 0;
	int Groups = ServerGroup;
	int TerritoryID = -1;
	char Name[256];
	std::string nTerritoryName = "";
	switch (Item->sIndex)
	{
	case KEY_ARIMA:
		TerritoryID = Arima;
		break;
	case KEY_BARNEL:
		TerritoryID = Barnel;
		break;
	case KEY_CAMPUS:
		TerritoryID = Campus;
		break;
	case KEY_GOBI:
		TerritoryID = Gobi;
		break;
	case KEY_ICECROW:
		TerritoryID = IceCrow;
		break;
	case KEY_ICELAND:
		break;
	default:
		break;
	}

	if (TerritoryID < 0)
	{
		sprintf(temp, " Territorio Inexistente");
		SendClientMsg(a_iConn, temp);
		SendItem(a_iConn, m->SourType, m->SourPos, Item);
		return;
	}

	GuildIndex = Territory[TerritoryID].GuildIndex;
	nTerritoryName = TerritoryName[TerritoryID];

	if (GuildIndex)
	{
		BASE_GetGuildName(Groups, GuildIndex, Name);

		sprintf(temp, "O Territorio [%s] já pertence a Guild [%s]", nTerritoryName.c_str(), Name);
		SendClientMsg(a_iConn, temp);
		SendItem(a_iConn, m->SourType, m->SourPos, Item);
		return;
	}


	memset(Item, 0, sizeof(STRUCT_ITEM));

	SendItem(a_iConn, m->SourType, m->SourPos, Item);

	GuildIndex = pMob[a_iConn].MOB.Guild;

	Territory[TerritoryID].MaxMob = MAX_MOB_TERRITORY;
	Territory[TerritoryID].GuildIndex = GuildIndex;
	Territory[TerritoryID].Name = TerritoryName[TerritoryID];
	Territory[TerritoryID].DayWar= 6;
	WriteTerritory(TerritoryID);
	ReadTerritory();

	ReadGuildHall(a_iConn);

	GuildHall[GuildIndex].Territory++;

	WriteGuildHall(a_iConn);

	BASE_GetGuildName(Groups, GuildIndex, Name);

	sprintf(temp, "A Guild [%s] Adiquiriu o Territorio [%s]", Name, nTerritoryName.c_str());
	SendNotice(temp);

	sprintf(temp, "useitem,item key territory type: %d", Item->sIndex);
	MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
	return;
}

void GuildLevelUp()
{
}

void FamePointMob(unsigned int conn, unsigned int target)
{
	unsigned int mobLevel = pMob[target].MOB.CurrentScore.Level;
	unsigned int playerLevel = pMob[conn].MOB.CurrentScore.Level;
	unsigned int Guild = pMob[conn].MOB.Guild;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (target < MAX_USER)
		return;

	if (!pMob[conn].MOB.Guild)
		return;

	if (mobLevel >= playerLevel)
	{
		pMob[conn].CountMobKilled++;

		if (pMob[conn].CountMobKilled >= MaxMobKilled)
		{
			pMob[conn].CountMobKilled = 0;

			ReadGuildHall(conn);

			GuildHall[Guild].FamePoint += FameMob;

			WriteGuildHall(conn);
		}
	}

}

void FamePointBoss(unsigned int conn, unsigned int boss)
{
	unsigned int newFame = FameBase;
	unsigned int Guild = pMob[conn].MOB.Guild;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	if (boss < MAX_USER)
		return;

	if (!pMob[conn].MOB.Guild)
		return;

	switch (boss)
	{
	case KEFRA_BOSS:
		newFame *= 20;
		break;
	case SOMBRA_NEGRA_BOSS:
		newFame *= 5;
		break;
	default:
		break;
	}

	for (size_t i = 0; i < MAX_BOSS_CAMP; i++)
	{
		if (boss = bossCamp[i].Boss.ID)
		{
			newFame *= 2;
			break;
		}
	}

	if (newFame == FameBase)
		return;

			ReadGuildHall(conn);

			GuildHall[Guild].FamePoint += newFame;

			WriteGuildHall(conn);
		
}

void GuardianTerritory(int conn, int nTerritory, int NPC)
{
	time_t rawtime;
	tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int GuildAtual = Territory[nTerritory].GuildIndex;
	int GuildDesafiante = Territory[nTerritory].Challenger;
	int Groups = ServerGroup;
	char NameAtual[256];
	char NameDesafiante[256];
	std::string nTerritoryName = TerritoryName[nTerritory];
	int WarDay = Territory[nTerritory].DayWar;
	int WarBid = WarDay - 1;
	ReadTerritory();
	BASE_GetGuildName(Groups, GuildAtual, NameAtual);
	BASE_GetGuildName(Groups, GuildDesafiante, NameDesafiante);

	if (timeinfo->tm_wday == WarDay)
	{
		if (GuildDesafiante)
		{
			sprintf(temp, "A Guerra de Territorio entre:");
			SendSay(NPC, temp);
			sprintf(temp, "Atual: [%s] vs Desafiante: [%s]", NameAtual, NameDesafiante);
			SendSay(NPC, temp);
			sprintf(temp, "Terá inicio as 21:00");
			SendSay(NPC, temp);
			return;
		}
		else if (pMob[conn].MOB.Guild != GuildAtual)
		{
			if (!GuildAtual)
				sprintf(temp, "Esse território esta livre");
			else
			sprintf(temp, "Esse território pertence a guild: [%s]", NameAtual);

			SendSay(NPC, temp);
			return;
		}
		else
		{
			sprintf(temp, "[%s] -> Não é possivel ir para o Território em dias de guerra", pMob[conn].MOB.MobName);
			SendSay(NPC, temp);
			return;
		}
		
	}

	if (timeinfo->tm_wday == WarBid && pMob[conn].MOB.Guild != GuildAtual)
	{
		if (pMob[conn].MOB.GuildLevel != GUILD_LEADER)
		{
			sprintf(temp, "[%s] -> Somente lideres de guild podem desafiar.", pMob[conn].MOB.MobName);
			SendSay(NPC, temp);
			return;
		}
		else
		{
			sprintf(temp, "[%s] -> Sistema de Desafio de territorio desativado.", pMob[conn].MOB.MobName);
			SendSay(NPC, temp);
			return;
			//SendClientSignal(conn, 0, _MSG_ReqChallange); //Janela de mensagem de aposta
		}
		
	}

	if (pMob[conn].MOB.Guild != GuildAtual)
	{
		if (!GuildAtual)
			sprintf(temp, "Esse território esta livre");
		else
		sprintf(temp, "Esse território pertence a guild: [%s]", NameAtual);

		SendSay(NPC, temp);
		return;
	}
	else
	{
		//x363 y1330 Arima
		DoTeleport(conn, 363, 1330);
		sprintf(temp, "Bem vindo ao Territorio: [%s]", nTerritoryName.c_str());
		SendClientMsg(conn, temp);
		return;
	}
	
}
