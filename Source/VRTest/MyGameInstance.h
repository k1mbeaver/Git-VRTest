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

	// ���� ������
	USoundWave* GetSound(FString SoundType);

	// �ִϸ��̼�, ��Ÿ�� ������
	UAnimMontage* GetMontage(FString MontageType);
	TSubclassOf<class UAnimInstance> GetAnimation(FString AnimationType);

	// ��ƼŬ ������
	UParticleSystem* GetParticle(FString ParticleType);

	// �÷��̾� ���� ������
	FString GetPlayerName(FString PlayerType);
	int GetPlayerStage(FString PlayerType);
	void SetPlayerName(FString PlayerType, FString SetPlayerName);
	void SetPlayerStage(FString PlayerType, int SetPlayerStage);
	FVector GetPlayerPosition(FString PlayerType);
	void SetPlayerPosition(FString PlayerType, FVector SetPlayerPosition);

	// AI ���� ������
	float GetAISpeed(FString AIType);
	FString GetAIType(FString AIType);

	// Map ���� ������
	int GetAICount(int MapType);
	FName GetMapName(int MapType);
	FName GetNextMapName(int MapType);
	FText GetMapText(int MapType);
	FVector GetMapPosition(int MapType);

	// ���� ���� �Լ�
	int GetPlayerKill();
	void SetPlayerKill();
	void InitializePlayerKill();

	// ����
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

};
