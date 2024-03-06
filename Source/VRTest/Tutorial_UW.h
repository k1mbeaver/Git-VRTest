// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tutorial_UW.generated.h"

/**
 * 
 */
UCLASS()
class VRTEST_API UTutorial_UW : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextInfo;

	UPROPERTY(Meta = (BindWidget))
		class UImage* BGImage;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

public:

	/*
	bool IsMenuOn;
	// KillingPoint ฐüทร
	void SetCurrentKill();
	void VisibleKillingPoint();
	void HiddenKillingPoint();
	*/
};
