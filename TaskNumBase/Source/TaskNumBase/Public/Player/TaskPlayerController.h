// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TaskPlayerController.generated.h"


class UTaskChatInput;
class UUserWidget;

/**
 * 
 */
UCLASS()
class TASKNUMBASE_API ATaskPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATaskPlayerController();

public:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	void SetChatMessageString(const FString& InChatMessageString);

	void PrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);

public:
	UFUNCTION(BlueprintCallable,BlueprintPure)
	const FText& GetNotificationText();

	FORCEINLINE void SetNotificationText(const FText& NotiText)
	{
		NotificationText = NotiText;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const FText& GetTimerText();

	FORCEINLINE void SetTimerText(const FText& TimerText)
	{
		TimeText = TimerText;
	}
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTaskChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UTaskChatInput> ChatInputWidgetInstance;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NotificationTextWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> NotificationTextWidgetInstance;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> TimeWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> TimeWidgetInstance;

	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;

	UPROPERTY(Replicated, BlueprintReadOnly)
	FText TimeText;

	FString ChatMessageString;
};
