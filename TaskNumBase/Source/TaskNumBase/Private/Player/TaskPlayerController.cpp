// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TaskPlayerController.h"
#include "UI/TaskChatInput.h"
#include "TaskNumBase.h"
#include "EngineUtils.h"

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
}

void ATaskPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;
	//PrintChatMessageString(ChatMessageString);

	if (IsLocalController() == true)
	{
		ServerRPCPrintChatMessageString(InChatMessageString);
	}
}

void ATaskPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	TaskNumBaseFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void ATaskPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(ChatMessageString);
}

void ATaskPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	// Server에서 Clinet 쪽으로 일일이 뿌림
	// NetMulticast??
	// - 이건 '클라'에서 호출되는 함수이기에,
	//   내 pc와 서버에서만 실행되게 됨
	for (TActorIterator<ATaskPlayerController> It(GetWorld()); It; ++It)
	{
		ATaskPlayerController* TaskPlayerController = *It;
		if (IsValid(TaskPlayerController) == true)
		{
			TaskPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
		}
	}
}
