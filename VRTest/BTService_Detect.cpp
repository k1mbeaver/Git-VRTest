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

    /*
    if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMyAIController_Gun::CanShot) == true)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMyAIController_Gun::CanShot, false);
        return;
    }
    */

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn)
        return;
   
    /*
    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
    bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);

    if (bResult)
    {
        for (auto const& OverlapResult : OverlapResults)
        {
            AMyCharacter* MyCharacter = Cast<AMyCharacter>(OverlapResult.GetActor());

            if (MyCharacter)
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMyAIController::TargetKey, MyCharacter);
                DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

                DrawDebugPoint(World, MyCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
                DrawDebugLine(World, ControllingPawn->GetActorLocation(), MyCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
                return;
            }

            else
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMyAIController::TargetKey, nullptr);
            }
        }
    }
    
    DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
    */

    int FrameShot = OwnerComp.GetBlackboardComponent()->GetValueAsInt(AMyAIController_Gun::PistolShot);

    FrameShot = FrameShot + 1;

    OwnerComp.GetBlackboardComponent()->SetValueAsInt(AMyAIController_Gun::PistolShot, FrameShot);

    if (FrameShot >= 5)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMyAIController_Gun::CanShot, true);
        OwnerComp.GetBlackboardComponent()->SetValueAsInt(AMyAIController_Gun::PistolShot, 0);
    }
}

 