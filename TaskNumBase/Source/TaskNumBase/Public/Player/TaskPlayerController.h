// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TaskPlayerController.generated.h"


class UTaskChatInput;

/**
 * 
 */
UCLASS()
class TASKNUMBASE_API ATaskPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetChatMessageString(const FString& InChatMessageString);

	void PrintChatMessageString(const FString& InChatMessageString);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTaskChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UTaskChatInput> ChatInputWidgetInstance;

	FString ChatMessageString;

};
