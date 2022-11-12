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

// Sets default values
AAIMonster_Gun::AAIMonster_Gun()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->JumpZVelocity = 400.0f;

	// 캐릭터가 자연스럽게 회전하게 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ProjectMonster"));

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(GetCapsuleComponent());

	MonsterSpeed = 200.0f; // 스피드는 지금 하드코딩 해두고 나중에 데이터 테이블로 옮기자

	GetCharacterMovement()->MaxWalkSpeed = MonsterSpeed;
}

// Called when the game starts or when spawned
void AAIMonster_Gun::BeginPlay()
{
	Super::BeginPlay();
	
	MonsterAnimation = Cast<UAIAnimInstance>(GetMesh()->GetAnimInstance());
	MonsterController = Cast<AMyAIController_Gun>(GetController());
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

	// 몬스터 들이 쓰러지면 충돌 X
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
}

void AAIMonster_Gun::MonsterPistolShot()
{
	GameStatic->SpawnEmitterAttached(AttackParticle, MuzzleLocation, FName("MuzzleLocatiom")); // 파티클 출력
	UGameplayStatics::PlaySoundAtLocation(this, AttackSound, MuzzleLocation->GetComponentLocation()); // 사운드 출력

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
