// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMonster.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAIMonster::AAIMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// ĳ���Ͱ� �ڿ������� ȸ���ϰ� 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ProjectMonster"));
}

// Called when the game starts or when spawned
void AAIMonster::BeginPlay()
{
	Super::BeginPlay();
	
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

