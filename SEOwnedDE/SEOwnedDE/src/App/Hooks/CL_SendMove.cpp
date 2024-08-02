#include "../../SDK/SDK.h"

#include "../Features/CFG.h"
#include "../Features/SeedPred/SeedPred.h"

// does not exist anymore, inlined; reimplement features elsewhere

MAKE_HOOK(CL_SendMove, Signatures::CL_SendMove.Get(), void, __fastcall,
	void* ecx)
{
	F::SeedPred->AskForPlayerPerf();

	if (Shifting::nAvailableTicks < MAX_COMMANDS)
	{
		if (H::Entities->GetWeapon())
		{
			if (!Shifting::bRecharging && !Shifting::bShifting && !Shifting::bShiftingWarp)
			{
				if (H::Input->IsDown(CFG::Exploits_Shifting_Recharge_Key))
				{
					Shifting::bRecharging = !I::MatSystemSurface->IsCursorVisible() && !I::EngineVGui->IsGameUIVisible();
				}
			}
		}

		if (Shifting::bRecharging)
		{
			Shifting::nAvailableTicks++;
			return;
		}
	}
	else
	{
		Shifting::bRecharging = false;
	}

	CALL_ORIGINAL(ecx);
}
