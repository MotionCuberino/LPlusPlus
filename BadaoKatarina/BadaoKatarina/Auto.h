#pragma once
#include "Helper.h"

inline void AutoOnUpdate()
{
	float endtime;
	if (AutoKs->Enabled() && !(GOrbwalking->GetOrbwalkingMode() == kModeCombo && !ComboCancelRForKS->Enabled() && Player->IsCastingImportantSpell(&endtime)))
	{
		IUnit* targetQ = SelectTarget(SpellDamage,QRange);
		if (IsValidTarget(targetQ) && Q->IsReady() && GetQDamage(targetQ) >= targetQ->GetHealth())
		{
			Q->CastOnTarget(targetQ);
		}
		IUnit* targetE = SelectTarget(SpellDamage, ERange);
		if (IsValidTarget(targetE) && E->IsReady() && GetEDamage(targetE) >= targetE->GetHealth())
		{
			E->CastOnPosition(targetE->GetPosition());
		}
		IUnit* targetEQ = SelectTarget(SpellDamage, ERange);
		if (IsValidTarget(targetEQ) && E->IsReady() && Q->IsReady() && GetEDamage(targetEQ) + GetQDamage(targetEQ) >= targetEQ->GetHealth())
		{
			E->CastOnPosition(targetEQ->GetPosition());
		}
		if (Q->IsReady() && E->IsReady())
		{
			for (IUnit* hero : Enemies.Where([](IUnit* i) {return IsValidTarget(i, ERange + QRange + 150) && GetQDamage(i) >= i->GetHealth(); }).ToVector())
			{
				IUnit* nearest = GetEVinasun().MinOrDefault<float>([&](IUnit* i) {return Distance(i, hero); });
				if (nearest != nullptr && Distance(nearest,hero)<= 150 + QRange)
				{
					Vec3 pos = Extend(nearest->GetPosition(), hero->GetPosition(), 150);
					E->CastOnPosition(pos);
				}
			}
		}
		// auto q
		if (Q->IsReady() && AutoQ->Enabled())
		{
			auto target = SelectTarget(SpellDamage, QRange);
			if (target != nullptr)
			{
				Q->CastOnTarget(target);
			}
		}
	}
}