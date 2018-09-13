// Copyright 2017-2018 Krivosheya Mikhail. All Rights Reserved.
#include "DialogSystemRuntime.h"
#include "DialogProcessor.h"
#include "DialogScript.h"

ADialogScript::ADialogScript()
{
}

AActor* ADialogScript::GetPlayer()
{
	return UGameplayStatics::GetPlayerCharacter(GetNPC()->GetWorld(), 0);
}

AActor* ADialogScript::GetNPC()
{
	return Implementer->NPC;
}
