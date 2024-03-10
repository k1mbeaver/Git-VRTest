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

public:
	bool IsVisible = false;
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	float LerpFun(float beginValue, float endValue, float t) 
	{
		return beginValue * (1 - t) + (endValue * t);
	};

	void TransparencyImage(float fSpeed, float fBegin, float fEnd);

public:

	UFUNCTION(BlueprintCallable)
		void VisibleBackImage(bool bVisible);

	UFUNCTION(BlueprintCallable)
		void SetTutorialText(FString myText);
	/*
	bool IsMenuOn;
	// KillingPoint ฐüทร
	void SetCurrentKill();
	void VisibleKillingPoint();
	void HiddenKillingPoint();
	*/
};
