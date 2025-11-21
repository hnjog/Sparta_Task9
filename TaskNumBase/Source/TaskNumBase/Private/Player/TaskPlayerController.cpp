// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TaskPlayerController.h"
#include "UI/TaskChatInput.h"
#include "TaskNumBase.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "TaskGameModeBase.h"
#include "Player/TaskPlayerState.h"
#include "Net/UnrealNetwork.h"

ATaskPlayerController::ATaskPlayerController()
{
	bReplicates = true;
}

void ATaskPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false)
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass))
	{
		ChatInputWidgetInstance = CreateWidget<UTaskChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance))
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}

	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void ATaskPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}

void ATaskPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController() == true)
	{
		ATaskPlayerState* TPS = GetPlayerState<ATaskPlayerState>();
		if (IsValid(TPS) == true)
		{
			FString CombineMsg = TPS->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;

			ServerRPCPrintChatMessageString(CombineMsg);
		}
	}
}

void ATaskPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	TaskNumBaseFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void ATaskPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ATaskPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	// Server에서 Clinet 쪽으로 일일이 뿌림
	// NetMulticast??
	// - 이건 '클라'에서 호출되는 함수이기에,
	//   내 pc와 서버에서만 실행되게 됨

	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		ATaskGameModeBase* TGM = Cast<ATaskGameModeBase>(GM);
		if (IsValid(TGM) == true)
		{
			TGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}