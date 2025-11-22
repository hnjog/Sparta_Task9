// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TaskPlayerState.h"
#include "Net/UnrealNetwork.h"

ATaskPlayerState::ATaskPlayerState()
	:PlayerNameString(TEXT("None"))
	, CurrentGuessCount(0)
	, MaxGuessCount(3)
{
	bReplicates = true;
}

void ATaskPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 현재 클래스의 Replication Descriptor Table 을 생성하여 NetDriver에 전달
	DOREPLIFETIME(ThisClass, PlayerNameString);
	DOREPLIFETIME(ThisClass, CurrentGuessCount);
	DOREPLIFETIME(ThisClass, MaxGuessCount);
}

FString ATaskPlayerState::GetPlayerInfoString()
{
	FString PlayerInfoString = PlayerNameString + TEXT("(") + FString::FromInt(CurrentGuessCount + 1) + TEXT("/") + FString::FromInt(MaxGuessCount) + TEXT(")");
	return PlayerInfoString;
}

bool ATaskPlayerState::AddGuessCount()
{
	if(CurrentGuessCount >= MaxGuessCount)
		return false;

	CurrentGuessCount++;

	return true;
}
