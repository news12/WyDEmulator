#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>
#include "..\Basedef.h"
#include "..\CPSock.h"
#include "..\ItemEffect.h"
#include "Language.h"
#include "CItem.h"
#include "Server.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "ProcessClientMessage.h"
#include "ProcessDBMessage.h"
#include "MacroPerga.h"
//Fadas Eternal
short fadasEternal[3]{ 3789,3790,3791 };
int fadaOn;

void WINAPI InitMacro()
{

	for (size_t i = 0; i < MAX_USER; i++)
	{

		if (pMob[i].Mode != USER_PLAY)
			continue;

		int PosX = pMob[i].TargetX;
		int PosY = pMob[i].TargetY;
		int EntradaAgua = FALSE;

		if ((PosY >= 1767 && PosY <= 1774) && (PosX >= 1962 && PosX <= 1986))
		{
			pMob[i].MOB.macroOn = FALSE;
			pMob[i].MOB.MacroInside = FALSE;
			pMob[i].MOB.SalaClear = FALSE;
			EntradaAgua = TRUE;
		}

		if (!EntradaAgua && !pMob[i].MOB.MacroInside && !pMob[i].MOB.SalaClear)
			break;

		for (size_t cFada = 0; cFada < 3; cFada++)
			{
				if (pMob[i].MOB.Equip[13].sIndex == fadasEternal[cFada])
				{
					fadaOn = TRUE;
					break;
				}
					fadaOn = FALSE;
					pMob[i].MOB.macroOn = FALSE;
					pMob[i].MOB.MacroInside = FALSE;
					pMob[i].MOB.SalaClear = FALSE;
					EntradaAgua = FALSE;
				
			}

		
		if (fadaOn)
		{
			if ((!pMob[i].MOB.MacroInside && EntradaAgua) || (pMob[i].MOB.SalaClear))
			{
				try
				{
					MacroOnline(i);
				}
				catch (const std::exception&)
				{
					sprintf(temp, "err,start MacroOnline %d", CurrentTime);
					Log(temp, "-system macro perga", 0);
				}
				
			}

		}

	}
}

void MacroOnline(int ClientID)
{
	//CloseHandle(InitMacro);
	int emptySlot = GetFirstSlotBag(ClientID);
	if (!emptySlot)
	{
		sprintf(temp, "Não foi encontrado slot vago na Mochila");
		SendMsgExp(ClientID, temp, TNColor::CornflowerBlue, false);
	}
	else
	{
		Sleep(2000);
		AtiveMacroPerga((int)ClientID);
	}
	
		 

}

