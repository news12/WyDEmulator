#include "AntCheat.h"
#include "BaseCli.h"
#include "main.h"

bool ReadConfig(const char* FileName)
{
	FILE* pFile = NULL;


	pFile = fopen(FileName, "r");


	if (pFile != NULL)
	{
		return true;
	}
	// isso � o anti hacker, que vai pro cliente dentro da DLL ta lgd ?
	return false;
}

unsigned static long dwRecvCall; // Addr do in�cio da func Recv
unsigned static long dwSendCall; // Addr do in�cio da func Send
unsigned static char bAddr_r[6], bAddr_s[6]; // Bytes iniciais das fun��es send/recv

void BackupWinsockData() {
	LoadLibrary("ws2_32.dll"); // Hook na dll da winsock2
	dwRecvCall = (unsigned long)GetProcAddress(GetModuleHandle("ws2_32.dll"), "recv"); // Seta o valor de dwRecvCall com o addrbase da func Recv
	dwSendCall = (unsigned long)GetProcAddress(GetModuleHandle("ws2_32.dll"), "send"); // Seta o valor de dwSendCall com o addrbase da func Send
	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwRecvCall, bAddr_r, 6, 0); // Move os bytes iniciais originais da func recv para o buffer
	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwSendCall, bAddr_s, 6, 0); // Move os bytes iniciais originais da func send para o buffer
}
void CloseGame() {
	DWORD exitCode;
	GetExitCodeProcess(GetCurrentProcess(), &exitCode);
	ExitProcess(exitCode);
}
void WINAPI AntiHack() {
	while (true) {
		if (memcmp((LPVOID)dwRecvCall, bAddr_r, 6) != 0) CloseGame(); // Verifica se os bytes iniciais da func Recv est�o diferentes do original
		if (memcmp((LPVOID)dwSendCall, bAddr_s, 6) != 0) CloseGame(); // Verifica se os bytes iniciais da func Send est�o diferentes do original
		Sleep(1000); // Delay para n�o dar lag
	}
}
unsigned long __stdcall AntiWPEPro(void* pVoid)
{
	bool bHooked = false;
	unsigned char szBuffer[8];

	// First 6 bytes of of Send/Recv
	unsigned char bOriginal[] = "\x55"         // PUSH EBP
		"\x8B\xEC\x83"   // MOV EBP, ESP
		"\xEC\x10";   // SUB ESP, 10

	int i;

	unsigned long dwRecvCall = (unsigned long)GetProcAddress(GetModuleHandle("WS2_32.dll"), "recv");
	unsigned long dwSendCall = (unsigned long)GetProcAddress(GetModuleHandle("WS2_32.dll"), "send");

	while (true)
	{
		ReadProcessMemory(GetCurrentProcess(), (void*)dwRecvCall, szBuffer, 6, 0);

		for (i = 0; i < 6; i++)
		{
			// If we find one part missing, write the original bytes back and break the loop
			if (bOriginal[i] != szBuffer[i])
			{
				WriteProcessMemory(GetCurrentProcess(), (void*)dwRecvCall, bOriginal, 6, 0);
				break;
			}
		}

		ReadProcessMemory(GetCurrentProcess(), (void*)dwSendCall, szBuffer, 6, 0);

		for (i = 0; i < 6; i++)
		{
			// Send + Recvs first 6 bytes are the same, we can use the same buffer
			if (bOriginal[i] != szBuffer[i])
			{
				WriteProcessMemory(GetCurrentProcess(), (void*)dwSendCall, bOriginal, 6, 0);
				break;
			}
		}

		Sleep(500);
	}

	return 0;
};


void I_loop()
{
	// [NAME.extension] Are NON case-sensitive.
	if (GetModuleHandle("speedhack.dll") ||
		(GetModuleHandle("speed-hack.dll")) ||
		(GetModuleHandle("speed-hack.dll")) ||
		(GetModuleHandle("speed_hack.dll")) ||
		(GetModuleHandle("hack_speed.dll")) ||
		(GetModuleHandle("hack-speed.dll")) ||
		(GetModuleHandle("hackspeed.dll")) ||
		(GetModuleHandle("hack.dll")) ||
		(GetModuleHandle("wpepro.dll")) ||
		(GetModuleHandle("Cr4ck3r.dll")) ||
		(GetModuleHandle("wpeprospy.dll")) ||
		(GetModuleHandle("engine.dll")) ||
		(GetModuleHandle("CheatEngine.dll")) ||
		(GetModuleHandle("c.e.dll")) ||
		(GetModuleHandle("cheat.dll")) ||
		(GetModuleHandle("mukilin.dll")) ||
		(GetModuleHandle("Whook.dll")) ||
		(GetModuleHandle("whook7556.dll")) ||
		(GetModuleHandle("hook.dll")) ||
		(GetModuleHandle("wHook.dll")) ||
		(GetModuleHandle("Hook756.dll")) ||
		(GetModuleHandle("WHOOK.dll")) ||
		(GetModuleHandle("whook756.dll")) ||
		(GetModuleHandle("whook.dll"))
		)
	{
		Injetado();
	}
	else
		Sleep(100);
}

