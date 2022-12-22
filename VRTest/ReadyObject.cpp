// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadyObject.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AReadyObject::AReadyObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReadyObject::BeginPlay()
{
	Super::BeginPlay();

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	BreakObjectSound = MyGameInstance->GetSound("BreakObjectSound");
	PlayerStage = MyGameInstance->GetPlayerStage("Player");

	if (PlayerStage <= 1)
	{
		bPlaying = false;
	}

	else
	{
		bPlaying = true;
	}
}

// Called every frame
void AReadyObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReadyObject::StartStage()
{
	PlayerStage = PlayerStage++;
	MyGameInstance->SetPlayerStage("Player", PlayerStage);
	MyGameInstance->InitializePlayerKill();

	FName fnMapName = MyGameInstance->GetMapName(PlayerStage);

	UGameplayStatics::OpenLevel(GetWorld(), fnMapName);
}

