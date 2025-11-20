// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskGameModeBase.h"
#include "TaskGameStateBase.h"

void ATaskGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	ATaskGameStateBase* TaskStateBase = GetGameState<ATaskGameStateBase>();
	if (IsValid(TaskStateBase) == true)
	{
		TaskStateBase->MulticastRPCBroadcastLoginMessage(TEXT("XXXXXXX"));
	}
}
