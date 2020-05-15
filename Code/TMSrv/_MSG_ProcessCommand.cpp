#include "ProcessDBMessage.h"
#include "ProcessClientMessage.h"

void Exec_MSG_ProcessCommand(int a_iConn, int level, char * pMsg)
{
	char cmd[128], sval1[128], sval2[128], sval3[128], sval4[128], sval5[128], sval6[128], sval7[128], sval8[128];
	unsigned int  ival1 = 0, ival2 = 0, ival3 = 0, ival4 = 0, ival5 = 0, ival6 = 0, ival7 = 0, ival8 = 0;
	long long  dval2 = 0;

	sscanf(pMsg + 1, "%s %s %s %s %s %s %s %s %s", cmd, sval1, sval2, sval3, sval4, sval5, sval6, sval7, sval8);

	sscanf(sval1, "%d", &ival1);
	sscanf(sval2, "%llu", &dval2);
	sscanf(sval2, "%d", &ival2);
	sscanf(sval3, "%d", &ival3);
	sscanf(sval4, "%d", &ival4);
	sscanf(sval5, "%d", &ival5);
	sscanf(sval6, "%d", &ival6);
	sscanf(sval7, "%d", &ival7);
	sscanf(sval8, "%d", &ival8);

	char logtemp[256];
	sprintf(logtemp, "Administrador [%s] %s", pMob[a_iConn].MOB.MobName, pMsg);

	if (a_iConn != 0)
		Log(logtemp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);

	else
		Log(logtemp, "Chat GM", 0);

	if (level >= 1)
	{
		if (a_iConn <= 0 && a_iConn >= MAX_USER)
			return;

		if (!strcmp(cmd, "set"))
		{
			if (!strcmp(sval1, "sanc"))
			{
				if (pMob[a_iConn].MOB.Equip[0].sIndex != 0) { pMob[a_iConn].MOB.Equip[0].stEffect[0].cEffect = EF_SANC; pMob[a_iConn].MOB.Equip[0].stEffect[0].cValue = ival2; }
				if (pMob[a_iConn].MOB.Equip[1].sIndex != 0) { pMob[a_iConn].MOB.Equip[1].stEffect[0].cEffect = EF_SANC; pMob[a_iConn].MOB.Equip[1].stEffect[0].cValue = ival2; }
				if (pMob[a_iConn].MOB.Equip[2].sIndex != 0) { pMob[a_iConn].MOB.Equip[2].stEffect[0].cEffect = EF_SANC; pMob[a_iConn].MOB.Equip[2].stEffect[0].cValue = ival2; }
				if (pMob[a_iConn].MOB.Equip[3].sIndex != 0) { pMob[a_iConn].MOB.Equip[3].stEffect[0].cEffect = EF_SANC; pMob[a_iConn].MOB.Equip[3].stEffect[0].cValue = ival2; }
				if (pMob[a_iConn].MOB.Equip[4].sIndex != 0) { pMob[a_iConn].MOB.Equip[4].stEffect[0].cEffect = EF_SANC; pMob[a_iConn].MOB.Equip[4].stEffect[0].cValue = ival2; }
				if (pMob[a_iConn].MOB.Equip[5].sIndex != 0) { pMob[a_iConn].MOB.Equip[5].stEffect[0].cEffect = EF_SANC; pMob[a_iConn].MOB.Equip[5].stEffect[0].cValue = ival2; }
				if (pMob[a_iConn].MOB.Equip[6].sIndex != 0) { pMob[a_iConn].MOB.Equip[6].stEffect[0].cEffect = EF_SANC; pMob[a_iConn].MOB.Equip[6].stEffect[0].cValue = ival2; }
				if (pMob[a_iConn].MOB.Equip[7].sIndex != 0) { pMob[a_iConn].MOB.Equip[7].stEffect[0].cEffect = EF_SANC; pMob[a_iConn].MOB.Equip[7].stEffect[0].cValue = ival2; }
				SendClientMsg(a_iConn, "[Eternal sanc] <SUCESS>");
			}

			else if (!strcmp(sval1, "isgod"))
			{
				pUser[a_iConn].Admin = 1;
				pMob[a_iConn].MOB.BaseScore.Level = 1010;
				pMob[a_iConn].UpdateScore();
				SendClientMsg(a_iConn, "[Eternal isgod] <SUCESS>");
			}
			else if (!strcmp(sval1, "secclearskill"))
			{
				pMob[a_iConn].Extra.SecLearnedSkill = 0;
				SendClientMsg(a_iConn, "set clearskill");
			}
			else if (!strcmp(sval1, "learn"))
			{
				pMob[a_iConn].MOB.LearnedSkill = -1;
				SendEtc(a_iConn);
				SendClientMsg(a_iConn, "LEARN");
			}
			else if (!strcmp(sval1, "seclearned"))
			{
				int skillpos = ival2 % 12;
				int learn = 1 << skillpos;

				pMob[a_iConn].Extra.SecLearnedSkill |= learn;

				sprintf(temp, "%d", learn);
				SendClientMsg(a_iConn, temp);
			}
			else if (!strcmp(sval1, "class"))
			{
				pMob[a_iConn].MOB.Class = ival2;
				SendEtc(a_iConn);
				SendClientMsg(a_iConn, "CLASS");
			}

			else if (!strcmp(sval1, "clearskill"))
			{
				pMob[a_iConn].MOB.LearnedSkill = 0;
				SendClientMsg(a_iConn, "[Eternal clearskill] <SUCESS>");
			}

			else if (!strcmp(sval1, "soul"))
			{
				pMob[a_iConn].Extra.Soul = ival1;
				SendClientMsg(a_iConn, "SOUL");
			}

			else if (!strcmp(sval1, "level"))
			{
				if (ival2 > 2010)
					ival2 = 2010;

				pMob[a_iConn].MOB.BaseScore.Level = ival2;
				SendEtc(a_iConn);
				SendClientMsg(a_iConn, "[Eternal level] <SUCESS>");
			}

			else if (!strcmp(sval1, "hp"))
			{
				pMob[a_iConn].MOB.BaseScore.MaxHp = pMob[a_iConn].MOB.BaseScore.Hp = ival2;
				pMob[a_iConn].MOB.CurrentScore.MaxHp = pMob[a_iConn].MOB.CurrentScore.Hp = ival2;
				SendClientMsg(a_iConn, "[Eternal hp] <SUCESS>");
			}

			else if (!strcmp(sval1, "mp"))
			{
				pMob[a_iConn].MOB.BaseScore.MaxMp = pMob[a_iConn].MOB.BaseScore.Mp = ival2;
				pMob[a_iConn].MOB.CurrentScore.MaxMp = pMob[a_iConn].MOB.CurrentScore.Mp = ival2;
				SendClientMsg(a_iConn, "[Eternal mp] <SUCESS>");
			}

			else if (!strcmp(sval1, "ac"))
			{
				pMob[a_iConn].MOB.BaseScore.Ac = ival2;
				SendClientMsg(a_iConn, "[Eternal ac] <SUCESS>");
			}

			else if (!strcmp(sval1, "dam"))
			{
				pMob[a_iConn].MOB.BaseScore.Damage = ival2;
				SendClientMsg(a_iConn, "[Eternal dam] <SUCESS>");
			}

			else if (!strcmp(sval1, "exp"))
			{
				pMob[a_iConn].MOB.Exp = dval2;
				SendClientMsg(a_iConn, "[Eternal exp] <SUCESS>");
				SendEtc(a_iConn);
				pMob[a_iConn].CheckGetLevel();
			}

			else if (!strcmp(sval1, "str"))
			{
				pMob[a_iConn].MOB.BaseScore.Str = ival2;
				SendClientMsg(a_iConn, "[Eternal str] <SUCESS>");
			}

			else if (!strcmp(sval1, "int"))
			{
				pMob[a_iConn].MOB.BaseScore.Int = ival2;
				SendClientMsg(a_iConn, "[Eternal int] <SUCESS>");
			}

			else if (!strcmp(sval1, "dex"))
			{
				pMob[a_iConn].MOB.BaseScore.Dex = ival2;
				SendClientMsg(a_iConn, "[Eternal dex] <SUCESS>");

			}

			else if (!strcmp(sval1, "con"))
			{
				pMob[a_iConn].MOB.BaseScore.Con = ival2;
				SendClientMsg(a_iConn, "[Eternal con] <SUCESS>");
			}

			else if (!strcmp(sval1, "coin"))
			{
				pMob[a_iConn].MOB.Coin = ival2;
				SendClientMsg(a_iConn, "[Eternal coin] <SUCESS>");
			}

			else if (!strcmp(sval1, "skillbonus"))
			{
				pMob[a_iConn].MOB.SkillBonus = ival2;
				SendClientMsg(a_iConn, "[Eternal skillbonus] <SUCESS>");
			}

			else if (!strcmp(sval1, "special0"))
			{
				pMob[a_iConn].MOB.BaseScore.Special[0] = ival2;
				SendClientMsg(a_iConn, "[Eternal special0] <SUCESS>");
			}

			else if (!strcmp(sval1, "special1"))
			{
				pMob[a_iConn].MOB.BaseScore.Special[1] = ival2;
				SendClientMsg(a_iConn, "[Eternal special1] <SUCESS>");
			}

			else if (!strcmp(sval1, "special2"))
			{
				pMob[a_iConn].MOB.BaseScore.Special[2] = ival2;
				SendClientMsg(a_iConn, "[Eternal special2] <SUCESS>");
			}

			else if (!strcmp(sval1, "special3"))
			{
				pMob[a_iConn].MOB.BaseScore.Special[3] = ival2;
				SendClientMsg(a_iConn, "[Eternal special3] <SUCESS>");
			}

			else if (!strcmp(sval1, "scorebonus"))
			{
				pMob[a_iConn].MOB.ScoreBonus = ival2;
				SendClientMsg(a_iConn, "[Eternal scorebonus] <SUCESS>");
			}

			else if (!strcmp(sval1, "attackrun"))
			{
				pMob[a_iConn].MOB.BaseScore.AttackRun = ival2;
				SendClientMsg(a_iConn, "[Eternal attackrun] <SUCESS>");
			}

			else if (!strcmp(sval1, "critical"))
			{
				pMob[a_iConn].MOB.Critical = ival2;
				SendClientMsg(a_iConn, "[Eternal critical] <SUCESS>");
			}

			else if (!strcmp(sval1, "learned"))
			{
				int skillpos = ival2 % 24;
				int learn = 1 << skillpos;

				sprintf(temp, "[Eternal learned] %d <SUCESS>", learn);
				SendClientMsg(a_iConn, temp);
			}

			else if (!strcmp(sval1, "multEXP"))
			{
				DOUBLEMODE = ival2;
				sprintf(temp, "[Exp do servidor será multiplicada por] %d ", DOUBLEMODE);
				SendClientMsg(a_iConn, temp);
				DrawConfig(TRUE);
			}

			else if (!strcmp(sval1, "dungeonevent"))
			{
				DUNGEONEVENT = ival2;

				if (DUNGEONEVENT)
					SendClientMsg(a_iConn, "SET DUNGEON EVENT ON");
				else
					SendClientMsg(a_iConn, "SET DUNGEON EVENT OFF");

				DrawConfig(TRUE);
			}

			else if (!strcmp(sval1, "champ"))
			{
				if (a_iConn <= 0 && a_iConn >= MAX_USER)
					return;

				if (ival2 >= 0 && ival2 < MAX_GUILDZONE)
				{
					g_pGuildZone[ival2].ChargeGuild = ival3;

					sprintf(temp, "Set Champion Guild - Zone:%d Guild %d", ival2, ival3);

					SendClientMsg(a_iConn, temp);
					GuildZoneReport();
					CReadFiles::WriteGuild();
				}
			}

			else if (!strcmp(sval1, "chall"))
			{
				if (a_iConn <= 0 && a_iConn >= MAX_USER)
					return;

				if (ival2 >= 0 && ival2 < MAX_GUILDZONE)
				{
					g_pGuildZone[ival2].ChallangeGuild = ival3;

					sprintf(temp, "Set Challanger Guild - Zone:%d Guild %d", ival2, ival3);

					SendClientMsg(a_iConn, temp);
					CReadFiles::WriteGuild();
				}
			}

			else if (!strcmp(sval1, "nobuffplayer"))
			{
				int player = GetUserByName(sval2);

				if (pUser[player].Mode != 22)
				{
					SendClientMsg(a_iConn, "Usuário não conectado.");
					return;
				}

				for (int i = 0; i < MAX_AFFECT; i++)
				{
					if (pMob[player].Affect[i].Type == 34)
						continue;

					pMob[player].Affect[i].Type = 0;
					pMob[player].Affect[i].Level = 0;
					pMob[player].Affect[i].Time = 0;
					pMob[player].Affect[i].Value = 0;
				}

				SendScore(player);
				SendClientMsg(a_iConn, "NO BUFF PLAYER");
			}

			
			else if (!strcmp(sval1, "special"))
			{
				pMob[a_iConn].MOB.SpecialBonus = ival2;
				SendClientMsg(a_iConn, "[Eternal special] <SUCESS>");
			}

			else if (!strcmp(sval1, "classmaster"))
			{
				pMob[a_iConn].Extra.ClassMaster = ival2;
				SendClientMsg(a_iConn, "[Eternal classmaster] <SUCESS>");
			}

			else if (!strcmp(sval1, "potiondelay"))
			{
				PotionDelay = ival2;
				SendClientMsg(a_iConn, "[Eternal potiondelay] <SUCESS>");
				DrawConfig(TRUE);
			}
			else if (!strcmp(sval1, "partybonus"))
			{
				PARTYBONUS = ival2;
				SendClientMsg(a_iConn, "[Eternal partybonus] <SUCESS>");
				DrawConfig(TRUE);
			}
			else if (!strcmp(sval1, "createitem"))
			{
				STRUCT_ITEM item;
				memset(&item, 0, sizeof(STRUCT_ITEM));

				item.sIndex = 696;
				SetItemBonus(&item, 0, 0, 0);

				CreateItem(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, &item, rand() % 4, 1);
			}
			else if (!strcmp(sval1, "name") && a_iConn != 0)
			{
				strcpy(pMob[a_iConn].MOB.MobName, sval2);

				MSG_CreateMob sm_cmn;
				memset(&sm_cmn, 0, sizeof(MSG_CreateMob));
				GetCreateMob(a_iConn, &sm_cmn);

				GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_cmn, 0);

				SendClientMsg(a_iConn, "[Eternal name] <SUCESS>");
			}

			else if (!strcmp(sval1, "closearmia"))
			{
				int i = 0;

				for (i = 0; i < MAX_ITEM; i++)
				{
					if (pItem[i].ITEM.sIndex == 4143)
						break;
				}
				if (i == MAX_ITEM)
					return;

				UpdateItem(i, STATE_LOCKED, &pItem[i].Height);

				MSG_CreateItem sm_cig;
				memset(&sm_cig, 0, sizeof(MSG_CreateItem));

				GetCreateItem(i, &sm_cig);

				GridMulticast(pItem[i].PosX, pItem[i].PosY, (MSG_STANDARD*)&sm_cig, 0);

				SendClientMsg(a_iConn, "[Eternal closearmia] <SUCESS>");
			}

			else if (!strcmp(sval1, "openarmia"))
			{
				int i = 0;

				for (i = 0; i < MAX_ITEM; i++)
				{
					if (pItem[i].ITEM.sIndex == 4143)
						break;
				}
				if (i == MAX_ITEM)
					return;

				UpdateItem(i, STATE_OPEN, &pItem[i].Height);

				MSG_CreateItem sm_cig;
				memset(&sm_cig, 0, sizeof(MSG_CreateItem));

				GetCreateItem(i, &sm_cig);

				GridMulticast(pItem[i].PosX, pItem[i].PosY, (MSG_STANDARD*)&sm_cig, 0);

				SendClientMsg(a_iConn, "[Eternal openarmia] <SUCESS>");
			}

			else if (!strcmp(sval1, "billmode"))
			{
				if (ival2 == 2 || ival2 == 3)
				{
					if (BillServerSocket.Sock == NULL)
					{
						SendClientMsg(a_iConn, "not connected to billing server.+billconnect first");
						return;
					}
				}
				BILLING = ival2;
				SendClientMsg(a_iConn, "set billing");
				DrawConfig(1);
			}

			else if (!strcmp(sval1, "billfree"))
			{
				FREEEXP = ival2;
				SendClientMsg(a_iConn, "SET FREE LEVEL");
				DrawConfig(1);
			}

			else if (!strcmp(sval1, "charselbill"))
			{
				CHARSELBILL = ival2;
				SendClientMsg(a_iConn, "SET CHARSELL BILL");
				DrawConfig(1);
			}

			else if (!strcmp(sval1, "reloadfile"))
			{
				BASE_InitializeBaseDef();
				BASE_ReadGuardFile();
				BASE_ReadQuestDiaria();
				BASE_InitializeMessage("Language.txt");
				ReadLevelItemConfig();
				CReadFiles::ReadSancRate();
				CReadFiles::ReadQuestsRate();
				CReadFiles::ReadCompRate();
				CCastleZakum::ReadCastleQuest();
				SendClientMsg(a_iConn, "[Eternal reloadfile] <SUCESS>");
			}

			else if (!strcmp(sval1, "clearcarry"))
			{
				for (int i = 0; i < MAX_CARRY - 4; i++)
				{
					BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);
					SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
				}

				SendClientMsg(a_iConn, "[Eternal clearcarry] <SUCESS>");
			}

			else if (!strcmp(sval1, "clearcargo"))
			{
				for (int i = 0; i < MAX_CARGO - 2; i++)
				{
					BASE_ClearItem(&pUser[a_iConn].Cargo[i]);
					SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pUser[a_iConn].Cargo[i]);
				}

				SendClientMsg(a_iConn, "[Eternal clearcargo] <SUCESS>");
			}

			else if (!strcmp(sval1, "item"))
			{
				STRUCT_ITEM Item;
				memset(&Item, 0, sizeof(STRUCT_ITEM));

				Item.sIndex = ival2;

				if (ival2 >= 2330 && ival2 < 2390)
				{
					Item.stEffect[0].sValue = 2000;
					Item.stEffect[1].cEffect = 120;
					Item.stEffect[1].cValue = 60;
				}

				Item.stEffect[0].cEffect = ival3;
				Item.stEffect[0].cValue = ival4;
				Item.stEffect[1].cEffect = ival5;
				Item.stEffect[1].cValue = ival6;
				Item.stEffect[2].cEffect = ival7;
				Item.stEffect[2].cValue = ival8;

				PutItem(a_iConn, &Item);

				sprintf(temp, "[Eternal item] Create item [%s] <SUCESS>", g_pItemList[Item.sIndex].Name);
				SendClientMsg(a_iConn, temp);
			}

			else if (ival1 >= 1 && ival1 <= MAX_EQUIP)
			{
				memset(&(pMob[a_iConn].MOB.Equip[ival1 - 1]), 0, sizeof(STRUCT_ITEM));
				pMob[a_iConn].MOB.Equip[ival1 - 1].sIndex = ival2;
				if (ival2 >= 2330 && ival2 < 2390)
				{
					pMob[a_iConn].MOB.Equip[ival1 - 1].stEffect[0].sValue = 2000;
					pMob[a_iConn].MOB.Equip[ival1 - 1].stEffect[1].cEffect = 120;
					pMob[a_iConn].MOB.Equip[ival1 - 1].stEffect[1].cValue = 60;
				}

				pMob[a_iConn].MOB.Equip[ival1 - 1].stEffect[0].cEffect = ival3;
				pMob[a_iConn].MOB.Equip[ival1 - 1].stEffect[0].cValue = ival4;
				pMob[a_iConn].MOB.Equip[ival1 - 1].stEffect[1].cEffect = ival5;
				pMob[a_iConn].MOB.Equip[ival1 - 1].stEffect[1].cValue = ival6;
				pMob[a_iConn].MOB.Equip[ival1 - 1].stEffect[2].cEffect = ival7;
				pMob[a_iConn].MOB.Equip[ival1 - 1].stEffect[2].cValue = ival8;
			}

			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendEquip(a_iConn, a_iConn);
			SendScore(a_iConn);
			SendEtc(a_iConn);

			for (int j = 0; j < MAX_EQUIP; j++)
				SendItem(a_iConn, 0, j, &pMob[a_iConn].MOB.Equip[j]);
		}
		//fin set
		else if (!strcmp(cmd, "ban"))
		{
			int tid = GetUserByName(sval2);

			if (sval2[0] == 0)
				return;

			if (pUser[tid].Mode != USER_PLAY)
				return;

			if (tid == 0)
			{
				SendClientMsg(a_iConn, "Can't find user.");
				return;
			}
			if (!strcmp(sval1, "3horas"))
			{
				SendBanAccount(tid, Banned::Tempo3horas);
				return;
			}
			if (!strcmp(sval1, "3dias"))
			{
				SendBanAccount(tid, Banned::Tempo3dias);
				return;
			}
			if (!strcmp(sval1, "7dias"))
			{
				SendBanAccount(tid, Banned::Tempo7dias);
				return;
			}
			return;
		}
		else if (!strcmp(cmd, "gfame"))
		{
			int Group = ServerGroup;

			if (ival1 > 0 && ival1 < 65536)
			{
				MSG_GuildInfo sm_gif;
				memset(&sm_gif, 0, sizeof(MSG_GuildInfo));

				sm_gif.Type = _MSG_GuildInfo;
				sm_gif.Size = sizeof(MSG_GuildInfo);
				sm_gif.ID = 0;

				sm_gif.Guild = ival1;

				GuildInfo[ival1].Fame += ival2;
				sm_gif.GuildInfo = GuildInfo[ival1];

				DBServerSocket.SendOneMessage((char*)&sm_gif, sizeof(MSG_GuildInfo));
				char cki[256];
				sprintf(cki, "Foi atribuido [%d] de fame para GuildIndex [%d]", ival2, ival1);
				SendClientMsg(a_iConn, cki);
			}
		}

		else if (!strcmp(cmd, "killkefra"))
		{
			for (int i = MAX_USER; i < MAX_MOB; i++)
				if (pMob[i].GenerateIndex == KEFRA_BOSS)
					MobKilled(i, a_iConn, 0, 0);

			SendClientMsg(a_iConn, "KILLKEFRA");

			DrawConfig(TRUE);
		}

		else if (!strcmp(cmd, "cp"))
		{
			SetPKPoint(a_iConn, ival1);

			MSG_CreateMob sm_cp;
			memset(&sm_cp, 0, sizeof(MSG_CreateMob));
			GetCreateMob(a_iConn, &sm_cp);

			GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_cp, 0);

			SendClientMsg(a_iConn, "CP");
		}

		else if (!strcmp(cmd, "frag"))
		{
			SetTotKill(a_iConn, ival1);

			MSG_CreateMob sm_cp;
			memset(&sm_cp, 0, sizeof(MSG_CreateMob));
			GetCreateMob(a_iConn, &sm_cp);

			GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_cp, 0);

			SendClientMsg(a_iConn, "FRAG");
		}

		else if (!strcmp(cmd, "createkefra"))
		{
			KefraLive = 0;

			GenerateMob(KEFRA_BOSS, 0, 0);

			for (int xx = KEFRA_MOB_INITIAL; xx <= KEFRA_MOB_END; xx++)
				GenerateMob(xx, 0, 0);

			DrawConfig(TRUE);
			SendClientMsg(a_iConn, "CREATE KEFRA");
		}

		else if (!strcmp(cmd, "reloadnpc"))
		{
			mNPCGen.ReadNPCGenerator();
			SendClientMsg(a_iConn, "RELOADNPC");
		}

		else if (!strcmp(cmd, "kick"))
		{
			if (sval1[0] == 0)
				return;

			sval1[NAME_LENGTH - 1] = 0;
			sval1[NAME_LENGTH - 2] = 0;

			int tid = GetUserByName(sval1);

			if (tid == 0)
			{
				SendClientMsg(a_iConn, "Can't find user.");
				return;
			}

			if (pUser[tid].Mode != USER_PLAY)
				return;

			if (pMob[tid].MOB.CurrentScore.Level >= pMob[a_iConn].MOB.CurrentScore.Level)
			{
				SendClientMsg(a_iConn, "Can't kick equal or high level admin");
				return;
			}

			CharLogOut(tid);
			CloseUser(tid);
		}

		else if (!strcmp(cmd, "ir"))
		{
			if (sval1[0] == 0)
				return;

			sval1[NAME_LENGTH - 1] = 0;
			sval1[NAME_LENGTH - 2] = 0;

			int user = GetUserByName(sval1);
			int x = pMob[user].TargetX;
			int y = pMob[user].TargetY;

			if (user == 0)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
				return;
			}

			if (pUser[user].Mode != USER_PLAY)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
				return;
			}

			DoTeleport(a_iConn, x, y);

			sprintf(temp, "[%s] se teleportou até você", pMob[a_iConn].MOB.MobName);
			SendClientMsg(user, temp);

			sprintf(temp, "Você se teleportou até [%s]", pMob[user].MOB.MobName);
			SendClientMsg(a_iConn, temp);
		}

		else if (!strcmp(cmd, "summon"))
		{
			if (sval1[0] == 0)
				return;

			sval1[NAME_LENGTH - 1] = 0;
			sval1[NAME_LENGTH - 2] = 0;

			int user = GetUserByName(sval1);
			int x = pMob[a_iConn].TargetX;
			int y = pMob[a_iConn].TargetY;
			if (user == 0)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
				return;
			}

			if (pUser[user].Mode != USER_PLAY)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
				return;
			}

			SummonPlayer(x, y, user);

			sprintf(temp, "Você foi sumonado por [%s]", pMob[a_iConn].MOB.MobName);
			SendClientMsg(user, temp);

			sprintf(temp, "Você sumonou [%s]", pMob[user].MOB.MobName);
			SendClientMsg(a_iConn, temp);
		}

		else if (!strcmp(cmd, "allsummon"))
		{
			int x = pMob[a_iConn].TargetX;
			int y = pMob[a_iConn].TargetY;

			SummonServer(x, y);
			SendClientMsg(a_iConn, "ALLSUMMON");
		}

		else if (!strcmp(cmd, "notice"))
		{
			memcpy(temp, pMsg + 7, MESSAGE_LENGTH);

			MSG_DBNotice sm_dbn;
			memset(&sm_dbn, 0, sizeof(MSG_DBNotice));

			sm_dbn.Size = sizeof(MSG_DBNotice);
			sm_dbn.ID = 0;
			sm_dbn.Type = _MSG_DBNotice;

			strncpy(sm_dbn.String, temp, MESSAGE_LENGTH - 1);

			DBServerSocket.SendOneMessage((char*)&sm_dbn, sizeof(MSG_DBNotice));

			return;
		}

		else if (!strcmp(cmd, "kill"))
		{
			for (int i = 0; i < NAME_LENGTH; i++)
			{
				if (sval1[i] == '_')
					sval1[i] = 32;
			}

			for (int i = MAX_USER; i < MAX_MOB; i++)
			{
				if (strncmp(pMob[i].MOB.MobName, sval1, NAME_LENGTH) == 0)
				{
					pMob[i].MOB.CurrentScore.Hp = 0;
					MobKilled(i, a_iConn, 0, 0);
				}
			}
			SendClientMsg(a_iConn, "[Eternal KILL] KILL");
		}


		else if (!strcmp(cmd, "create"))
		{
			int ret = CreateMob(sval1, pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, "npc", 0);

			if (ret == 1)
				SendClientMsg(a_iConn, "[Eternal create] Create mob <SUCESS>");
			if (ret == 0)
				SendClientMsg(a_iConn, "[Eternal create] <ERROR> No monster file in boss directory ");
			if (ret == -1)
				SendClientMsg(a_iConn, "[Eternal create] <ERROR> No empty mob");
			if (ret == -2)
				SendClientMsg(a_iConn, "[Eternal create] <ERROR> No empty mob grid");
		}

		else if (!strcmp(cmd, "buff"))
		{
			pMob[a_iConn].Affect[0].Type = ival1;
			pMob[a_iConn].Affect[0].Time = 162000;
			pMob[a_iConn].Affect[0].Value = 0;

			SendScore(a_iConn);
			SendClientMsg(a_iConn, "BUFF");
		}

		else if (!strcmp(cmd, "nobuff"))
		{
			for (int i = 0; i < MAX_AFFECT; i++)
			{

				pMob[a_iConn].Affect[i].Type = 0;
				pMob[a_iConn].Affect[i].Level = 0;
				pMob[a_iConn].Affect[i].Time = 0;
				pMob[a_iConn].Affect[i].Value = 0;
			}
			SendScore(a_iConn);
			SendClientMsg(a_iConn, "NOBUFF");
		}

		else if (!strcmp(cmd, "guildday"))
		{
			if (ival1 >= 0 && ival1 <= 6)
			{
				GuildDay = ival1;
				SendClientMsg(a_iConn, "SET GUILD BATTLE DAY");
			}
		}

		else if (!strcmp(cmd, "guildhour"))
		{
			if (ival1 >= 0 && ival1 <= 23)
			{
				GuildHour = ival1;
				SendClientMsg(a_iConn, "SET GUILD BATTLE HOUR");
			}
		}

		else if (!strcmp(cmd, "newbiehour"))
		{
			if (ival1 >= 0 && ival1 <= 23)
			{
				NewbieHour = ival1;
				SendClientMsg(a_iConn, "SET NEWBIE BATTLE HOUR");
			}
		}

		else if (!strcmp(cmd, "weekmode"))
		{
			if (ival1 >= 0 && ival1 <= 5)
			{
				ForceWeekMode = ival1;
				WeekMode = ival1 - 1;

				if (WeekMode == -1)
					WeekMode = 5;
				SendClientMsg(a_iConn, "[Eternal weekmode] FORCE GUILD MODE");
				return;
			}

			ForceWeekMode = -1;
			SendClientMsg(a_iConn, "[Eternal weekmode] WEEKLY GUILD MODE");
		}

		

		else if (!strcmp(cmd, "reloadguild"))
		{
			CReadFiles::ReadGuild();
			SendClientMsg(a_iConn, "[Eternal reloadguild] <SUCESS>");
		}

		else if (!strcmp(cmd, "readguildname"))
		{
			BASE_InitializeGuildName();
			SendClientMsg(a_iConn, "[Eternal readguildname] <SUCESS>");
		}

		else if (!strcmp(cmd, "reboot"))
		{
			ServerDown = 1;
		}

		else if (!strcmp(cmd, "impost"))
		{
			pMob[GuildImpostoID[0]].MOB.Exp = 0;
			pMob[GuildImpostoID[1]].MOB.Exp = 0;
			pMob[GuildImpostoID[2]].MOB.Exp = 0;
			pMob[GuildImpostoID[3]].MOB.Exp = 0;
			pMob[GuildImpostoID[4]].MOB.Exp = 0;

			SendClientMsg(a_iConn, "[Eternal impost]  IMPOST <SUCESS>");
		}

		else if (!strcmp(cmd, "statsapphire"))
		{
			if (ival1 < 0)
			{
				SendClientMsg(a_iConn, "err: +statsapphire (0-64)");
				return;
			}

			StatSapphire = ival1;
			SendClientMsg(a_iConn, "CHANGE STAT SAPPHIRE");
			DrawConfig(TRUE);
		}

		else if (!strcmp(cmd, "weather"))
		{
			ForceWeather = ival1;
			CurrentWeather = ival1;
			SendWeather();

			SendClientMsg(a_iConn, "[Eternal weather]  IMPOST <SUCESS>");
		}

		else if (!strcmp(cmd, "mute"))
		{
			int user = GetUserByName(sval1);

			if (user == 0)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
				return;
			}

			if (pUser[user].Mode != USER_PLAY)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
				return;
			}

			pUser[user].MuteChat = 1;

			SendScore(a_iConn);

			sprintf(temp, "[Eternal mute]  MUTE [%s] <SUCESS>", pMob[user].MOB.MobName);
			SendClientMsg(a_iConn, temp);
			SendClientMsg(user, g_pMessageStringTable[_NN_Chat_Prohibition]);
			return;
		}

		else if (!strcmp(cmd, "desmute"))
		{
			int user = GetUserByName(sval1);

			if (user == 0)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
				return;
			}

			if (pUser[user].Mode != USER_PLAY)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
				return;
			}

			pUser[user].MuteChat = 0;

			SendScore(a_iConn);

			sprintf(temp, "[Eternal desmute]  Desmute [%s] <SUCESS>", pMob[user].MOB.MobName);
			SendClientMsg(a_iConn, temp);
			SendClientMsg(user, g_pMessageStringTable[_NN_Chat_Free]);
			return;
		}

		else if (!strcmp(cmd, "saveall"))
		{
			SaveAll();
			SendClientMsg(a_iConn, "[Eternal mute] SAVEALL");
		}

		else if (!strcmp(cmd, "teleport"))
		{
			if (ival1 < 100)
				ival1 = ival1 * 128 + 64;
			if (ival2 < 100)
				ival2 = ival2 * 128 + 64;

			if (ival1 >= 0 && ival1 < MAX_GRIDX &&ival2 >= 0 && ival2 < MAX_GRIDY)
				DoTeleport(a_iConn, ival1, ival2);
		}

		else if (!strcmp(cmd, "snoop"))
		{
			if (a_iConn <= 0 && a_iConn >= MAX_USER)
				return;

			if (pMob[a_iConn].MOB.Merchant&MSV_SNOOP)
			{
				pMob[a_iConn].MOB.Merchant = pMob[a_iConn].MOB.Merchant & 0xFE;
				SendClientMsg(a_iConn, "SNOOP OFF");
			}
			else
			{
				pMob[a_iConn].MOB.Merchant = pMob[a_iConn].MOB.Merchant | MSV_SNOOP;
				SendClientMsg(a_iConn, "SNOOP ON");
			}

			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendScore(a_iConn);
			return;
		}
	}
}
