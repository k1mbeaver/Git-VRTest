// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

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

};
