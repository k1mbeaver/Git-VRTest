// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"
#include "AIMonster.h"

const FName AMyAIController::TargetKey(TEXT("Target"));

AMyAIController::AMyAIController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/BT_AI.BT_AI'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	BTAsset_Component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BBAsset = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BTAsset);
	BTAsset_Component->StartTree(*BTAsset);

	AMyCharacter* myPlayerCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());

	GetBlackboardComponent()->SetValueAsObject(AMyAIController::TargetKey, myPlayerCharacter);
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AICharacter = Cast<AAIMonster>(InPawn);
}

UBlackboardComponent* AMyAIController::get_blackboard() const
{
	return BBAsset;
}

void AMyAIController::RunAI()
{
	if (BBAsset)
	{
		BBAsset->InitializeBlackboard(*BTAsset->BlackboardAsset);
	}
}

void AMyAIController::StopAI()
{
	if (this == nullptr) // 서버, 클라이언트 할때는 이거 해줘야하나?
	{
		return;
	}

	AMyCharacter* myPlayerCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());
	myPlayerCharacter->KillingMonster();

	BTAsset_Component->StopTree(EBTStopMode::Safe);
}
