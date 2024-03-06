// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMonster.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "AIAnimInstance.h"
#include "MyAIController.h"
#include "MyCharacter.h"
#include "MyGameInstance.h"

// Sets default values
AAIMonster::AAIMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->JumpZVelocity = 400.0f;

	// 캐릭터가 자연스럽게 회전하게 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ProjectMonster"));

	GetCharacterMovement()->MaxWalkSpeed = MonsterSpeed;

	AttackRange = 250.0f;
	AttackRadius = 50.0f;

	IsAttacking = false;
}

// Called when the game starts or when spawned
void AAIMonster::BeginPlay()
{
	Super::BeginPlay();

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	
	MonsterAnimation = Cast<UAIAnimInstance>(GetMesh()->GetAnimInstance());
	MonsterController = Cast<AMyAIController>(GetController());

	AttackMontage = MyGameInstance->GetMontage("AIAnimation");
	MonsterSpeed = MyGameInstance->GetAISpeed("PunchAI");
	BreakAISound = MyGameInstance->GetSound("BreakAISound");

	GetCharacterMovement()->MaxWalkSpeed = MonsterSpeed;

	MonsterAnimation->AttackEnd_Attack.AddUObject(this, &AAIMonster::MonsterPunchEnd);
	MonsterAnimation->AttackCheck_Attack.AddUObject(this, &AAIMonster::AttackCheck);
}

// Called every frame
void AAIMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIMonster::MonsterDead()
{
	MyGameInstance->SetPlayerKill();

	MonsterAnimation->SetDeadAnim();
	MonsterController->StopAI();
}

void AAIMonster::MonsterPunch()
{
	if (!IsAttacking)
	{
		IsAttacking = true;

		auto AnimInstance = Cast<UAIAnimInstance>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimInstance) return;

		AnimInstance->PlayAttackMontage(AttackMontage);
		AnimInstance->IsAttacking = true;
	}
}

void AAIMonster::MonsterPunchEnd()
{
	auto AnimInstance = Cast<UAIAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	IsAttacking = false;
	AnimInstance->IsAttacking = false;

	OnAttackEnd.Broadcast();
}

void AAIMonster::AttackCheck()
{

}