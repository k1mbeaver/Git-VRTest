// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIMonster.generated.h"

UCLASS()
class VRTEST_API AAIMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIMonster();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Speed, Meta = (AllowPrivateAccess = true))
		float MonsterSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	class UAIAnimInstance* MonsterAnimation;
	class AMyAIController* MonsterController;
	class UMyGameInstance* MyGameInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void MonsterDead();

	UFUNCTION(BlueprintCallable)
		void MonsterPunch();

	UFUNCTION(BlueprintCallable)
		void MonsterPunchEnd();
};
