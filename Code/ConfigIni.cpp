#include "ConfigIni.h"
#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "Basedef.h"
#include <json.hpp>
#include "DBSrv/CFileDB.h"

using namespace std;
using ConfigIni::nConfig;
using json = nlohmann::json;
STRUCT_MOB g_MobBase[];
STRUCT_TREASURE ng_pTreasure[];
STRUCT_EVENTS eEvents;
STRUCT_QUIZ eQuiz[];
STRUCT_ITEM premioLojaAfk;
int jsonSancRate[3][12];
int TOTAL_QUIZ;
int goldQuiz;
long int expQuiz;
int QuizOn;
int SortQuiz;
unsigned int ipAdmin[];
unsigned int CharaCreate[];
//Maximo de config 100 maximo de subconfig 50
short gameConfig[maxGameConfig][MaxSubConfig];
//PATH Folders, difinir extern no basedef.h
const string PATH_COMMON = "../../Common/";
const string PATH_DB = "../../DBSrv/";
const string PATH_TM = "../../TMSrv/";
const string PATH_CONFIG = "Config/";
const string PATH_SETTINGS = PATH_COMMON + "Settings/";
const string PATH_EVENTS = PATH_COMMON + "Events/";
const string PATH_EVENT_VemProEternal = PATH_EVENTS + "VemProEternal/";
const string PATH_EVENT_LojaAfk = PATH_EVENTS + "LojaAfk/";
//Files Json, definir extern no basedef.h
const string ConfigJson = "config.json";
const string GameConfig = "gameConfig.json";

enum  keyName : char
{
	CONFIG,
	SERVERLIST,
	ADMIN
};
/*
enum eGameConfig 
{
	DROP_ITEM_EVENT,
	ETC_EVENT,
	BILLING,
	ITEM_DROP_BONUS,
	TREASURE,
	ETC
};*/

void nConfig::findAndReplaceAll(std::string& data, std::string& match, const std::string& replace)
{
	// pega a primeira ocorrência
	size_t pos = data.find(match);

	// Repete até o fim
	while (pos != std::string::npos)
	{
		data.replace(pos, match.size(), replace);

		// pega a próxima ocorrência da posição atual
		pos = data.find(match, pos + replace.size());
	}
}

int nConfig::ReadEventsEternal(string path, string file, int key)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteEventsEternal(PATH_EVENT_VemProEternal, file, key, 0);

		if (!creat)
			return creat;
	}

	ifstream spath(fullpath);
	json nJson;
	spath >> nJson;

	switch (key)
	{
	case VemProEternal:
		//eEvents.name = (char*)file.c_str();
		nJson["EVENTSETERNAL"]["VemProEternal"].get_to(eEvents.eventValue);
		break;
	default:
		break;
	}

}
int nConfig::WriteEventsEternal(string path, string file, int key, int nValue)
{

	string fullpath = path + file;

#pragma region Txt New playerEvent.json
	auto nJson = R"(
{
"EVENTSETERNAL": {
					"VemProEternal": 0

				 }
	
})"_json;

