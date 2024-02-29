// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerGround.generated.h"

UCLASS()
class VRTEST_API APlayerGround : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerGround();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void UpGround();

	UFUNCTION(BlueprintCallable)
		void DownGround();

	UFUNCTION(BlueprintCallable)
		void GoGround();

	UFUNCTION(BlueprintCallable)
		void BackGround();

	UFUNCTION(BlueprintCallable)
		void LeftGround();

	UFUNCTION(BlueprintCallable)
		void RightGround();
};
