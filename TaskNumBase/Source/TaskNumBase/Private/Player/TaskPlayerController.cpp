// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TaskPlayerController.h"
#include "UI/TaskChatInput.h"
#include "TaskNumBase.h"

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
	PrintChatMessageString(ChatMessageString);
}

void ATaskPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	TaskNumBaseFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}
