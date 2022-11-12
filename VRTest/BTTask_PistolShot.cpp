// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PistolShot.h"
#include "AIMonster_Gun.h"
#include "MyAIController_Gun.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_PistolShot::UBTTask_PistolShot()
{
    bNotifyTick = true;
    IsAttacking = false;
}

EBTNodeResult::Type UBTTask_PistolShot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    auto MyAICharacter = Cast<AAIMonster_Gun>(OwnerComp.GetAIOwner()->GetPawn());
    if (MyAICharacter == nullptr)
        return EBTNodeResult::Failed;

    MyAICharacter->MonsterPistolShot();
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMyAIController_Gun::CanShot, false);
    OwnerComp.GetBlackboardComponent()->SetValueAsInt(AMyAIController_Gun::PistolShot, 0);

   // IsAttacking = true;
    //MyAICharacter->OnAttackEnd.AddLambda([this]() -> void {
        //IsAttacking = false;
        //});

    return EBTNodeResult::InProgress;
}

void UBTTask_PistolShot::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
    if (!IsAttacking)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
