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
}

// Called every frame
void AReadyObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReadyObject::StartStage()
{
	MyGameInstance->SetPlayerStage("Player", MyGameInstance->GetPlayerStage("Player") + 1);

	UGameplayStatics::OpenLevel(GetWorld(), "Tutorial");
}

