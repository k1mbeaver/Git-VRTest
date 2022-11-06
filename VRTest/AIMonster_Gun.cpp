// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMonster_Gun.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAIMonster_Gun::AAIMonster_Gun()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->JumpZVelocity = 400.0f;

	// ĳ���Ͱ� �ڿ������� ȸ���ϰ� 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ProjectGunMonster"));

	MonsterSpeed = 200.0f; // ���ǵ�� ���� �ϵ��ڵ� �صΰ� ���߿� ������ ���̺�� �ű���

	GetCharacterMovement()->MaxWalkSpeed = MonsterSpeed;
}

// Called when the game starts or when spawned
void AAIMonster_Gun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIMonster_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIMonster_Gun::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

