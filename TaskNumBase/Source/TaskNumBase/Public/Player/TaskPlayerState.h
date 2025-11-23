// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TaskPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TASKNUMBASE_API ATaskPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ATaskPlayerState();

	// Replicated 선언된 변수들을 엔진이 처리하도록 등록함
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	FString GetPlayerInfoString();

public:
	FORCEINLINE void SetPlayerName(const FString& NameString) { PlayerNameString = NameString; }

	FORCEINLINE const FString& GetPlayerName() { return PlayerNameString; }

	FORCEINLINE int32 GetPlayerNowGuessCount() { return CurrentGuessCount; }
	FORCEINLINE int32 GetPlayerMaxGuessCount() { return MaxGuessCount; }

	FORCEINLINE bool CanGuess() { return CurrentGuessCount < MaxGuessCount; }
	FORCEINLINE void ResetGuessCount() { CurrentGuessCount = 0; }

	FORCEINLINE bool IsMyTurn() { return bMyTurn; }
	FORCEINLINE void SetTurn() { bMyTurn = true; }
	FORCEINLINE void EndTurn() { bMyTurn = false; }
public:
	bool AddGuessCount();

protected:
	UPROPERTY(Replicated)
	FString PlayerNameString;

	UPROPERTY(Replicated)
	int32 CurrentGuessCount;

	UPROPERTY(Replicated)
	int32 MaxGuessCount;

	// 지금 이거 동기화가 잘 안됨
	// 따라서 '턴 시작'에 관련된 부분을 OnRef로 냅두는 것이 좋음
	// 
	UPROPERTY(Replicated)
	bool bMyTurn;
};
