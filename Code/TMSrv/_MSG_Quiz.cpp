#include "ProcessClientMessage.h"

void Exec_MSG_Quiz(int a_iConn, char *pMsg)
{
	if (a_iConn <= 0 || a_iConn >= MAX_USER)
		return;

	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	if (SendQuiz[a_iConn].Status)
	{
		if (m->Parm == SendQuiz[a_iConn].RespostaCorreta)
		{
			pMob[a_iConn].MOB.Coin += pMob[a_iConn].MOB.BaseScore.Level * 2;
			pMob[a_iConn].MOB.Exp += pMob[a_iConn].MOB.BaseScore.Level * 5;
			SendEtc(a_iConn);

			sprintf(temp, g_pMessageStringTable[_DD_QUIZ], pMob[a_iConn].MOB.Exp, pMob[a_iConn].MOB.Coin);
			SendMsgExp(a_iConn, temp, TNColor::Original, false);
			SendEmotion(a_iConn, 100, rand() % 5);
		}
		else
		{
			sprintf(temp, g_pMessageStringTable[_DD_NOT_QUIZ]);
			SendMsgExp(a_iConn, temp, TNColor::Original, false);
		}

		SendQuiz[a_iConn].Status = FALSE;
	}
	return;
}