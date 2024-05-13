#define _CRT_SECURE_NO_WARNINGS
#include "Cheats.h"
#include "Offsets.h"
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <KnownFolders.h>
#include <ShlObj.h>
#include <stdio.h>
#include <thread>S
#include "OS-ImGui/OS-ImGui.h"
using namespace std;


void Exit()
{
	system("pause");
	exit(0);
}
int main()
{
	//SetConsoleOutputCP(CP_UTF8);

	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
	//SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

	auto ProcessStatus = ProcessMgr.Attach("cs2.exe");

	switch (ProcessStatus) {
	case 1:
		//SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		//cout << "[ERROR] Please launch the game first!" << endl;
		Exit();
	case 2:
		//SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		//cout << "[ERROR] Failed to hook process, please run the cheat as Administrator (Right click AimStar > Run as Adminstrator)." << endl;
		Exit();
	case 3:
		//SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		//cout << "[ERROR] Failed to get module address." << endl;
		Exit();
	default:
		break;
	}

	if (!Offset::UpdateOffsets())
	{
		//SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		//cout << "[ERROR] Failed to update offsets." << endl;
		Exit();
	}
	if (!gGame.InitAddress())
	{
		//SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		//cout << "[ERROR] Failed to call InitAddress()." << endl;
		Exit();
	}

	//cout << "[Game] Process ID: " << ProcessMgr.ProcessID << endl;
	//cout << "[Game] Client Address: " << gGame.GetClientDLLAddress() << endl;


	//cout << endl;
	//SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	//cout << "Cheat running successfully!" << endl;
	//SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
	/*cout << "=======[ Offset List ]=======" << endl;
	cout << setw(23) << left << "EntityList:" << setiosflags(ios::uppercase) << hex << Offset::EntityList << endl;
	cout << setw(23) << left << "Matrix:" << setiosflags(ios::uppercase) << hex << Offset::Matrix << endl;
	cout << setw(23) << left << "LocalPlayerController:" << setiosflags(ios::uppercase) << hex << Offset::LocalPlayerController << endl;
	cout << setw(23) << left << "ViewAngles:" << setiosflags(ios::uppercase) << hex << Offset::ViewAngle << endl;
	cout << setw(23) << left << "LocalPlayerPawn:" << setiosflags(ios::uppercase) << hex << Offset::LocalPlayerPawn << endl;
	cout << setw(23) << left << "PlantedC4:" << setiosflags(ios::uppercase) << hex << Offset::PlantedC4 << endl;
	cout << setw(23) << left << "ForceJump:" << setiosflags(ios::uppercase) << hex << Offset::ForceJump << endl;
	cout << setw(23) << left << "Sensitivity:" << setiosflags(ios::uppercase) << hex << Offset::Sensitivity << endl;
	cout << endl;
	*/
	//SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

	//Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Cheats::Run);
	Gui.AttachAnotherWindow("反恐精英：全球攻势", "SDL_app", Cheats::Run);
	/*
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds
	while (1) {
		Cheats::Run();
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + seconds(1));
		cout << "-----------------------------------------------------" << std::endl;
	}
	*/
}