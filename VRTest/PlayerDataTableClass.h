// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "PlayerDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FPlayerDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PlayerStage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* PlayerShootingParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PositionHeight;
};

UCLASS()
class VRTEST_API APlayerDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
