#pragma once
//用于将CS2三位世界二向箔打击,投影到观察者的屏幕上
#define Window_X 2880
#define Window_Y 1800
#include "OS-ImGui/OS-ImGui.h"
// 游戏视图类
class CView
{
public:
	float Matrix[4][4]{};

	bool WorldToScreen(const Vec3& Pos, Vec2& ToPos)
	{
		float View = 0.f;
		float SightX = Gui.Window.Size.x / 2, SightY = Gui.Window.Size.y / 2;

		View = Matrix[3][0] * Pos.x + Matrix[3][1] * Pos.y + Matrix[3][2] * Pos.z + Matrix[3][3];
		if (View <= 0)
			return false;

		ToPos.x = SightX + (Matrix[0][0] * Pos.x + Matrix[0][1] * Pos.y + Matrix[0][2] * Pos.z + Matrix[0][3]) / View * SightX;
		ToPos.y = SightY - (Matrix[1][0] * Pos.x + Matrix[1][1] * Pos.y + Matrix[1][2] * Pos.z + Matrix[1][3]) / View * SightY;
		if(ToPos.x> Window_X|| ToPos.x<0|| ToPos.y>Window_Y|| Window_Y<0)return false;
		return true;
	}
};
