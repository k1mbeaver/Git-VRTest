// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TurnToTarget_Gun.generated.h"

/**
 * 
 */
UCLASS()
class VRTEST_API UBTTask_TurnToTarget_Gun : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_TurnToTarget_Gun();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
