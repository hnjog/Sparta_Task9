// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TaskGameModeBase.generated.h"

class ATaskPlayerController;

/**
 * 
 */
UCLASS()
class TASKNUMBASE_API ATaskGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void OnPostLogin(AController* NewPlayer) override;

	virtual void BeginPlay() override;
public:
	FString GenerateSecretNumber();

	bool IsGuessNumberString(const FString& InNumberString);

	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);
	
	void PrintChatMessageString(ATaskPlayerController* InChattingPlayerController, const FString& InChatMessageString);

protected:
	FString SecretNumberString;

	TArray<TObjectPtr<ATaskPlayerController>> AllPlayerControllers;
};
