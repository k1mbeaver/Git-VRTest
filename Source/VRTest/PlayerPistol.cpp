// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPistol.h"
#include "Components/CapsuleComponent.h"
#include "PlayerProjectile.h"
#include "MyPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "MotionControllerComponent.h"

// Sets default values
APlayerPistol::APlayerPistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	nPistolMagazine = 5;
	IsControlling = false;
}

// Called when the game starts or when spawned
void APlayerPistol::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerPistol::PlayerShot()
{
	if (nPistolMagazine <= 0)
	{
		return;
	}
	
	else
	{
		nPistolMagazine -= 1;
	}
}

void APlayerPistol::SetPlayerMotion(UMotionControllerComponent* getController)
{
	PlayerController = getController;
}

