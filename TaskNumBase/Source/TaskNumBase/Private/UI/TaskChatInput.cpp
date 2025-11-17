// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TaskChatInput.h"

#include "Components/EditableTextBox.h"
#include "Player/TaskPlayerController.h"

void UTaskChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (EditableTextBox_ChatInput &&
		EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this,&ThisClass::OnChatInputTextCommitted) == false)
	{
		EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UTaskChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (EditableTextBox_ChatInput &&
		EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted))
	{
		EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UTaskChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController))
		{
			ATaskPlayerController* OwningTPC = Cast<ATaskPlayerController>(OwningPlayerController);
			if (IsValid(OwningTPC))
			{
				OwningTPC->SetChatMessageString(Text.ToString());

				EditableTextBox_ChatInput->SetText(FText());
			}
		}
	}
}
