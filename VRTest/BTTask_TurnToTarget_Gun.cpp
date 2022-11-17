// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget_Gun.h"
#include "AIMonster_Gun.h"
#include "MyCharacter.h"
#include "MyAIController_Gun.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget_Gun::UBTTask_TurnToTarget_Gun()
{
    NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget_Gun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    auto MyAI = Cast<AAIMonster_Gun>(OwnerComp.GetAIOwner()->GetPawn());
    if (nullptr == MyAI)
        return EBTNodeResult::Failed;

    auto Target = Cast<AMyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMyAIController_Gun::TargetKey));
    if (nullptr == Target)
        return EBTNodeResult::Failed;

    // Gun AI의 경우에는 총구 방향이 캐릭터에게 향하도록 하자

    FVector LookVector = Target->GetActorLocation() - MyAI->GetActorLocation();
    LookVector.Z = 0.0f;
    FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
    MyAI->SetActorRotation(FMath::RInterpTo(MyAI->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

    return EBTNodeResult::Succeeded;
}
