// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TaskGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class TASKNUMBASE_API ATaskGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	ATaskGameStateBase();

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCBroadcastLoginMessage(const FString& InNameString = FString(TEXT("XXXXXXX")));

	FORCEINLINE void TimeGone() { RemainTurnCount--; }

	FORCEINLINE bool IsTurnEnd() { return RemainTurnCount <= 0; }

	FORCEINLINE void ResetTime() { RemainTurnCount = MaxTurnCount; }

	FORCEINLINE int32 GetRemainTime() { return RemainTurnCount; }

public:
	UPROPERTY(Replicated)
	int32 RemainTurnCount;

	int32 MaxTurnCount;
};