void Msg_I_Br()
{
	MessageBoxA(NULL, "AntiHacker\n\nA integridade do processo foi corrompida!", Config.MsgBox_Title, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Injetado()
{

	if (Config.EnableLogFile == 1)
	{
		using namespace std;
		ofstream out("WYD.log", ios::app);
		out << "\n AntiHacker:  ", out << "File integrity violated!";
	}
	if (Config.SendClientMsg == 2)
	{
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_I_Br), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (Config.SendClientMsg == 0)
	{
		ExitProcess(0);
	}
	else
		ExitProcess(0);
}

void I_Scan()
{
again:
	I_loop();
	Sleep(58000);
	goto again;
}

void Dll_Inject()
{
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(I_Scan), NULL, 0, 0);
}

void Msg_W_Br()
{
	MessageBoxA(NULL, "AntiHacker\n\nConte�do suspeito detectado!", Config.MsgBox_Title, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}


bool TitleWindow(LPCSTR WindowTitle)
{
	HWND WinTitle = FindWindowA(NULL, WindowTitle);
	if (WinTitle > 0)
	{

		if (Config.EnableLogFile == 1)
		{
			using namespace std;
			ofstream out("WYD.log", ios::app);
			out << "\n AntiHacker:  ", out << WindowTitle;
		}
		if (Config.SendClientMsg == 2)
		{
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_W_Br), NULL, 0, 0);
			Sleep(5000);
			ExitProcess(0);
		}
		if (Config.SendClientMsg == 0)
		{
			ExitProcess(0);
		}
		else
			ExitProcess(0);
		return false;
	}
	return true;
}


void TitleCheckWindow()
{
	TitleWindow("Cheat Engine 5.0");
	TitleWindow("Cheat Engine 5.1");
	TitleWindow("Cheat Engine 5.1.1");
	TitleWindow("Cheat Engine 5.2");
	TitleWindow("Cheat Engine 5.3");
	TitleWindow("Cheat Engine 5.4");
	TitleWindow("Cheat Engine 5.5");
	TitleWindow("Cheat Engine 5.6");
	TitleWindow("Cheat Engine 5.6.1");
	TitleWindow("Cheat Engine 6.0");
	TitleWindow("Cheat Engine 6.1");
	TitleWindow("Cheat Engine 6.2");
	TitleWindow("Cheat Engine 6.3");
	TitleWindow("Cheat Engine 6.4");
	TitleWindow("Cheat Engine 6.5");
	TitleWindow("Cheat Engine 7.1");
	TitleWindow("Cheat Engine");
	TitleWindow("WPE PRO");
	TitleWindow("WPePro 0.9a");
	TitleWindow("WPePro 1.3");
}

void W_Scan()
{
again:
	TitleCheckWindow();
	Sleep(1000);
	goto again;
}

void YProtectionMain()
{
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(W_Scan), NULL, 0, 0);
}

DWORD __forceinline IsInsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep)
{
	PCONTEXT ctx = ep->ContextRecord;

	ctx->Ebx = -1;
	ctx->Eip += 4;
	return EXCEPTION_CONTINUE_EXECUTION;
}

bool IsInsideVPC()
{
	bool rc = false;

	__try
	{
		_asm push ebx
		_asm mov  ebx, 0
		_asm mov  eax, 1


		_asm __emit 0Fh
		_asm __emit 3Fh
		_asm __emit 07h
		_asm __emit 0Bh

		_asm test ebx, ebx
		_asm setz[rc]
			_asm pop ebx
	}

	__except (IsInsideVPC_exceptionFilter(GetExceptionInformation()))
	{
	}

	return rc;
}

bool IsInsideVMWare()
{
	bool rc = true;

	__try
	{
		__asm
		{
			push   edx
			push   ecx
			push   ebx

			mov    eax, 'VMXh'
			mov    ebx, 0
			mov    ecx, 10
			mov    edx, 'VX'

			in     eax, dx

			cmp    ebx, 'VMXh'
			setz[rc]

			pop    ebx
			pop    ecx
			pop    edx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		rc = false;
	}

	return rc;
}




