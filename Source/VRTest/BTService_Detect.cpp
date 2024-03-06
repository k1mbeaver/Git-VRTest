// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "MyAIController.h"
#include "MyAIController_Gun.h"
#include "AIMonster.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
    NodeName = TEXT("Detect");
    Interval = 0.3f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn)
        return;

    int FrameShot = OwnerComp.GetBlackboardComponent()->GetValueAsInt(AMyAIController_Gun::PistolShot);

    FrameShot = FrameShot + 1;

    OwnerComp.GetBlackboardComponent()->SetValueAsInt(AMyAIController_Gun::PistolShot, FrameShot);

    if (FrameShot >= 5)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMyAIController_Gun::CanShot, true);
        OwnerComp.GetBlackboardComponent()->SetValueAsInt(AMyAIController_Gun::PistolShot, 0);
    }
}

 