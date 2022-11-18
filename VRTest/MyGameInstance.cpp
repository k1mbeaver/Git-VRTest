// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "PlayerDataTableClass.h"

UMyGameInstance::UMyGameInstance()
{
	FString PlayerFileDataPath = TEXT("DataTable'/Game/DataTable/PlayerDataTable.PlayerDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYPLAYERFILE(*PlayerFileDataPath);

	if (DT_MYPLAYERFILE.Succeeded())
	{
		FPlayerFileTable = DT_MYPLAYERFILE.Object;
	}
}