int AtiveMacroPerga(int conn)
{

	if (!fadaOn)
	return FALSE;

	int isPergaN = FALSE;
	int isPergaM = FALSE;
	int isPergaA = FALSE;
	int slotsInv = pMob[conn].MaxCarry;
	int salaFounded = false;
	int tipoPerga = -1;
	int slotPerga = -1;
	int pergaItem = 0;
	short wp = 0;
	short PosX ;
	short PosY;
	if (!pMob[conn].MOB.macroOn)
	{
		pMob[conn].MOB.macroOn = TRUE;
		for (size_t i = 0; i < slotsInv; i++)
		{
			 PosX = pMob[conn].TargetX;
			 PosY = pMob[conn].TargetY;
			int inside = 0;
			for (size_t p = 0; p < 9; p++)
			{
				if (pMob[conn].MOB.Carry[i].sIndex == PergaAguaN + p)
				{
					isPergaN = TRUE;
					break;
				}
					if (pMob[conn].MOB.Carry[i].sIndex == PergaAguaM + p)
				{
					isPergaM = TRUE;
					break;

				}
					if (pMob[conn].MOB.Carry[i].sIndex == PergaAguaA + p)
				{
					isPergaA = TRUE;
					break;

				}
			
			}
			slotPerga = i;

			if (isPergaN)
			{
				wp = 0;
				//
			}
#pragma region Pergaminho da Água M
			if (isPergaM)
			{
				wp = 1;

				for (int f = 0; f < 10; f++)
				{
					if (PosX >= WaterScrollPosition[wp][f][0] - 12 && PosY >= WaterScrollPosition[wp][f][1] - 12
						&& PosX <= WaterScrollPosition[wp][f][0] + 12 && PosY <= WaterScrollPosition[wp][f][1] + 12 && f >= 9)
					{
						inside = 1;
						break;
					}

					if (PosX >= WaterScrollPosition[wp][f][0] - 8 && PosY >= WaterScrollPosition[wp][f][1] - 8
						&& PosX <= WaterScrollPosition[wp][f][0] + 8 && PosY <= WaterScrollPosition[wp][f][1] + 8)
					{
						inside = 1;
						break;
					}


				}
				pMob[conn].MOB.MacroInside = inside;
				STRUCT_ITEM* item = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, 1, slotPerga);
				int Vol = BASE_GetItemAbility(item, EF_VOLATILE);
				int amount = BASE_GetItemAmount(item);
				
				


				if (Vol >= 21 && Vol <= 30)
				{
					
					if (pMob[conn].Leader != -1 && pMob[conn].Leader)
					{
						SendClientMsg(conn, g_pMessageStringTable[_NN_Party_Leader_Only]);
						SendItem(conn,1, slotPerga, item);
						break;
					}

					char UserName[128];

					int Sala = Vol - 21;
					int UserArea = Sala <= 7 ? GetUserInArea(WaterScrollPosition[wp][Sala][0] - 8, WaterScrollPosition[wp][Sala][1] - 8, WaterScrollPosition[wp][Sala][0] + 8,
						WaterScrollPosition[wp][Sala][1] + 8, UserName) : GetUserInArea(WaterScrollPosition[wp][Sala][0] - 12, WaterScrollPosition[wp][Sala][1] - 12,
						WaterScrollPosition[wp][Sala][0] + 12, WaterScrollPosition[wp][Sala][1] + 12, UserName);

					if (UserArea >= 1)
						continue;
					

					WaterClear1[wp][Sala] = Sala <= 7 ? 30 : 15;

					DoTeleport(conn, WaterScrollPosition[wp][Sala][0], WaterScrollPosition[wp][Sala][1]);
					SendClientSignalParm(conn, ESCENE_FIELD, _MSG_StartTime, WaterClear1[wp][Sala] * 2);
					pMob[conn].MOB.SalaClear = FALSE;
					for (int i = 0; i < MAX_PARTY; i++)
					{
						int partyconn = pMob[conn].PartyList[i];

						if (partyconn > 0 && partyconn < MAX_USER && partyconn != conn && pUser[partyconn].Mode == USER_PLAY)
						{
							DoTeleport(partyconn, WaterScrollPosition[wp][Sala][0], WaterScrollPosition[wp][Sala][1]);
							SendClientSignalParm(partyconn, ESCENE_FIELD, _MSG_StartTime, WaterClear1[wp][Sala] * 2);
						}
					}

					if (Sala <= 7)
					{
						GenerateMob(Sala + WATER_M_INITIAL, 0, 0);
						GenerateMob(Sala + WATER_M_INITIAL, 0, 0);
						RebuildGenerator();
					}
					else if (Sala == 9)
					{
						int _rand = rand() % 10;

						if (_rand < 4)
							GenerateMob(WATER_M_INITIAL + 8, 0, 0);

						else if (_rand < 5)
							GenerateMob(WATER_M_INITIAL + 9, 0, 0);

						else if (_rand < 6)
							GenerateMob(WATER_M_INITIAL + 10, 0, 0);

						else
							GenerateMob(WATER_M_INITIAL + 11, 0, 0);
					}

				
						//BASE_ClearItem(&pMob[conn].MOB.Carry[slotPerga]);

					if (amount > 1)
						BASE_SetItemAmount(&pMob[conn].MOB.Carry[i], amount - 1);
					else
						BASE_ClearItem(&pMob[conn].MOB.Carry[i]);

					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
					
					return TRUE;
				}

				//return FALSE;
			}

#pragma endregion


#pragma region Pergaminho da Água A
			if (isPergaA)
			{
				wp = 2;

				for (int f = 0; f < 10; f++)
				{
					if (PosX >= WaterScrollPosition[wp][f][0] - 12 && PosY >= WaterScrollPosition[wp][f][1] - 12
						&& PosX <= WaterScrollPosition[wp][f][0] + 12 && PosY <= WaterScrollPosition[wp][f][1] + 12 && f >= 9)
					{
						inside = 1;
						break;
					}

					if (PosX >= WaterScrollPosition[wp][f][0] - 8 && PosY >= WaterScrollPosition[wp][f][1] - 8
						&& PosX <= WaterScrollPosition[wp][f][0] + 8 && PosY <= WaterScrollPosition[wp][f][1] + 8)
					{
						inside = 1;
						break;
					}

				}
				pMob[conn].MOB.MacroInside = inside;
				STRUCT_ITEM* item = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, 1, slotPerga);
				int Vol = BASE_GetItemAbility(item, EF_VOLATILE);
				int amount = BASE_GetItemAmount(item);




				if (Vol >= 161 && Vol <= 170)
				{

					if (pMob[conn].Leader != -1 && pMob[conn].Leader)
					{
						SendClientMsg(conn, g_pMessageStringTable[_NN_Party_Leader_Only]);
						SendItem(conn, 1, slotPerga, item);
						break;
					}

					char UserName[128];

					int Sala = Vol - 161;
					int UserArea = Sala <= 7 ? GetUserInArea(WaterScrollPosition[wp][Sala][0] - 8, WaterScrollPosition[wp][Sala][1] - 8, WaterScrollPosition[wp][Sala][0] + 8,
						WaterScrollPosition[wp][Sala][1] + 8, UserName) : GetUserInArea(WaterScrollPosition[wp][Sala][0] - 12, WaterScrollPosition[wp][Sala][1] - 12,
							WaterScrollPosition[wp][Sala][0] + 12, WaterScrollPosition[wp][Sala][1] + 12, UserName);

					if (UserArea >= 1)
						continue;


					WaterClear1[wp][Sala] = Sala <= 7 ? 30 : 15;

					DoTeleport(conn, WaterScrollPosition[wp][Sala][0], WaterScrollPosition[wp][Sala][1]);
					SendClientSignalParm(conn, ESCENE_FIELD, _MSG_StartTime, WaterClear1[wp][Sala] * 2);
					pMob[conn].MOB.SalaClear = FALSE;
					for (int i = 0; i < MAX_PARTY; i++)
					{
						int partyconn = pMob[conn].PartyList[i];

						if (partyconn > 0 && partyconn < MAX_USER && partyconn != conn && pUser[partyconn].Mode == USER_PLAY)
						{
							DoTeleport(partyconn, WaterScrollPosition[wp][Sala][0], WaterScrollPosition[wp][Sala][1]);
							SendClientSignalParm(partyconn, ESCENE_FIELD, _MSG_StartTime, WaterClear1[wp][Sala] * 2);
						}
					}

					if (Sala <= 7)
					{
						GenerateMob(Sala + WATER_A_INITIAL, 0, 0);
						GenerateMob(Sala + WATER_A_INITIAL, 0, 0);
						RebuildGenerator();
					}
					else if (Sala == 9)
					{
						int _rand = rand() % 10;

						if (_rand < 4)
							GenerateMob(WATER_A_INITIAL + 8, 0, 0);

						else if (_rand < 5)
							GenerateMob(WATER_A_INITIAL + 9, 0, 0);

						else if (_rand < 6)
							GenerateMob(WATER_A_INITIAL + 10, 0, 0);

						else
							GenerateMob(WATER_A_INITIAL + 11, 0, 0);
					}


					//BASE_ClearItem(&pMob[conn].MOB.Carry[slotPerga]);

					if (amount > 1)
						BASE_SetItemAmount(&pMob[conn].MOB.Carry[i], amount - 1);
					else
						BASE_ClearItem(&pMob[conn].MOB.Carry[i]);

					SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);

					return TRUE;
				}

				//return FALSE;
			}

#pragma endregion

		}
		return TRUE;
		//Player.macroOn = FALSE;
		//pMob[conn].MacroPerga = FALSE;
	}


}

int UseItem(int slotItem, int conn)
{
	try
	{
	
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
	
}

