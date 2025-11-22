// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskPawn.h"
#include "TaskNumBase.h"

void ATaskPawn::BeginPlay()
{
	Super::BeginPlay();

	FString NetRoleString = TaskNumBaseFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("TaskPawn::BeginPlay() %s [%s]"), *TaskNumBaseFunctionLibrary::GetNetModeString(this), *NetRoleString);
	TaskNumBaseFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

void ATaskPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = TaskNumBaseFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("TaskPawn::PossessedBy() %s [%s]"), *TaskNumBaseFunctionLibrary::GetNetModeString(this), *NetRoleString);
	TaskNumBaseFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}