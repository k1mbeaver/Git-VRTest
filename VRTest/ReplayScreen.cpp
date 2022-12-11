// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayScreen.h"
#include "MyGameInstance.h"

// Sets default values
AReplayScreen::AReplayScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReplayScreen::BeginPlay()
{
	Super::BeginPlay();
	
	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
}

// Called every frame
void AReplayScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReplayScreen::GameReplay()
{
	MyGameInstance->SetPlayerStage("Player", 0);
}
