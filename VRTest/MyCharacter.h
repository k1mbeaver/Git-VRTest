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
	E_Paused = 3 UMETA(DisplayName = "Pause"),
	E_Exit = 4 UMETA(DisplayName = "Exit"),
	E_Test = 5 UMETA(DisplayName = "Test"),

};

DECLARE_MULTICAST_DELEGATE(FOnPlayerMenuDelegate);
DECLARE_MULTICAST_DELEGATE(FOnPlayerMenuUpDelegate);
DECLARE_MULTICAST_DELEGATE(FOnPlayerMenuDownDelegate);
DECLARE_MULTICAST_DELEGATE(FOnPlayerMenuClickDelegate);

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
	FVector PlayerPosition;
	float GroundPosition;

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

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Motion)
		class AReadyObject* MyReadyObject;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UCameraComponent* MyCamera;


	bool IsRightGrip;
	bool IsLeftGrip;
	bool IsMenuOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true))
		USoundWave* StartVRSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true))
		USoundWave* StageChangeSound;

	// 현재 플레이어의 상태 (시작화면, 준비화면, 플레이)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EMyPlayerState MyPlayerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PlayerHasRightObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PlayerHasLeftObject;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

	class UPlayerAnim* LeftHandInstance;
	class UPlayerAnim* RightHandInstance;

	class UMyGameInstance* MyGameInstance;

	FOnPlayerMenuDelegate OnPlayerMenuDelegate;
	FOnPlayerMenuUpDelegate OnPlayerMenuUpDelegate;
	FOnPlayerMenuDownDelegate OnPlayerMenuDownDelegate;
	FOnPlayerMenuClickDelegate OnPlayerMenuClickDelegate;

	UFUNCTION(BlueprintCallable)
		void PressedMenuButton();

	UFUNCTION(BlueprintCallable)
		void PressedMenuUpButton();

	UFUNCTION(BlueprintCallable)
		void PressedMenuDownButton();

	UFUNCTION(BlueprintCallable)
		void PressedMenuClickButton();

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

	UFUNCTION(BlueprintCallable)
		void PositionClick();

	// 몬스터를 킬했을 시에 호출하는 함수
	UFUNCTION(BlueprintCallable)
		void KillingMonster();

	// 플레이어가 게임 중인지 아닌지 확인하는 함수
	UFUNCTION(BlueprintCallable)
		bool PlayerPlaying();

	// 플레이어의 게임 Start
	UFUNCTION(BlueprintCallable)
		void PlayerGameStart();


	// 이벤트
	UFUNCTION(BlueprintNativeEvent)
		void OnAllKillMonster();
	virtual void OnAllKillMonster_Implementation()
	{

	}

	// 이벤트
	UFUNCTION(BlueprintNativeEvent)
		void OnPlayerKillMonster();
	virtual void OnPlayerKillMonster_Implementation()
	{

	}
};