#pragma endregion

	
	switch (key)
		{
		case VemProEternal:
			nJson["EVENTSETERNAL"]["VemProEternal"] = nValue;
			break;
		case 99:
			break;
		default:
			break;
		}

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadQuiz(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteQuiz(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	ifstream spath(fullpath);
	json nJson;
	spath >> nJson;

	nJson["CONFIG"]["ToTalQuiz"].get_to(TOTAL_QUIZ);
	nJson["CONFIG"]["GOLD"].get_to(goldQuiz);
	nJson["CONFIG"]["EXP"].get_to(expQuiz);

	for (auto& x : nJson["QUESTIONS"].items())
	{
		string Title = x.value().find("Title").value();
		int tLength = Title.size();
		int Correct = x.value().find("Correct").value();
		string Answer0 = x.value().find("Answer0").value();
		int tA0 = Answer0.size();
		string Answer1 = x.value().find("Answer1").value();
		int tA1 = Answer1.size();
		string Answer2 = x.value().find("Answer2").value();
		int tA2 = Answer2.size();
		string Answer3 = x.value().find("Answer3").value();
		int tA3 = Answer3.size();

		char* cTitle = new char[tLength +1];
		copy(Title.begin(), Title.end(), cTitle);
		cTitle[tLength] = '\0';
		eQuiz[stoi(x.key())].Title = cTitle;

		eQuiz[stoi(x.key())].Correct = Correct;

		char* cA0 = new char[tA0 + 1];
		copy(Answer0.begin(), Answer0.end(), cA0);
		cA0[tA0] = '\0';
		eQuiz[stoi(x.key())].Answer0 = cA0;

		char* cA1 = new char[tA1 + 1];
		copy(Answer1.begin(), Answer1.end(), cA1);
		cA1[tA1] = '\0';
		eQuiz[stoi(x.key())].Answer1 = cA1;

		char* cA2 = new char[tA2 + 1];
		copy(Answer2.begin(), Answer2.end(), cA2);
		cA2[tA2] = '\0';
		eQuiz[stoi(x.key())].Answer2 = cA2;

		char* cA3 = new char[tA3 + 1];
		copy(Answer3.begin(), Answer3.end(), cA3);
		cA3[tA3] = '\0';
		eQuiz[stoi(x.key())].Answer3 = cA3;

	};
	return TRUE;
	
}

int ConfigIni::nConfig::WriteQuiz(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New quiz.json
	auto nJson = R"(
{
"CONFIG": {
			"GOLD": 10000,
			"EXP": 100000,
			"ToTalQuiz": 3
		  },
"QUESTIONS": [
				{
					"Title": "Qual classe evoca monstros?",
					"Correct": 1,
					"Answer0": "Foema",
					"Answer1": "BeastMaster",
					"Answer2": "Transknight",
					"Answer3": "Huntress"
				},
				{
					"Title": "Em qual cidade fica a Zona Elemental da Agua?",
					"Correct": 0,
					"Answer0": "Arzam",
					"Answer1": "Armia",
					"Answer2": "Erion",
					"Answer3": "Noatum"
				},
				{
					"Title": "Qual o nome do Servidor?",
					"Correct": 3,
					"Answer0": "Eternity",
					"Answer1": "7DY",
					"Answer2": "WYD",
					"Answer3": "ETERNAL"
				}
			]
	
	
})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadSancRate(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteSancRate(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	ifstream spath(fullpath);
	json nJson;
	spath >> nJson;

	for (auto& x : nJson["SANC"]["ORI"].items())
	{
		x.value().get_to(jsonSancRate[0][stoi(x.key())]);
	}

	for (auto& x : nJson["SANC"]["LAC"].items())
	{
		x.value().get_to(jsonSancRate[1][stoi(x.key())]);
	}

	for (auto& x : nJson["SANC"]["AMAGO"].items())
	{
		x.value().get_to(jsonSancRate[2][stoi(x.key())]);
	}

	memmove(g_pSancRate, jsonSancRate, sizeof(g_pSancRate));

	return TRUE;
}

int ConfigIni::nConfig::WriteSancRate(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New sancRate.json
	auto nJson = R"(
{
"SANC": {
		"ORI": {
				"0":100,
				"1":100,
				"2":100,
				"3":85,
				"4":70,
				"5":50,
				"6":00,
				"7":00,
				"8":00,
				"9":00,
				"10":00,
				"11":00
				},
		"LAC": {
				"0":100,
				"1":100,
				"2":100,
				"3":100,
				"4":100,
				"5":100,
				"6":70,
				"7":60,
				"8":30,
				"9":10,
				"10":00,
				"11":00
				},
				
		"AMAGO": {
				"0":100,
				"1":100,
				"2":100,
				"3":100,
				"4":100,
				"5":100,
				"6":70,
				"7":60,
				"8":30,
				"9":10,
				"10":10,
				"11":05
				}

		}

})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadPremioLojaAfk(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	memset(&premioLojaAfk, 0, sizeof(STRUCT_ITEM));

	if (fp == NULL) {
		
		premioLojaAfk.sIndex = 475;
		return FALSE;
	}

	ifstream spath(fullpath);
	json nJson;
	spath >> nJson;
	vector<short> itemPremio;
	nJson["SHOP"]["Item"].get_to(itemPremio);

	premioLojaAfk.sIndex = itemPremio[0];
	premioLojaAfk.stEffect->sValue = itemPremio[1];
	premioLojaAfk.stEffect[0].cEffect = itemPremio[2];
	premioLojaAfk.stEffect[0].cValue = itemPremio[3];
	premioLojaAfk.stEffect[1].cEffect = itemPremio[4];
	premioLojaAfk.stEffect[1].cValue = itemPremio[5];
	premioLojaAfk.stEffect[2].cEffect = itemPremio[6];
	premioLojaAfk.stEffect[2].cValue = itemPremio[7];
}

int nConfig::ReadGameConfig(string path, string file, int key)
{
	string fullpath = path + file;
	short itemDropBonus[64];
	STRUCT_TREASURE treasure[8];
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		//gameConfig.json não encontrado, será criado um novo(default) no diretorio config/
		int creat = WriteGameConfig(PATH_CONFIG, "gameConfig.json", 0);

		if (!creat)
			return creat;
	}

	ifstream spath(fullpath);
	json nJson;
	spath >> nJson;

	switch (key)
	{
	case DROP_ITEM_EVENT:
		nJson["DROP_ITEM_EVENT"]["evIndex"].get_to(gameConfig[DROP_ITEM_EVENT][0]);
		nJson["DROP_ITEM_EVENT"]["evDelete"].get_to(gameConfig[DROP_ITEM_EVENT][1]);
		nJson["DROP_ITEM_EVENT"]["evOn"].get_to(gameConfig[DROP_ITEM_EVENT][2]);
		nJson["DROP_ITEM_EVENT"]["evItem"].get_to(gameConfig[DROP_ITEM_EVENT][3]);
		nJson["DROP_ITEM_EVENT"]["evRate"].get_to(gameConfig[DROP_ITEM_EVENT][4]);
		nJson["DROP_ITEM_EVENT"]["evStartIndex"].get_to(gameConfig[DROP_ITEM_EVENT][5]);
		nJson["DROP_ITEM_EVENT"]["evCurrentIndex"].get_to(gameConfig[DROP_ITEM_EVENT][6]);
		nJson["DROP_ITEM_EVENT"]["evEndIndex"].get_to(gameConfig[DROP_ITEM_EVENT][7]);
		nJson["DROP_ITEM_EVENT"]["evNotice"].get_to(gameConfig[DROP_ITEM_EVENT][8]);
		break;
	case ETC_EVENT:
		nJson["ETC_EVENT"]["DOUBLEMODE"].get_to(gameConfig[ETC_EVENT][0]);
		nJson["ETC_EVENT"]["DEADPOINT"].get_to(gameConfig[ETC_EVENT][1]);
		nJson["ETC_EVENT"]["DUNGEONEVENT"].get_to(gameConfig[ETC_EVENT][2]);
		nJson["ETC_EVENT"]["StatSpapphire"].get_to(gameConfig[ETC_EVENT][3]);
		nJson["ETC_EVENT"]["BatleRoyalItem"].get_to(gameConfig[ETC_EVENT][4]);
		break;
	case nBILLING:
		nJson["BILLING"]["BILLING"].get_to(gameConfig[nBILLING][0]);
		nJson["BILLING"]["FREEEXP"].get_to(gameConfig[nBILLING][1]);
		nJson["BILLING"]["CHARSELBILL"].get_to(gameConfig[nBILLING][2]);
		nJson["BILLING"]["POTIONCOUNT"].get_to(gameConfig[nBILLING][3]);
		nJson["BILLING"]["PARTYBONUS"].get_to(gameConfig[nBILLING][4]);
		nJson["BILLING"]["GUILDBOARD"].get_to(gameConfig[nBILLING][5]);
		break;
	case ITEM_DROP_BONUS:
		nJson["ITEM_DROP_BONUS"].get_to(itemDropBonus);
		memmove(&gameConfig[ITEM_DROP_BONUS], &itemDropBonus, sizeof(itemDropBonus));
		break;
	case TREASURE:
		for (auto& x : nJson["TREASURE"].items())
		{
			for (auto& e : x.value().items())
			{
				vector<short> ntreasure = e.value();

				treasure->Source = stoi(x.key());
				treasure->Rate[stoi(e.key())] = ntreasure[5];
				treasure->Target[stoi(e.key())].sIndex = ntreasure[0];
				treasure->Target[stoi(e.key())].stEffect[0].cEffect = ntreasure[1];
				treasure->Target[stoi(e.key())].stEffect[0].cValue = ntreasure[2];
				treasure->Target[stoi(e.key())].stEffect[1].cEffect = ntreasure[3];
				treasure->Target[stoi(e.key())].stEffect[1].cValue = ntreasure[4];
			//	memmove(&treasure[stoi(x.key())][stoi(e.key())], &ntreasure, sizeof(ntreasure));
			}

			memmove(&ng_pTreasure[stoi(x.key())], &treasure, sizeof(STRUCT_TREASURE));

		};
		break;
	case OTHER:
		nJson["OTHER"]["PARTY_DIF"].get_to(gameConfig[OTHER][0]);
		nJson["OTHER"]["KefraLive"].get_to(gameConfig[OTHER][1]);
		nJson["OTHER"]["GTorreHour"].get_to(gameConfig[OTHER][2]);
		nJson["OTHER"]["isDropItem"].get_to(gameConfig[OTHER][3]);
		nJson["OTHER"]["BableRoyalRHour"].get_to(gameConfig[OTHER][4]);
		nJson["OTHER"]["maxNightmare"].get_to(gameConfig[OTHER][5]);
		nJson["OTHER"]["PotionDelay"].get_to(gameConfig[OTHER][6]);
		break;
	default:
		break;
	}

	return TRUE;
}

int nConfig::WriteGameConfig(string path, string file, int key)
{

	std::string fullpath = path + file;

#pragma region Txt New gameConfig.json
	auto nJson = R"(
{
"DROP_ITEM_EVENT": {
					"evIndex": 1,
					"evDelete": 0,
					"evOn": 0,
					"evItem": 475,
					"evRate": 40,
					"evStartIndex": 1,
					"evCurrentIndex": 126,
					"evEndIndex": 30000,
					"evNotice": 1
				   },
"ETC_EVENT": {
				"DOUBLEMODE": 0,
				"DEADPOINT": 1,
				"DUNGEONEVENT": 0,
				"StatSpapphire": 30,
				"BatleRoyalItem": 0
			},
"BILLING": {
			"BILLING": 0,
			"FREEEXP": 35,
			"CHARSELBILL": 0,
			"POTIONCOUNT": 100,
			"PARTYBONUS": 82,
			"GUILDBOARD": 0
		   },
"ITEM_DROP_BONUS": [
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100
				  ],
"TREASURE": {
				"0": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"1": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"2": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"3": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"4": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"5": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"6": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"7": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					 ]
			},
"OTHER": {
		"PARTY_DIF": 200,
		"KefraLive": 0,
		"GTorreHour": 21,
		"isDropItem": 0,
		"BableRoyalRHour": 19,
		"maxNightmare": 3,
		"PotionDelay": 500
	  }

})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}


}

