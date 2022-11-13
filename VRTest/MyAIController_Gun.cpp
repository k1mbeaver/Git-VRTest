// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController_Gun.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"
#include "AIMonster_Gun.h"

const FName AMyAIController_Gun::TargetKey(TEXT("Target"));
const FName AMyAIController_Gun::PistolShot(TEXT("PistolShot"));
const FName AMyAIController_Gun::CanShot(TEXT("CanShot"));

AMyAIController_Gun::AMyAIController_Gun(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/BT_AI_GUN.BT_AI_GUN'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	BTAsset_Component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BBAsset = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AMyAIController_Gun::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BTAsset);
	BTAsset_Component->StartTree(*BTAsset);

	AMyCharacter* myPlayerCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());

	GetBlackboardComponent()->SetValueAsObject(AMyAIController_Gun::TargetKey, myPlayerCharacter);
	GetBlackboardComponent()->SetValueAsBool(AMyAIController_Gun::CanShot, false);
}

void AMyAIController_Gun::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AICharacter = Cast<AAIMonster_Gun>(InPawn);
}

UBlackboardComponent* AMyAIController_Gun::get_blackboard() const
{
	return BBAsset;
}

void AMyAIController_Gun::RunAI()
{
	if (BBAsset)
	{
		BBAsset->InitializeBlackboard(*BTAsset->BlackboardAsset);
	}
}

void AMyAIController_Gun::StopAI()
{
	if (this == nullptr) // 서버, 클라이언트 할때는 이거 해줘야하나?
	{
		return;
	}

	BTAsset_Component->StopTree(EBTStopMode::Safe);
}

