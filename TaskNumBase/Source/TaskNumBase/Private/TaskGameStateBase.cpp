// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/TaskPlayerController.h"

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