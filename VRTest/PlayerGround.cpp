// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGround.h"
#include "MyGameInstance.h"

// Sets default values
APlayerGround::APlayerGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerGround::BeginPlay()
{
	Super::BeginPlay();
	
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	FVector customPosition = MyGameInstance->GetPlayerPosition("Player");
	FVector curPosition = GetActorLocation();

	curPosition.X += customPosition.X;
	curPosition.Y += customPosition.Y;
	curPosition.Z += customPosition.Z;

	SetActorLocation(curPosition);
}

// Called every frame
void APlayerGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerGround::UpGround()
{
	FVector groundLocation = GetActorLocation();
	groundLocation.Z = groundLocation.Z + 10.0f;
	SetActorLocation(groundLocation);
}

void APlayerGround::DownGround()
{
	FVector groundLocation = GetActorLocation();
	groundLocation.Z = groundLocation.Z - 10.0f;
	SetActorLocation(groundLocation);
}

void APlayerGround::GoGround()
{
	FVector groundLocation = GetActorLocation();
	groundLocation.X = groundLocation.X + 10.0f;
	SetActorLocation(groundLocation);
}

void APlayerGround::BackGround()
{
	FVector groundLocation = GetActorLocation();
	groundLocation.X = groundLocation.X - 10.0f;
	SetActorLocation(groundLocation);
}

void APlayerGround::LeftGround()
{
	FVector groundLocation = GetActorLocation();
	groundLocation.Y = groundLocation.Y - 10.0f;
	SetActorLocation(groundLocation);
}

void APlayerGround::RightGround()
{
	FVector groundLocation = GetActorLocation();
	groundLocation.Y = groundLocation.Y + 10.0f;
	SetActorLocation(groundLocation);
}
