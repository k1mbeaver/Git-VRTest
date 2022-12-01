// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMonster_Gun.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "AIAnimInstance.h"
#include "MyAIController_Gun.h"
#include "PlayerProjectile.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

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

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ProjectMonster"));

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(GetCapsuleComponent());

	MonsterSpeed = 200.0f; // ���ǵ�� ���� �ϵ��ڵ� �صΰ� ���߿� ������ ���̺�� �ű���

	GetCharacterMovement()->MaxWalkSpeed = MonsterSpeed;
}

// Called when the game starts or when spawned
void AAIMonster_Gun::BeginPlay()
{
	Super::BeginPlay();
	
	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	MonsterAnimation = Cast<UAIAnimInstance>(GetMesh()->GetAnimInstance());
	MonsterController = Cast<AMyAIController_Gun>(GetController());

	MonsterSpeed = MyGameInstance->GetAISpeed("GunAI");
	AttackParticle = MyGameInstance->GetParticle("AIShot");
	AttackSound = MyGameInstance->GetSound("AIShot");
	BreakAISound = MyGameInstance->GetSound("BreakAISound");
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

void AAIMonster_Gun::MonsterDead()
{
	MonsterAnimation->SetDeadAnim();
	MonsterController->StopAI();

	// ���� ���� �������� �浹 X
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
}

void AAIMonster_Gun::MonsterPistolShot()
{
	GameStatic->SpawnEmitterAttached(AttackParticle, MuzzleLocation, FName("MuzzleLocatiom")); // ��ƼŬ ���
	UGameplayStatics::PlaySoundAtLocation(this, AttackSound, MuzzleLocation->GetComponentLocation()); // ���� ���

	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();

		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation());

			// + SpawnRotation.RotateVector(GunOffset)
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<APlayerProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}
