// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerPistol.generated.h"

UCLASS()
class VRTEST_API APlayerPistol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerPistol();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int nPistolMagazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsControlling;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class APlayerProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Motion)
		class UMotionControllerComponent* PlayerController;

	class AMyPlayerController* myPlayerController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void PlayerShot();

	UFUNCTION(BlueprintCallable)
		void SetPlayerMotion(UMotionControllerComponent* getController);
};
