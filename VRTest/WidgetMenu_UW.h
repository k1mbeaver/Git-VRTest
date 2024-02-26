// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetMenu_UW.generated.h"

/**
 * 
 */
UCLASS()
class VRTEST_API UWidgetMenu_UW : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void GameResume();

	UFUNCTION(BlueprintCallable)
		void GameRestart();

	UFUNCTION(BlueprintCallable)
		void GameExit();
};
