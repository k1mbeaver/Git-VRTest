// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController_Gun.generated.h"

/**
 * 
 */
UCLASS()
class VRTEST_API AMyAIController_Gun : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController_Gun(FObjectInitializer const& object_initializer);
	virtual void OnPossess(APawn* InPawn) override;
	void BeginPlay() override;

	class UBlackboardComponent* get_blackboard() const;

	static const FName TargetKey;
	static const FName PistolShot;
	static const FName CanShot;

	void RunAI();
	void StopAI();

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BTAsset;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BTAsset_Component;

	UPROPERTY()
		class UBlackboardComponent* BBAsset;

	UPROPERTY()
		class AAIMonster_Gun* AICharacter;
};
