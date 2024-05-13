#include <string>
#include <thread>
#include <future>
#include <iostream>
#include "View.hpp"
#include "Cheats.h"
#include "OS-ImGui/OS-ImGui.h"

void Cheats::Run()
{	
	if (!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64))
		return;

	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;
	CEntity LocalEntity, ServerEntity;
	static int LocalPlayerControllerIndex = 1;
	LocalEntity.UpdateClientData();
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;
	if (!LocalEntity.UpdatePawn(LocalPawnAddress) )
		return;

	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;
		if (EntityAddress == LocalEntity.Controller.Address)
		{
			LocalPlayerControllerIndex = i;
			continue;
		}
		if (!Entity.UpdateController(EntityAddress))
			continue;
		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;
		if (Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;
		/*
		dust: 180 230 15
		inf:140 245 16
		*/
		if (Entity.IsAlive()!=0) {
			Vec2 temp;
			temp.x = 180 + Entity.Pawn.Pos.x / 15;
			temp.y = 230 -Entity.Pawn.Pos.y / 15;
			Gui.CircleFilled(temp, 5, ImColor(255,0,0,30),50);
		}
		/*
		if (Entity.IsAlive() != 0&&Entity.IsInScreen()) {
			Vec2 temp;
			temp.x = Entity.Pawn.ScreenPos.x;
			temp.y = Entity.Pawn.ScreenPos.y;
			Gui.CircleFilled(temp, 3, ImColor(139 ,139 ,122, 125), 50);
		}*/
	}
	
}
