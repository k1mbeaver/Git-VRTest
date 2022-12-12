// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitScreen.h"
#include "MyGameInstance.h"

// Sets default values
AExitScreen::AExitScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExitScreen::BeginPlay()
{
	Super::BeginPlay();
	
	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
}

// Called every frame
void AExitScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExitScreen::GameExit()
{
	MyGameInstance->SetPlayerStage("Player", 8);
}

