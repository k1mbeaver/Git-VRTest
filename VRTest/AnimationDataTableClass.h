// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "AnimationDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FAnimationDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* MyMontage;

	// �ִϸ��̼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UAnimInstance> MyAnimation;
};

UCLASS()
class VRTEST_API AAnimationDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimationDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
