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

protected:
	float CurrentFadeValue = 0.0f;

public:
	bool IsVisible = false;
	bool IsFading = true; // 페이드 활성화
	bool IsFadeIn = true; // true면 페이드인, false면 페이드 아웃

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void WidgetTick(float DeltaTime);

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

	UFUNCTION(BlueprintCallable)
		void TutorialFadeOut();

	UFUNCTION(BlueprintCallable)
		void TutorialFadeIn(int nSequence);
	/*
	bool IsMenuOn;
	// KillingPoint 관련
	void SetCurrentKill();
	void VisibleKillingPoint();
	void HiddenKillingPoint();
	*/
};
