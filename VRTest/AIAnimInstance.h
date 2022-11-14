// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AIAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FAttackCheck_AttackDelegate); // ����
DECLARE_MULTICAST_DELEGATE(FAttackEnd_AttackDelegate); // ���� ��
/**
 * 
 */
UCLASS()
class VRTEST_API UAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	UAIAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed; // AnimInstance�� ����ؼ� C++ ��ũ���� �� ���� �������Ʈ���� ����� �����ϴ�.

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;

public:

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

private:
	UFUNCTION()
		void AnimNotify_AttackCheck();

	UFUNCTION()
		void AnimNotify_AttackEnd();
public:
	void SetDeadAnim();
	void PlayAttackMontage(UAnimMontage* GetAttackMontage);

	FAttackCheck_AttackDelegate AttackCheck_Attack;
	FAttackEnd_AttackDelegate AttackEnd_Attack;

};
