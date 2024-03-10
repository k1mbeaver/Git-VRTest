// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

struct FPlayerDataTable;
struct FParticleDataTable;
struct FAnimationDataTable;
struct FSoundDataTable;
struct FAIDataTable;
struct FMapDataTable;

class UDataTable;

DECLARE_MULTICAST_DELEGATE(FOnPlayerKillDelegate);

/**
 * 
 */
UCLASS()
class VRTEST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	// 사운드 얻어오기
	USoundWave* GetSound(FString SoundType);

	// 애니메이션, 몽타주 얻어오기
	UAnimMontage* GetMontage(FString MontageType);
	TSubclassOf<class UAnimInstance> GetAnimation(FString AnimationType);

	// 파티클 얻어오기
	UParticleSystem* GetParticle(FString ParticleType);

	// 플레이어 정보 얻어오기
	FString GetPlayerName(FString PlayerType);
	int GetPlayerStage(FString PlayerType);
	void SetPlayerName(FString PlayerType, FString SetPlayerName);
	void SetPlayerStage(FString PlayerType, int SetPlayerStage);
	FVector GetPlayerPosition(FString PlayerType);
	void SetPlayerPosition(FString PlayerType, FVector SetPlayerPosition);

	// AI 정보 얻어오기
	float GetAISpeed(FString AIType);
	FString GetAIType(FString AIType);

	// Map 정보 얻어오기
	int GetAICount(int MapType);
	FName GetMapName(int MapType);
	FName GetNextMapName(int MapType);
	FText GetMapText(int MapType);
	FVector GetMapPosition(int MapType);

	// 변수 관련 함수
	int GetPlayerKill();
	void SetPlayerKill();
	void InitializePlayerKill();

	// Tutorial 정보 얻어오기
	FString GetTutorialText(int nSequence);

	// 변수
	int nPlayerKill = 0;
	
	FOnPlayerKillDelegate OnPlayerKill;
private:
	UPROPERTY()
		UDataTable* FPlayerFileTable;

	UPROPERTY()
		UDataTable* FParticleFileTable;

	UPROPERTY()
		UDataTable* FAnimationFileTable;

	UPROPERTY()
		UDataTable* FSoundFileTable;

	UPROPERTY()
		UDataTable* FAIFileTable;

	UPROPERTY()
		UDataTable* FMapFileTable;

	UPROPERTY()
		UDataTable* FTutorialFileTable;

};
