// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UENUM(BlueprintType)
enum class EMyPlayerState : uint8
{
	E_Start = 0 UMETA(DisplayName = "Start"),
	E_Ready = 1 UMETA(DisplayName = "Ready"),
	E_Play = 2 UMETA(DisplayName = "Play"),
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

	// ���� �÷��̾��� ���� (����ȭ��, �غ�ȭ��, �÷���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EMyPlayerState MyPlayerState;

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
		void PlayerDead();

	// ���͸� ų���� �ÿ� ȣ���ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
		void KillingMonster();

	// �÷��̾ ���� ������ �ƴ��� Ȯ���ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
		bool PlayerPlaying();

	// �÷��̾��� ���� Start
	UFUNCTION(BlueprintCallable)
		void PlayerGameStart();
};