int nConfig::ReadExtra(string path, string file, int key)
{
	string fullpath = path + file;

	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		//config.json não encontrado, será criado um novo(default) no diretorio config/
		int creat = WriteExtra(PATH_SETTINGS, "extra.json", 0);

		if (!creat)
			return creat;
	}

	ifstream spath(fullpath);
	json nJson;
	spath >> nJson;
	
	switch (key)
	{
	case MORTAL:
		nJson["CHARACTER_CREATE"]["MORTAL"].get_to(CharaCreate[MORTAL]);
		break;

	case ARCH:
		nJson["CHARACTER_CREATE"]["ARCH"].get_to(CharaCreate[ARCH]);
		break;

	case CELESTIAL:
		nJson["CHARACTER_CREATE"]["CELESTIAL"].get_to(CharaCreate[CELESTIAL]);
		break;

	case CELESTIALCS:
		nJson["CHARACTER_CREATE"]["CELESTIALCS"].get_to(CharaCreate[CELESTIALCS]);
		break;

	case SCELESTIAL:
		nJson["CHARACTER_CREATE"]["SCELESTIAL"].get_to(CharaCreate[SCELESTIAL]);
		break;

	default:
		break;
	}

	return TRUE;
}

int nConfig::WriteExtra(string path, string file, int key)
{
	std::string fullpath = path + file;
	FILE* fp = fopen(fullpath.c_str(), "rt");

#pragma region Txt New Extra
	auto text = R"({
"CHARACTER_CREATE": {
			"MORTAL": 1,
			"ARCH": 1,
			"CELESTIAL": 1,
			"CELESTIALCS": 1,
			"SCELESTIAL": 1
		},
"CLASS_CREATE": {
			"TK": 1,
			"FM": 1,
			"BM": 1,
			"HT": 1
		}

}
    )";
