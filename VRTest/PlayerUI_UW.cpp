// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI_UW.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"

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
	TextPointOne = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextPointOne")));
	TextPointTwo = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextPointTwo")));
	TextPointThree = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextPointThree")));
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

	BtArray.Insert(TextPointOne, 0);
	BtArray.Insert(TextPointTwo, 1);
	BtArray.Insert(TextPointThree, 2);

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
	FocusButton();

	IsMenuOn = true;
}

void UPlayerUI_UW::HiddenMenu()
{
	MenuImage->SetVisibility(ESlateVisibility::Hidden);
	BtTutorial->SetVisibility(ESlateVisibility::Hidden);
	BtReplay->SetVisibility(ESlateVisibility::Hidden);
	BtExit->SetVisibility(ESlateVisibility::Hidden);
	UnFocusButton();

	IsMenuOn = false;
	BtSequence = 0;
}

void UPlayerUI_UW::MenuUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("MenuUp!"));
	if (BtSequence == 0)
	{
		return;
	}

	else
	{
		UnFocusButton();
		BtSequence--;
		FocusButton();
	}
	//FocusButton(0);
}

void UPlayerUI_UW::MenuDown()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("MenuDown!"));
	if (BtSequence == 2)
	{
		return;
	}

	else
	{
		UnFocusButton();
		BtSequence++;
		FocusButton();
	}
}

void UPlayerUI_UW::MenuClick()
{
	OnMenuClick();

	if (BtSequence == 0)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
		MyGameInstance->SetPlayerStage("Player", 8);
		UGameplayStatics::OpenLevel(GetWorld(), "TestMap");

	}

	else if (BtSequence == 1)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
		MyGameInstance->SetPlayerStage("Player", 0);
		UGameplayStatics::OpenLevel(GetWorld(), "StartMap");
	}

	else if (BtSequence == 2)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
		MyGameInstance->SetPlayerStage("Player", 0);
		UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
	}

	else
	{
		return;
	}
}

void UPlayerUI_UW::FocusButton()
{
	BtArray[BtSequence]->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerUI_UW::UnFocusButton()
{
	BtArray[BtSequence]->SetVisibility(ESlateVisibility::Hidden);
}