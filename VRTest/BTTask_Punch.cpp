// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Punch.h"
#include "AIMonster.h"
#include "MyAIController.h"

UBTTask_Punch::UBTTask_Punch()
{
    bNotifyTick = true;
    IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Punch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    auto MyAICharacter = Cast<AAIMonster>(OwnerComp.GetAIOwner()->GetPawn());
    if (MyAICharacter == nullptr)
        return EBTNodeResult::Failed;

    MyAICharacter->MonsterPunch();
    IsAttacking = true;
    //MyAICharacter->OnAttackEnd.AddLambda([this]() -> void {
        //IsAttacking = false;
        //});

    return EBTNodeResult::InProgress;
}

void UBTTask_Punch::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
    if (!IsAttacking)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
