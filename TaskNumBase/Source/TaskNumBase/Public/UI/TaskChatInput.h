// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/SlateEnums.h"
#include "TaskChatInput.generated.h"


class UEditableTextBox;

/**
 * 
 */
UCLASS()
class TASKNUMBASE_API UTaskChatInput : public UUserWidget
{
	GENERATED_BODY()

public:
	// UI용 생명 주기 함수들
	// AddToViewport()/AddChild()/AddToPlayerScreen() 등 화면에 추가될때 호출
	virtual void NativeConstruct() override;

	// 위젯이 화면에서 제거되거나 GC로 파괴될 때 호출
	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox_ChatInput;
};
