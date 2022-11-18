// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

struct FPlayerDataTable;
struct FParticleDataTable;
struct FAnimationDataTable;
struct FSoundDataTable;

class UDataTable;
/**
 * 
 */
UCLASS()
class VRTEST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

		UMyGameInstance();

public:

private:
	UPROPERTY()
		UDataTable* FPlayerFileTable;

};
