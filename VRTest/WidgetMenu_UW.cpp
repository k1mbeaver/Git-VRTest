// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetMenu_UW.h"
#include "MyGameInstance.h"
#include "MyCharacter.h"

void UWidgetMenu_UW::GameRestart()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	MyGameInstance->SetPlayerStage("Player", 1);
}

void UWidgetMenu_UW::GameResume()
{

}

void UWidgetMenu_UW::GameExit()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	MyGameInstance->SetPlayerStage("Player", 8);
}