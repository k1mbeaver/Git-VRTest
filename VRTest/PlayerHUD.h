// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class VRTEST_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
	APlayerHUD();
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UPlayerUI_UW> MainUIClass;
	class UPlayerUI_UW* MainUIObject;

	bool CheckUIObject();
	bool CreateUIObject();
};
