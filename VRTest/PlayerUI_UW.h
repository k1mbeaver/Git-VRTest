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

	TArray<UButton*> BtArray;
	int BtSequence = 0;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

public:
	bool IsMenuOn;
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

	// 이벤트
	UFUNCTION(BlueprintNativeEvent)
		void OnMenuClick();
	virtual void OnMenuClick_Implementation()
	{

	}

	void FocusButton(int nButton);
};
