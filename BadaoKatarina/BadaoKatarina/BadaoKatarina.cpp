#pragma once
#include "Combo.h"
#include "Harass.h"
#include "Flee.h"
#include "Laneclear.h"
#include "LastHit.h"
#include "Auto.h"
#include "Config.h"
#include "BadaoKatarinaVariables.h"
#include <string>

PluginSetup("BadaoKatarina");

#pragma region config
//void MenuAndSpell()
//{
//	GGame->PrintChat("hello badao");
//}

#pragma endregion 
Vec3 position = Vec3(0,0,0);
int statge = 1;
int lasttick = 0;
PLUGIN_EVENT(void) OnGameUpdate()
{
	//string items;
	//for (ItemData data : Player->AllItems())
	//{
	//	items = items + " ; " + std::to_string(data.Id_) + "(" + data.Name_ +")";
	//}
	//GGame->PrintChat(items.c_str());
    //if (GGame->TickCount() - lasttick <= 5000)
	//	return;
	//lasttick = GGame->TickCount();
	//if (position == Vec3(0,0,0))
	//{
	//	position = GEntityList->Player()->GetPosition() + Vec3(100, 100, 100);
	//}
	//else if (statge == 1)
	//{
	//	GGame->IssueOrder(GEntityList->Player(), kMoveTo, position + Vec3(100, 100, 100));
	//	position = GEntityList->Player()->GetPosition();
	//	statge = 2;
	//}
	//else
	//{
	//	GGame->IssueOrder(GEntityList->Player(), kMoveTo, position - Vec3(100, 100, 100));
	//	position = GEntityList->Player()->GetPosition();
	//	statge = 1;
	//}
	ComboOnGameUpdate();
	HarassOnUpdate();
	FleeOnUpdate();
	LastHitOnUpdate();
	LaneClearOnUpdate();
	AutoOnUpdate();
}
PLUGIN_EVENT(void) OnCreateObject(IUnit* Source)
{
	if (Source->IsMissile() && GMissileData->GetCaster(Source) == Player)
	{
		if (Contains(GMissileData->GetName(Source), "katarinarmis"))
		{
			RMis.Add(Source);
			LastRMis = GGame->TickCount(); // in milisecond
		}
		if (Contains(GMissileData->GetName(Source), "katarinawdaggerarc"))
		{
			WMis.Add(Source);
		}
	}
	if (Contains(Source->GetObjectName(), "katarina_base_e_beam.troy"))
	{
		MyBeam.Add(Source);
	}
	if (Contains(Source->GetObjectName(), "katarina_base_w_indicator"))
	{
		Daggers.Add(KatarinaDagger(GGame->TickCount(), Source));
	}
}
PLUGIN_EVENT(void) OnDestroyObject(IUnit* Source)
{
	if (Source->IsMissile() && GMissileData->GetCaster(Source) == Player)
	{
		if (Contains(GMissileData->GetName(Source), "katarinarmis"))
		{
			RMis.RemoveAll([&](IUnit* i) {return i == Source; });
		}
		if (Contains(GMissileData->GetName(Source), "katarinawdaggerarc"))
		{
			WMis.RemoveAll([&](IUnit* i) {return i == Source; });
		}
	}
	if (Contains(Source->GetObjectName(), "katarina_base_e_beam.troy"))
	{
		MyBeam.RemoveAll([&](IUnit* i) {return i == Source; });
	}
	if (Contains(Source->GetObjectName(), "katarina_base_w_indicator"))
	{
		Daggers.RemoveAll([&](KatarinaDagger i) {return i.Dagger == Source; });
	}
}

PLUGIN_EVENT(void) OnRender()
{
	//for (IUnit* minion : EnemyMinions().ToVector())
	//{
	//	GRender->DrawOutlinedCircle(minion->GetPosition(), Vec4(255, 255, 0, 255), 200);
	//}

}
// Called when plugin is first loaded
PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	// Initializes global interfaces for core access
	PluginSDKSetup(PluginSDK);
	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, OnDestroyObject);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
	Init();
	MenuAndSpell();

}

// Called when plugin is unloaded
PLUGIN_API void OnUnload()
{
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, OnDestroyObject);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	MainMenu->Remove();
}