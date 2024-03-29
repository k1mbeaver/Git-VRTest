// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUI_UW.generated.h"

/**
 * 
 */
UCLASS()
class VRTEST_API UPlayerUI_UW : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextDefaultKill;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextCurrentKill;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextTest;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextKill;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextColon;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextSlash;

	UPROPERTY(Meta = (BindWidget))
		class UImage* MenuImage;

	UPROPERTY(Meta = (BindWidget))
		class UButton* BtTutorial;

	UPROPERTY(Meta = (BindWidget))
		class UButton* BtReplay;

	UPROPERTY(Meta = (BindWidget))
		class UButton* BtExit;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextPointOne;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextPointTwo;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextPointThree;

	UPROPERTY(Meta = (BindWidget))
		class UTutorial_UW* Tutorial_WB;

	TArray<UTextBlock*> BtArray;
	int BtSequence = 0;
	int TutorialSequence = 0;
	int DefaultSequence = 0;
	bool IsMenuOn = false;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

public:
	bool IsTutorial = false;
	// KillingPoint 관련
	void SetCurrentKill();
	void VisibleKillingPoint();
	void HiddenKillingPoint();

	// PlayerText 관련
	void VisibleText();
	void HiddenText();
	void SetPlayerText(FText MyText);

	// Menu 관련
	void SetMenu();
	void VisibleMenu();
	void HiddenMenu();
	void MenuDown();
	void MenuUp();
	void MenuClick();

	// Tutorial 관련
	void VisibleTutorial(bool bVisible);
	void TutorialNext();
	void TutorialPrev();

	// 이벤트
	UFUNCTION(BlueprintNativeEvent)
		void OnMenuClick();
	virtual void OnMenuClick_Implementation()
	{

	}

	void FocusButton();
	void UnFocusButton();
};