#pragma endregion

	if (fp == NULL)
	{
		fprintf(fp, text, 0);
		fclose(fp);

		return TRUE;
	};

	ifstream spath(fullpath);
	json nJson;
	spath >> nJson;
	int nvalor = CharaCreate[key] + 1;
	switch (key)
	{
	case MORTAL:
		nJson["CHARACTER_CREATE"]["MORTAL"] = nvalor;
		break;

	case ARCH:
		nJson["CHARACTER_CREATE"]["ARCH"] = nvalor;
		break;

	case CELESTIAL:
		nJson["CHARACTER_CREATE"]["CELESTIAL"] = nvalor;
		break;

	case CELESTIALCS:
		nJson["CHARACTER_CREATE"]["CELESTIALCS"] = nvalor;
		break;

	case SCELESTIAL:
		nJson["CHARACTER_CREATE"]["SCELESTIAL"] = nvalor;
		break;

	default:
		break;
	}

	ofstream bjson(fullpath);
	bjson << setw(4) << nJson << std::endl;
	return TRUE;

}

#pragma region Config Json
int nConfig::ReadConfigNews(string path, string file, int key)
{
	string fullpath = path + file;

	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		//config.json não encontrado, será criado um novo(default) no diretorio config/
		int creat = WriteConfigNews(PATH_SETTINGS, ConfigJson, 0);
		
		if (!creat)
			return creat;
	}

	ifstream spath(fullpath);
	json nJson;
	spath >> nJson;
	GroupServer Server0;
	GroupServer Server1;
    GroupServer Server2;
		
	try
	{

	
		switch (key)
		{
		case CONFIG:
			nJson["CONFIG"]["Sapphire"].get_to(Sapphire);
			nJson["CONFIG"]["LastCapsule"].get_to(LastCapsule);
			break;
		case SERVERLIST:
			nJson["SERVERLIST"]["MaxServer"].get_to(MaxServer);
			nJson["SERVERLIST"]["MaxServerGroup"].get_to(MaxServerGroup);
			nJson["SERVERLIST"]["MaxServerNumber"].get_to(MaxServerNumber);

			for (auto& x : nJson["SERVERLIST"]["IPLIST"].items())
			{
				int group = x.value().find("ServerGroup").value();
				int number = x.value().find("ServerNumber").value();
				string address = x.value().find("Address").value();

				strcpy(g_pServerList[group][number], address.c_str());
			};
			
			break;
		case ADMIN:
			int a, b, c, d;
			a = b = c = d = 0;
			for (auto& x : nJson["ADMIN"].items())
			{
				string remov = ".";
				string inc = " ";
				string ip = x.value();

				findAndReplaceAll(ip, remov, inc);
		
				sscanf(ip.c_str(), "%d %d %d %d", &a, &b, &c, &d);

				unsigned int ip_decimal = (d << 24) + (c << 16) + (b << 8) + a;

			ipAdmin[stoi(x.key())] = ip_decimal;
			
			};

			break;
		default:
			break;
		}
		

		return TRUE;

	}
	catch (json::parse_error& e)
	{
		// output exception information
		std::cout << "message: " << e.what() << '\n'
			<< "exception id: " << e.id << '\n'
			<< "byte position of error: " << e.byte << std::endl;
		return FALSE;
	}
}

