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

		//DB
		static int ReadbaseMob(string path, string file, int key);
	
		//TM
		static int ReadGameConfig(string path, string file, int key);
		static int WriteGameConfig(string path, string file, int key);

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
