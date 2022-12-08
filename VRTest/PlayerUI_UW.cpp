// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI_UW.h"
#include "Components/TextBlock.h"
#include "MyGameInstance.h"

void UPlayerUI_UW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextDefaultKill = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextDefaultKill")));
	TextCurrentKill = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextCurrentKill")));
	TextTest = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextTest")));
	TextKill = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextKill")));
	TextColon = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextColon")));
	TextSlash = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextSlash")));
}

void UPlayerUI_UW::NativeConstruct()
{
	Super::NativeConstruct();

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	int PlayerStage = MyGameInstance->GetPlayerStage("Player");
	int StageMonsters = MyGameInstance->GetAICount(PlayerStage);

	FString strStageMonsters = FString::FromInt(StageMonsters);
	FText ftStageMonsters = FText::FromString(strStageMonsters);
	TextDefaultKill->SetText(ftStageMonsters);

	MyGameInstance->OnPlayerKill.AddUObject(this, &UPlayerUI_UW::SetCurrentKill);

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