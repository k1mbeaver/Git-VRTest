// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Punch.generated.h"

/**
 * 
 */
UCLASS()
class VRTEST_API UBTTask_Punch : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
    UBTTask_Punch();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
    bool IsAttacking = false;
};
