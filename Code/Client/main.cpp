#include "main.h"

STRUCT_QUESTDIARIA QuestDay;
STRUCT_CLIENTPAC g_pSendClientPac;

int __stdcall DllMain(HINSTANCE hInstDLL, DWORD catchReason, LPVOID lpResrv)
{
	__try
	{
		switch (catchReason)
		{
		case DLL_PROCESS_ATTACH:
		{
			DWORD dwOldProtectFlag_text;
			VirtualProtect((int*)0x0401000, 0x5F0FFF - 0x0401000, 0x40, &dwOldProtectFlag_text);

			HookNaked::Start();

			/* Tira os check-sum para manipulação de ponteiros */
			/* Remove - Client Is Bad Ptr */
			JMP_NEAR(0x005D33FD, (INT32*)0x005D3418);

			/* Remove - Client Is Write Ptr */
			JMP_NEAR(0x005D3419, (INT32*)0x005D3434);

			/* Remove - Client Is Bad Code Ptr */
			JMP_NEAR(0x005D3435, (INT32*)0x005D344C);

			BASE_EffectMagic(true);
			AffectIconLimit();

			VirtualProtect((int*)0x0401000, 0x5F0FFF - 0x0401000, dwOldProtectFlag_text, &dwOldProtectFlag_text);
			break;
		}

		case DLL_PROCESS_DETACH:
		{
			FreeLibrary(hInstDLL);
			break;
		}

		}
	}
	__except (GetExceptionCode())
	{

	}

	return TRUE;
}