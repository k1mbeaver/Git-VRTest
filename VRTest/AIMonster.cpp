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

	GetCharacterMovement()->MaxWalkSpeed = MonsterSpeed;

	//MonsterAnimation->AttackCheck_Attack.AddUObject(this, &AAIMonster::AttackCheck);
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
	MonsterAnimation->SetDeadAnim();
	MonsterController->StopAI();

	// 몬스터 들이 쓰러지면 충돌 X, 여기서 몬스터의 모든 콜리전을 땅빼고 무시로 바꾸기 블루프린트로 진행한다.
	/*
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	*/
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

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("MonsterKickEnd!"));
}

void AAIMonster::AttackCheck()
{
	//KickCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Block);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("MonsterKickStart!"));
	/*
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // Monster의 Attack 채널
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	#if ENABLE_DRAW_DEBUG
		FVector TraceVec = GetActorForwardVector() * AttackRange;
		FVector Center = GetActorLocation() + TraceVec * 0.5f;
		float HalfHeight = AttackRange * 0.5f + AttackRadius;
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		// 이거는 에디터에서만 사용하는거
		DrawDebugCapsule(GetWorld(),
			Center,
			HalfHeight,
			AttackRadius,
			CapsuleRot,
			DrawColor,
			false,
			DebugLifeTime);
		
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("MonsterAttack!")); // 플레이어가 펀치하는지 확인용

	#endif


	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hit!"));
			//FDamageEvent DamageEvent;
			//AMyCharacter* HitCharacter = Cast<AMyCharacter>(HitResult.Actor);
			//HitCharacter->PlayerDead();
		}
	}
	*/
}