// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "AIMonster.h"
#include "AIMonster_Gun.h"
#include "MyCharacter.h"
#include "MyAIController.h"
#include "MyAIController_Gun.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
    NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    auto MyAI = Cast<AAIMonster>(OwnerComp.GetAIOwner()->GetPawn());
    if (nullptr == MyAI)
        return EBTNodeResult::Failed;

    auto Target = Cast<AMyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMyAIController::TargetKey));
    if (nullptr == Target)
        return EBTNodeResult::Failed;

    FVector LookVector = Target->GetActorLocation() - MyAI->GetActorLocation();
    LookVector.Z = 0.0f;
    FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
    MyAI->SetActorRotation(FMath::RInterpTo(MyAI->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

    return EBTNodeResult::Succeeded;
}

