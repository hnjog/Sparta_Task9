// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskGameModeBase.h"
#include "TaskGameStateBase.h"
#include "Player/TaskPlayerController.h"
#include "Player/TaskPlayerState.h"
#include "EngineUtils.h"

void ATaskGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	ATaskPlayerController* TPC = Cast<ATaskPlayerController>(NewPlayer);
	if (IsValid(TPC) == true)
	{
		AllPlayerControllers.Add(TPC);

		ATaskPlayerState* TPS = TPC->GetPlayerState<ATaskPlayerState>();
		if (IsValid(TPS) == true)
		{
			TPS->PlayerNameString = TEXT("Player") + FString::FromInt(AllPlayerControllers.Num());
		}

		ATaskGameStateBase* TaskGameStateBase = GetGameState<ATaskGameStateBase>();
		if (IsValid(TaskGameStateBase) == true)
		{
			TaskGameStateBase->MulticastRPCBroadcastLoginMessage(TPS->PlayerNameString);
		}
	}
}

void ATaskGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateSecretNumber();

	UE_LOG(LogTemp, Error, TEXT("%s"), *SecretNumberString);
}

FString ATaskGameModeBase::GenerateSecretNumber()
{
	TArray<int32> BaseNums;
	for (int32 i = 1; i < 9; i++)
	{
		BaseNums.Add(i);
	}

	FMath::RandInit(FDateTime::Now().GetTicks());
	BaseNums = BaseNums.FilterByPredicate([](int32 Num) {return Num > 0; });

	FString Result;
	for (int32 i = 0; i < 3; i++)
	{
		int32 Index = FMath::RandRange(0, BaseNums.Num() - 1);
		Result.Append(FString::FromInt(BaseNums[Index]));
		BaseNums.RemoveAt(Index);
	}

	return Result;
}

bool ATaskGameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay = false;

	do
	{
		if (InNumberString.Len() != 3)
		{
			break;
		}

		bool bIsUnique = true;
		TSet<TCHAR> UniqueDigits;
		for (TCHAR C : InNumberString)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}

			UniqueDigits.Add(C);
		}

		if (bIsUnique == false)
		{
			break;
		}

		bCanPlay = true;

	} while (false);

	return bCanPlay;
}

FString ATaskGameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString)
{
	int32 StrikeCount = 0, BallCount = 0;

	for (int32 i = 0; i < 3; i++)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InGuessNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}

	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}

void ATaskGameModeBase::PrintChatMessageString(ATaskPlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	FString ChatMessageString = InChatMessageString;
	int Index = InChatMessageString.Len() - 3;
	FString GuessNumberString = InChatMessageString.RightChop(Index);

	if (IsGuessNumberString(GuessNumberString) == true)
	{
		FString JudgeResultString = JudgeResult(SecretNumberString, GuessNumberString);
		for (TActorIterator<ATaskPlayerController> It(GetWorld()); It; ++It)
		{
			ATaskPlayerController* TPC = *It;
			if (IsValid(TPC) == true)
			{
				FString CombinedMessageString = InChatMessageString + TEXT(" -> ") + JudgeResultString;
				TPC->ClientRPCPrintChatMessageString(CombinedMessageString);
			}
		}
	}
	else
	{
		for (TActorIterator<ATaskPlayerController> It(GetWorld()); It; ++It)
		{
			ATaskPlayerController* TPC = *It;
			if (IsValid(TPC) == true)
			{
				TPC->ClientRPCPrintChatMessageString(InChatMessageString);
			}
		}
	}
}
