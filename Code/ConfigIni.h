#ifndef __CONFIGINI__
#define __CONFIGINI__
#include <string>
#include <iostream>

using namespace std;
namespace ConfigIni {

	class nConfig
	{


	public:

		static void findAndReplaceAll(std::string& data, std::string& match, const std::string& replace);

		//COMMON
		static int ReadExtra(string path, string file, int key);
		static int WriteExtra(string path, string file, int key);
		static int ReadConfigNews(string path, string file, int key);
		static int WriteConfigNews(string path, string file, int key);
		static int ReadEventsEternal(string path, string file, int key);
		static int WriteEventsEternal(string path, string file, int key,int nValue);
		static int ReadQuiz(string path, string file);
		static int WriteQuiz(string path, string file);
		static int ReadSancRate(string path, string file);
		static int WriteSancRate(string path, string file);
		static int ReadPremioLojaAfk(string path, string file);
		static int ReadGroupItens(string path, string file);
		static int WriteGrupItens(string path, string file);
		static int ReadFadaAmmount(string path, string file);
		static int WriteFadaAmmount(string path, string file);
		static int ReadNPCBlock(string path, string file);
		static int WriteNPCBlock(string path, string file);
		static int ReadLottery(string path, string file);
		static int WriteLottery(string path, string file);
		static int ReadDropKefra(string path, string file);
		static int WriteDropKefra(string path, string file);
		static int ReadWarsTimer(string path, string file);
		static int WriteWarsTimer(string path, string file);
		static int ReadBoxEvent(string path, string file);
		static int WriteBoxEvent(string path, string file);
		static int ReadAltarOfKing(string path, string file);
		static int WriteAltarOfKing(string path, string file);
		static int ReadBagWarrior(string path, string file);
		static int WriteBagWarrior(string path, string file);
		static int ReadAutoEvent(string path, string file);
		static int WriteAutoEvent(string path, string file);
		
		//DB
		static int ReadbaseMob(string path, string file, int key);
	
		//TM
		static int ReadGameConfig(string path, string file);
		static int WriteGameConfig(string path, string file);
		static int ConvertNPC(string path, string file);
		static int ReadSombraNegra(string path, string file);
		static int WriteSombraNegra(string path, string file);
		static int ReadStatusSombraNegra(string path, string file);
		static int WriteStatusSombraNegra(string path, string file);

	static	struct GroupServer
		{
			int ServerGrup;
			int ServerNumber;
			const char* Address;
		};



	private:

	};


}






































#endif
