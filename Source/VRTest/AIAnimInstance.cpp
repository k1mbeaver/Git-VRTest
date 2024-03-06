// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UAIAnimInstance::UAIAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	IsAttacking = false;
}

void UAIAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // 폰에 접근해서 폰의 속력 값을 얻어온다.
	if (!::IsValid(Pawn)) return;

	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UAIAnimInstance::SetDeadAnim()
{
	IsDead = true;
}

void UAIAnimInstance::PlayAttackMontage(UAnimMontage* GetAttackMontage)
{
	Montage_Play(GetAttackMontage, 1.0f);
}

void UAIAnimInstance::AnimNotify_AttackCheck()
{
	AttackCheck_Attack.Broadcast();
}

void UAIAnimInstance::AnimNotify_AttackEnd()
{
	AttackEnd_Attack.Broadcast();
}