int nConfig::WriteConfigNews(std::string path, std::string file, int key)
{
	std::string fullpath = path + file;
	FILE* fp = fopen(fullpath.c_str(), "wt");

	if (fp == NULL)
		return FALSE;

	ifstream spath(fullpath);
	json nJson;

#pragma region Txt New config
	auto text = R"({
	"CONFIG": {
		"Sapphire": 8,
		"LastCapsule": 0
	},
	"SERVERLIST": {
		"MaxServer": 10,
		"MaxServerGroup": 10,
		"MaxServerNumber": 11,
		"IPLIST": [
					{
						"ServerGroup": 0,
						"ServerNumber": 0,
						"Address": "192.168.0.102"
					},
					{
						"ServerGroup": 0,
						"ServerNumber": 1,
						"Address": "192.168.0.102"
					},
					{
						"ServerGroup": 0,
						"ServerNumber": 2,
						"Address": "192.168.0.102"
					}
				]
			
			},
	"ADMIN": {
				
				"0": "192.168.0.102"
			 }
		}
    )";
#pragma endregion
	switch (key)
	{
	case CONFIG:
		fprintf(fp, text, 0);
		fclose(fp);

		return TRUE;
		break;
	default:
		break;
	}
	
	
}

#pragma endregion

#pragma region Config baseMob
int nConfig::ReadbaseMob(string path, string file, int key)
{
	char Class[4][2] = {
		{'T','K'},
		{'F','M'},
		{'B','M'},
		{'H','T'}
	};

	string className;
	short equipSlot[16][8];
	string fullpath = path + file;

	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		//baseMob.json não encontrado
		return FALSE;
	}

	ifstream spath(fullpath);
	json nJson;
	spath >> nJson;

	for (int i = 0; i < 2; i++)
	{
		g_MobBase[0].MobName[i] = Class[key][i];
	}

	switch (key)
	{
	case TK:
		className = "TK";
		break;
	case FM:
		className = "FM";
		break;
	case BM:
		className = "BM";
		break;
	case HT:
		className = "HT";
		break;
	default:
		break;
	}

	//Base
	nJson[className]["Merchant"].get_to(g_MobBase[key].Merchant);
	nJson[className]["Guild"].get_to(g_MobBase[key].Guild);
	nJson[className]["Class"].get_to(g_MobBase[key].Class);
	nJson[className]["Coin"].get_to(g_MobBase[key].Coin);
	nJson[className]["Exp"].get_to(g_MobBase[key].Exp);
	nJson[className]["SPX"].get_to(g_MobBase[key].SPX);
	nJson[className]["SPY"].get_to(g_MobBase[key].SPY);
	//BaseScore
	nJson[className]["BaseScore"].find("Level").value().get_to(g_MobBase[key].BaseScore.Level);
	nJson[className]["BaseScore"].find("Ac").value().get_to(g_MobBase[key].BaseScore.Ac);
	nJson[className]["BaseScore"].find("Damage").value().get_to(g_MobBase[key].BaseScore.Damage);
	nJson[className]["BaseScore"].find("Merchant").value().get_to(g_MobBase[key].BaseScore.Merchant);
	nJson[className]["BaseScore"].find("AttackRun").value().get_to(g_MobBase[key].BaseScore.AttackRun);
	nJson[className]["BaseScore"].find("Direction").value().get_to(g_MobBase[key].BaseScore.Direction);
	nJson[className]["BaseScore"].find("ChaosRate").value().get_to(g_MobBase[key].BaseScore.ChaosRate);
	nJson[className]["BaseScore"].find("MaxHp").value().get_to(g_MobBase[key].BaseScore.MaxHp);
	nJson[className]["BaseScore"].find("MaxMp").value().get_to(g_MobBase[key].BaseScore.MaxMp);
	nJson[className]["BaseScore"].find("Hp").value().get_to(g_MobBase[key].BaseScore.Hp);
	nJson[className]["BaseScore"].find("Mp").value().get_to(g_MobBase[key].BaseScore.Mp);
	nJson[className]["BaseScore"].find("Str").value().get_to(g_MobBase[key].BaseScore.Str);
	nJson[className]["BaseScore"].find("Int").value().get_to(g_MobBase[key].BaseScore.Int);
	nJson[className]["BaseScore"].find("Dex").value().get_to(g_MobBase[key].BaseScore.Dex);
	nJson[className]["BaseScore"].find("Con").value().get_to(g_MobBase[key].BaseScore.Con);
	nJson[className]["BaseScore"].find("Special1").value().get_to(g_MobBase[key].BaseScore.Special[0]);
	nJson[className]["BaseScore"].find("Special2").value().get_to(g_MobBase[key].BaseScore.Special[1]);
	nJson[className]["BaseScore"].find("Special3").value().get_to(g_MobBase[key].BaseScore.Special[2]);
	nJson[className]["BaseScore"].find("Special4").value().get_to(g_MobBase[key].BaseScore.Special[3]);
	//passar o baseScore para CurrentScore
	memmove(&g_MobBase[key].CurrentScore, &g_MobBase[key].BaseScore, sizeof(STRUCT_SCORE));
	//Equip
	nJson[className]["Equip"].find("Face").value().get_to(equipSlot[0]);
	nJson[className]["Equip"].find("Helmet").value().get_to(equipSlot[1]);
	nJson[className]["Equip"].find("Armor").value().get_to(equipSlot[2]);
	nJson[className]["Equip"].find("Pant").value().get_to(equipSlot[3]);
	nJson[className]["Equip"].find("Glove").value().get_to(equipSlot[4]);
	nJson[className]["Equip"].find("Boot").value().get_to(equipSlot[5]);
	nJson[className]["Equip"].find("Weapon").value().get_to(equipSlot[6]);
	nJson[className]["Equip"].find("Shield").value().get_to(equipSlot[7]);
	nJson[className]["Equip"].find("Ring").value().get_to(equipSlot[8]);
	nJson[className]["Equip"].find("Amulet").value().get_to(equipSlot[9]);
	nJson[className]["Equip"].find("Orb").value().get_to(equipSlot[10]);
	nJson[className]["Equip"].find("Stone").value().get_to(equipSlot[11]);
	nJson[className]["Equip"].find("Guild").value().get_to(equipSlot[12]);
	nJson[className]["Equip"].find("Pixie").value().get_to(equipSlot[13]);
	nJson[className]["Equip"].find("Mount").value().get_to(equipSlot[14]);
	nJson[className]["Equip"].find("Mantle").value().get_to(equipSlot[15]);
	//for passando em todos os itens/slot e pegando os dados do array
	for (size_t i = 0; i < 16; i++)
	{
		g_MobBase[key].Equip[i].sIndex = equipSlot[i][0];
		g_MobBase[key].Equip[i].stEffect->sValue = equipSlot[i][1];
		g_MobBase[key].Equip[i].stEffect[0].cEffect = equipSlot[i][2];
		g_MobBase[key].Equip[i].stEffect[0].cValue = equipSlot[i][3];
		g_MobBase[key].Equip[i].stEffect[1].cEffect = equipSlot[i][4];
		g_MobBase[key].Equip[i].stEffect[1].cValue = equipSlot[i][5];
		g_MobBase[key].Equip[i].stEffect[2].cEffect = equipSlot[i][6];
		g_MobBase[key].Equip[i].stEffect[2].cValue = equipSlot[i][7];
	};
	//for para pegar os itens inciais da mochila
	for (auto& x : nJson[className]["Bag"].items())
	{
		
		vector<short> equipBag = x.value();
		g_MobBase[key].Carry[stoi(x.key())].sIndex = equipBag[0];
		g_MobBase[key].Carry[stoi(x.key())].stEffect->sValue = equipBag[1];
		g_MobBase[key].Carry[stoi(x.key())].stEffect[0].cEffect = equipBag[2];
		g_MobBase[key].Carry[stoi(x.key())].stEffect[0].cValue = equipBag[3];
		g_MobBase[key].Carry[stoi(x.key())].stEffect[1].cEffect = equipBag[4];
		g_MobBase[key].Carry[stoi(x.key())].stEffect[1].cValue = equipBag[5];
		g_MobBase[key].Carry[stoi(x.key())].stEffect[2].cEffect = equipBag[6];
		g_MobBase[key].Carry[stoi(x.key())].stEffect[2].cValue = equipBag[7];

	};

	nJson[className]["LearnedSkill"].get_to(g_MobBase[key].LearnedSkill);
	nJson[className]["Magic"].get_to(g_MobBase[key].Magic);
	nJson[className]["ScoreBonus"].get_to(g_MobBase[key].ScoreBonus);
	nJson[className]["SpecialBonus"].get_to(g_MobBase[key].SpecialBonus);
	nJson[className]["SkillBonus"].get_to(g_MobBase[key].SkillBonus);
	nJson[className]["Critical"].get_to(g_MobBase[key].Critical);
	nJson[className]["SaveMana"].get_to(g_MobBase[key].SaveMana);
	nJson[className]["GuildLevel"].get_to(g_MobBase[key].GuildLevel);
	nJson[className]["RegenHP"].get_to(g_MobBase[key].RegenHP);
	nJson[className]["RegenMP"].get_to(g_MobBase[key].RegenMP);

	vector<short> skill;
	nJson[className]["SkillBar"].get_to(skill);
	for (size_t i = 0; i < 4 ; i++)
	{
		g_MobBase[key].SkillBar[i] = skill[i];
	}

	vector<short> resist;
	nJson[className]["Resist"].get_to(skill);
	for (size_t i = 0; i < 4; i++)
	{
		g_MobBase[key].Resist[i] = skill[i];
	}
}

#pragma endregion


