// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "PlayerDataTableClass.h"
#include "SoundDataTableClass.h"
#include "ParticleDataTableClass.h"
#include "AnimationDataTableClass.h"
#include "AIDataTableClass.h"
#include "MapDataTableClass.h"

UMyGameInstance::UMyGameInstance()
{
	FString PlayerFileDataPath = TEXT("DataTable'/Game/DataTable/PlayerDataTable.PlayerDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYPLAYERFILE(*PlayerFileDataPath);

	if (DT_MYPLAYERFILE.Succeeded())
	{
		FPlayerFileTable = DT_MYPLAYERFILE.Object;
	}

	FString ParticleFileDataPath = TEXT("DataTable'/Game/DataTable/ParticleDataTable.ParticleDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYPARTICLEFILE(*ParticleFileDataPath);

	if (DT_MYPARTICLEFILE.Succeeded())
	{
		FParticleFileTable = DT_MYPARTICLEFILE.Object;
	}

	FString AnimationFileDataPath = TEXT("DataTable'/Game/DataTable/AnimationDataTable.AnimationDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYANIMATIONFILE(*AnimationFileDataPath);

	if (DT_MYANIMATIONFILE.Succeeded())
	{
		FAnimationFileTable = DT_MYANIMATIONFILE.Object;
	}

	FString SoundFileDataPath = TEXT("DataTable'/Game/DataTable/SoundDataTable.SoundDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYSOUNDFILE(*SoundFileDataPath);

	if (DT_MYSOUNDFILE.Succeeded())
	{
		FSoundFileTable = DT_MYSOUNDFILE.Object;
	}

	FString AIFileDataPath = TEXT("DataTable'/Game/DataTable/AIDataTable.AIDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYAIFILE(*AIFileDataPath);

	if (DT_MYAIFILE.Succeeded())
	{
		FAIFileTable = DT_MYAIFILE.Object;
	}

	FString MapFileDataPath = TEXT("DataTable'/Game/DataTable/MapDataTable.MapDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYMAPFILE(*MapFileDataPath);

	if (DT_MYMAPFILE.Succeeded())
	{
		FMapFileTable = DT_MYMAPFILE.Object;
	}
}

USoundWave* UMyGameInstance::GetSound(FString SoundType)
{
	FSoundDataTable* SoundData = FSoundFileTable->FindRow<FSoundDataTable>(*SoundType, TEXT(""));
	USoundWave* GetMySound = SoundData->MySound;
	return GetMySound;
}

UAnimMontage* UMyGameInstance::GetMontage(FString MontageType)
{
	FAnimationDataTable* MontageData = FAnimationFileTable->FindRow<FAnimationDataTable>(*MontageType, TEXT(""));
	UAnimMontage* GetMyMontage = MontageData->MyMontage;
	return GetMyMontage;
}

TSubclassOf<class UAnimInstance> UMyGameInstance::GetAnimation(FString AnimationType)
{
	FAnimationDataTable* AnimationData = FAnimationFileTable->FindRow<FAnimationDataTable>(*AnimationType, TEXT(""));
	TSubclassOf<class UAnimInstance> GetMyAnimation = AnimationData->MyAnimation;
	return GetMyAnimation;
}

UParticleSystem* UMyGameInstance::GetParticle(FString ParticleType)
{
	FParticleDataTable* ParticleData = FParticleFileTable->FindRow<FParticleDataTable>(*ParticleType, TEXT(""));
	UParticleSystem* GetMyParticle = ParticleData->MyParticle;
	return GetMyParticle;
}

FString UMyGameInstance::GetPlayerName(FString PlayerType)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerType, TEXT(""));
	FString GetPlayerName = PlayerData->PlayerName;
	return GetPlayerName;
}

int UMyGameInstance::GetPlayerStage(FString PlayerType)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerType, TEXT(""));
	int GetPlayerStage = PlayerData->PlayerStage;
	return GetPlayerStage;
}

void UMyGameInstance::SetPlayerName(FString PlayerType, FString SetPlayerName)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerType, TEXT(""));
	PlayerData->PlayerName = SetPlayerName;
}

void UMyGameInstance::SetPlayerStage(FString PlayerType, int SetPlayerStage)
{
	FPlayerDataTable* PlayerData = FPlayerFileTable->FindRow<FPlayerDataTable>(*PlayerType, TEXT(""));
	PlayerData->PlayerStage = SetPlayerStage;
}

float UMyGameInstance::GetAISpeed(FString AIType)
{
	FAIDataTable* AIData = FAIFileTable->FindRow<FAIDataTable>(*AIType, TEXT(""));
	float GetAISpeed = AIData->AICharacterSpeed;
	return GetAISpeed;
}

FString UMyGameInstance::GetAIType(FString AIType)
{
	FAIDataTable* AIData = FAIFileTable->FindRow<FAIDataTable>(*AIType, TEXT(""));
	FString GetAIType = AIData->AICharacterType;
	return GetAIType;
}

int UMyGameInstance::GetAICount(int MapType)
{
	FString strMapType = FString::FromInt(MapType);
	FMapDataTable* MapData = FMapFileTable->FindRow<FMapDataTable>(*strMapType, TEXT(""));
	int GetAICount = MapData->CountAI;
	return GetAICount;
}

FName UMyGameInstance::GetMapName(int MapType)
{
	FString strMapType = FString::FromInt(MapType);
	FMapDataTable* MapData = FMapFileTable->FindRow<FMapDataTable>(*strMapType, TEXT(""));
	FName GetMapName = MapData->MapName;
	return GetMapName;
}

FName UMyGameInstance::GetNextMapName(int MapType)
{
	FString strMapType = FString::FromInt(MapType);
	FMapDataTable* MapData = FMapFileTable->FindRow<FMapDataTable>(*strMapType, TEXT(""));
	FName GetNextMapName = MapData->NextMapName;
	return GetNextMapName;
}

FText UMyGameInstance::GetMapText(int MapType)
{
	FString strMapType = FString::FromInt(MapType);
	FMapDataTable* MapData = FMapFileTable->FindRow<FMapDataTable>(*strMapType, TEXT(""));
	FText GetMapText = MapData->MapText;
	return GetMapText;
}

int UMyGameInstance::GetPlayerKill()
{
	return nPlayerKill;
}

void UMyGameInstance::SetPlayerKill()
{
	nPlayerKill = nPlayerKill + 1;
	OnPlayerKill.Broadcast();
}

void UMyGameInstance::InitializePlayerKill()
{
	nPlayerKill = 0;
}