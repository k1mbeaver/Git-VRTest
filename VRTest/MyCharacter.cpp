// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "PlayerAnim.h"
#include "PlayerPistol.h"
#include "MotionControllerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MotionLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MOTIONLEFT"));
	MotionRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MOTIONRIGHT"));

	MeshLeft = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESHLEFT"));
	MeshRight = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESHRIGHT"));

	MotionLeft->SetupAttachment(GetCapsuleComponent());
	MotionRight->SetupAttachment(GetCapsuleComponent());

	MeshLeft->SetupAttachment(MotionLeft);
	MeshRight->SetupAttachment(MotionRight);

	IsRightGrip = false;
	IsLeftGrip = false;

	// ���� �÷��̾��� ���� ���´� �ָ����� ����Ʈ��
	PlayerWeapon = EPlayerWeapon::E_Punch;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	LeftHandInstance = Cast<UPlayerAnim>(MeshLeft->GetAnimInstance());
	RightHandInstance = Cast<UPlayerAnim>(MeshRight->GetAnimInstance());

	GetWorldSettings()->SetTimeDilation(0.5f);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TriggerLeft", IE_Pressed, this, &AMyCharacter::PressedLeftGrip);
	PlayerInputComponent->BindAction("TriggerLeft", IE_Released, this, &AMyCharacter::ReleasedLeftGrip);
	PlayerInputComponent->BindAction("TriggerRight", IE_Pressed, this, &AMyCharacter::PressedRightGrip);
	PlayerInputComponent->BindAction("TriggerRight", IE_Released, this, &AMyCharacter::ReleasedRightGrip);
}

void AMyCharacter::PressedLeftGrip()
{
	if (PlayerWeapon == EPlayerWeapon::E_Punch)
	{
		if (!IsLeftGrip)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LeftPunchPressed"));
			LeftHandInstance->bGrip = true;
		}
	}

	else if (PlayerWeapon == EPlayerWeapon::E_Pistol)
	{
		//myLeftPlayerPistol->PlayerShot();
	}
}

void AMyCharacter::ReleasedLeftGrip()
{
	if (PlayerWeapon == EPlayerWeapon::E_Punch)
	{
		if (!IsLeftGrip)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LeftPunchReleased"));
			LeftHandInstance->bGrip = false;
		}
	}
}

void AMyCharacter::PressedRightGrip()
{
	if (PlayerWeapon == EPlayerWeapon::E_Punch)
	{
		if (!IsRightGrip)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("RightPunchPressed"));
			RightHandInstance->bGrip = true;
		}
	}

	else if (PlayerWeapon == EPlayerWeapon::E_Pistol)
	{
		//myRightPlayerPistol->PlayerShot();
	}
}

void AMyCharacter::ReleasedRightGrip()
{
	if (PlayerWeapon == EPlayerWeapon::E_Punch)
	{
		if (!IsRightGrip)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("RightPunchReleased"));
			RightHandInstance->bGrip = false;
		}
	}
}

void AMyCharacter::SetIsRightGrip()
{
	if (IsRightGrip)
	{
		IsRightGrip = false;
	}

	else
	{
		IsRightGrip = true;
	}
}

void AMyCharacter::SetIsLeftGrip()
{
	if (IsLeftGrip)
	{
		IsLeftGrip = false;
	}

	else
	{
		IsLeftGrip = true;
	}
}

void AMyCharacter::SetPlayerWeapon(EPlayerWeapon myPlayerWeapon)
{
	PlayerWeapon = myPlayerWeapon;
}

EPlayerWeapon AMyCharacter::GetPlayerWeapon()
{
	return PlayerWeapon;
}

void AMyCharacter::SetPlayerLeftPistol(UActorComponent* myPistol)
{
	myLeftPlayerPistol = Cast<APlayerPistol>(myPistol);
}

void AMyCharacter::SetPlayerRightPistol(UActorComponent* myPistol)
{
	myRightPlayerPistol = Cast<APlayerPistol>(myPistol);
}