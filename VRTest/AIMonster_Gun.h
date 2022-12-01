// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIMonster_Gun.generated.h"

UCLASS()
class VRTEST_API AAIMonster_Gun : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIMonster_Gun();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Speed, Meta = (AllowPrivateAccess = true))
		float MonsterSpeed;

	class UAIAnimInstance* MonsterAnimation;
	class AMyAIController_Gun* MonsterController;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USceneComponent* MuzzleLocation;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true))
		//UAnimMontage* AttackMontage;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UParticleSystem* AttackParticle;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundWave* AttackSound;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true))
			USoundWave* BreakAISound;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class APlayerProjectile> ProjectileClass;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

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
		void MonsterPistolShot();
};
