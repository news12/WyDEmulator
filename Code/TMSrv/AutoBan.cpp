#include "AutoBan.h"
#include "../ConfigIni.h"

using ConfigIni::nConfig;

void ReadAutoBan()
{
	for (size_t i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;
		
		int status = nConfig::ReadAutoBan(PATH_AUTO_BAN, pMob[i].MOB.MobName);
		if (status)
		{
			int eu = 0;
		}
	}
}

void WriteAutoBan()
{
}
