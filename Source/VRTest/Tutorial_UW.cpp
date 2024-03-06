// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial_UW.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MyGameInstance.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"

void UTutorial_UW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextInfo")));
	BGImage = Cast<UImage>(GetWidgetFromName(TEXT("BGImage")));
}

void UTutorial_UW::NativeConstruct()
{
	Super::NativeConstruct();
	// BeginPlay ó�� Ȱ��

	/*
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
	*/
}
