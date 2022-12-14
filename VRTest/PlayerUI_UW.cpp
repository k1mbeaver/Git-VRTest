// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI_UW.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Styling/SlateBrush.h"

void UPlayerUI_UW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextDefaultKill = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextDefaultKill")));
	TextCurrentKill = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextCurrentKill")));
	TextTest = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextTest")));
	TextKill = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextKill")));
	TextColon = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextColon")));
	TextSlash = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextSlash")));
	MenuImage = Cast<UImage>(GetWidgetFromName(TEXT("MenuImage")));
	BtTutorial = Cast<UButton>(GetWidgetFromName(TEXT("BtTutorial")));
	BtReplay = Cast<UButton>(GetWidgetFromName(TEXT("BtReplay")));
	BtExit = Cast<UButton>(GetWidgetFromName(TEXT("BtExit")));
}

void UPlayerUI_UW::NativeConstruct()
{
	Super::NativeConstruct();

	IsMenuOn = false;

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	AMyCharacter* MyPlayerCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());

	int PlayerStage = MyGameInstance->GetPlayerStage("Player");
	int StageMonsters = MyGameInstance->GetAICount(PlayerStage);

	FString strStageMonsters = FString::FromInt(StageMonsters);
	FText ftStageMonsters = FText::FromString(strStageMonsters);
	TextDefaultKill->SetText(ftStageMonsters);

	MyGameInstance->OnPlayerKill.AddUObject(this, &UPlayerUI_UW::SetCurrentKill);
	MyPlayerCharacter->OnPlayerMenuDelegate.AddUObject(this, &UPlayerUI_UW::SetMenu);
	MyPlayerCharacter->OnPlayerMenuUpDelegate.AddUObject(this, &UPlayerUI_UW::MenuUp);
	MyPlayerCharacter->OnPlayerMenuDownDelegate.AddUObject(this, &UPlayerUI_UW::MenuDown);
	MyPlayerCharacter->OnPlayerMenuClickDelegate.AddUObject(this, &UPlayerUI_UW::MenuClick);

	BtArray.Add(BtTutorial);
	BtArray.Add(BtReplay);
	BtArray.Add(BtExit);

	if (PlayerStage == 0)
	{
		SetPlayerText(MyGameInstance->GetMapText(PlayerStage));
		VisibleText();
	}

	else if (PlayerStage == 1)
	{
		SetPlayerText(MyGameInstance->GetMapText(PlayerStage));
		VisibleText();
	}

	else if (PlayerStage == 7)
	{
		return;
	}

	else if (PlayerStage == 8)
	{
		return;
	}

	else
	{
		VisibleKillingPoint();
		SetPlayerText(MyGameInstance->GetMapText(PlayerStage));
	}
}

void UPlayerUI_UW::SetCurrentKill()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	FString strStageMonsters = FString::FromInt(MyGameInstance->GetPlayerKill());
	FText ftStageMonsters = FText::FromString(strStageMonsters);
	TextCurrentKill->SetText(ftStageMonsters);
}

void UPlayerUI_UW::VisibleKillingPoint()
{
	TextDefaultKill->SetVisibility(ESlateVisibility::Visible);
	TextCurrentKill->SetVisibility(ESlateVisibility::Visible);
	TextKill->SetVisibility(ESlateVisibility::Visible);
	TextColon->SetVisibility(ESlateVisibility::Visible);
	TextSlash->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerUI_UW::HiddenKillingPoint()
{
	TextDefaultKill->SetVisibility(ESlateVisibility::Hidden);
	TextCurrentKill->SetVisibility(ESlateVisibility::Hidden);
	TextKill->SetVisibility(ESlateVisibility::Hidden);
	TextColon->SetVisibility(ESlateVisibility::Hidden);
	TextSlash->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerUI_UW::VisibleText()
{
	TextTest->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerUI_UW::HiddenText()
{
	TextTest->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerUI_UW::SetPlayerText(FText MyText)
{
	TextTest->SetText(MyText);
}

void UPlayerUI_UW::SetMenu()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	int PlayerStage = MyGameInstance->GetPlayerStage("Player");

	if (IsMenuOn)
	{
		HiddenMenu();
	}

	else
	{
		VisibleMenu();
	}
}

void UPlayerUI_UW::VisibleMenu()
{
	// 튜토리얼 모드의 경우에는 튜토리얼은 IsFocusible = false
	MenuImage->SetVisibility(ESlateVisibility::Visible);
	BtTutorial->SetVisibility(ESlateVisibility::Visible);
	BtReplay->SetVisibility(ESlateVisibility::Visible);
	BtExit->SetVisibility(ESlateVisibility::Visible);

	IsMenuOn = true;
}

void UPlayerUI_UW::HiddenMenu()
{
	MenuImage->SetVisibility(ESlateVisibility::Hidden);
	BtTutorial->SetVisibility(ESlateVisibility::Hidden);
	BtReplay->SetVisibility(ESlateVisibility::Hidden);
	BtExit->SetVisibility(ESlateVisibility::Hidden);

	IsMenuOn = false;
	BtSequence = 0;
}

void UPlayerUI_UW::MenuUp()
{
	FocusButton(0);
}

void UPlayerUI_UW::MenuDown()
{

}

void UPlayerUI_UW::MenuClick()
{
	OnMenuClick();
}

void UPlayerUI_UW::FocusButton(int nButton)
{
	BtArray[nButton]->SetFocus();
}