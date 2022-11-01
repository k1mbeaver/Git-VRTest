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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Motion)
		class UMotionControllerComponent* MotionLeft;

	UPROPERTY(VisibleAnywhere, Category = Motion)
		class UMotionControllerComponent* MotionRight;

	UPROPERTY(VisibleAnywhere, Category = Motion)
		class USkeletalMeshComponent* MeshLeft;

	UPROPERTY(VisibleAnywhere, Category = Motion)
		class USkeletalMeshComponent* MeshRight;


	bool IsRightGrip;
	bool IsLeftGrip;

	// 플레이어의 현재 공격 무기 (주먹, 총, 물체)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerWeapon PlayerWeapon;

	UPROPERTY()
		class APlayerPistol* myLeftPlayerPistol;

	UPROPERTY()
		class APlayerPistol* myRightPlayerPistol;

	class UPlayerAnim* LeftHandInstance;
	class UPlayerAnim* RightHandInstance;

	void PressedLeftGrip();
	void ReleasedLeftGrip();
	void PressedRightGrip();
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
		void SetPlayerLeftPistol(UActorComponent* myPistol);

	UFUNCTION(BlueprintCallable)
		void SetPlayerRightPistol(UActorComponent* myPistol);
};
