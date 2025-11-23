// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/TaskPlayerController.h"
#include "Net/UnrealNetwork.h"

void ATaskGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(PC) == true)
		{
			ATaskPlayerController* TPC = Cast<ATaskPlayerController>(PC);
			if (IsValid(TPC) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				TPC->PrintChatMessageString(NotificationString);
			}
		}
	}
}

ATaskGameStateBase::ATaskGameStateBase()
	:MaxTurnCount(30),
	RemainTurnCount(30)
{
}

void ATaskGameStateBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, RemainTurnCount);
}
