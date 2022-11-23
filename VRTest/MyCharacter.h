// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerWeapon : uint8
{
	E_Punch = 0 UMETA(DisplayName = "Punch"),
	E_Pistol = 1 UMETA(DisplayName = "Pistol"),
	E_Object = 2 UMETA(DisplayName = "Object"),
};

UCLASS()
class VRTEST_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int TotalMonsterKill;
	int CurrentMonsterKill;
	int PlayerStage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Motion)
		class UMotionControllerComponent* MotionLeft;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Motion)
		class UMotionControllerComponent* MotionRight;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Motion)
		class USkeletalMeshComponent* MeshLeft;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Motion)
		class USkeletalMeshComponent* MeshRight;


	bool IsRightGrip;
	bool IsLeftGrip;

	// 플레이어의 현재 공격 무기 (주먹, 총, 물체)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerWeapon PlayerWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PlayerHasRightObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PlayerHasLeftObject;

	class UPlayerAnim* LeftHandInstance;
	class UPlayerAnim* RightHandInstance;

	class UMyGameInstance* MyGameInstance;


	UFUNCTION(BlueprintCallable)
	void PressedLeftGrip();

	UFUNCTION(BlueprintCallable)
	void ReleasedLeftGrip();

	UFUNCTION(BlueprintCallable)
	void PressedRightGrip();

	UFUNCTION(BlueprintCallable)
	void ReleasedRightGrip();

	UFUNCTION(BlueprintCallable)
		void SetIsRightGrip();

	UFUNCTION(BlueprintCallable)
		void SetIsLeftGrip();

	UFUNCTION(BlueprintCallable)
		void SetPlayerWeapon(EPlayerWeapon myPlayerWeapon);

	UFUNCTION(BlueprintCallable)
		EPlayerWeapon GetPlayerWeapon();

	UFUNCTION(BlueprintCallable)
		void PlayerDead();

	// 몬스터를 킬했을 시에 호출하는 함수
	UFUNCTION(BlueprintCallable)
		void KillingMonster();
};
