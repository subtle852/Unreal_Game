// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GHUD.generated.h"

class UGStatComponent;
class AGPlayerState;
class UTextBlock;
class UGW_HPBar;

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UGHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindStatComponent(UGStatComponent* InStatComponent);

	void BindPlayerState(AGPlayerState* InPlayerState);

protected:
	UFUNCTION()
	void OnKillCountChanged(int32 InOldKillCount, int32 InNewKillCount);

protected:
	TWeakObjectPtr<UGStatComponent> StatComponent;

	TWeakObjectPtr<AGPlayerState> PlayerState;
	
	// 하드코딩으로 속성과 위젯 바인드하는 것이 아닌
	// BindWidget 키워드를 통해서
	// 속성의 이름과 위젯 블루프린트 속 위젯의 이름을 동일하게 해주면 바인드 됨
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> KillCountText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UGW_HPBar> HPBar;
};

