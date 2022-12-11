// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "PlayerAnim.h"
#include "PlayerPistol.h"
#include "MotionControllerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ActorComponent.h"
#include "MyGameInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ReadyObject.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MotionLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MOTIONLEFT"));
	MotionRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MOTIONRIGHT"));

	MeshLeft = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESHLEFT"));
	MeshRight = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESHRIGHT"));

	//MyReadyObject = GetCapsuleComponent()->GetChildComponent(0);

	MotionLeft->SetupAttachment(GetCapsuleComponent());
	MotionRight->SetupAttachment(GetCapsuleComponent());
	
	MeshLeft->SetupAttachment(MotionLeft);
	MeshRight->SetupAttachment(MotionRight);

	PlayerHasRightObject = false;
	PlayerHasLeftObject = false;

	IsRightGrip = false;
	IsLeftGrip = false;

	CurrentMonsterKill = 0;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	
	LeftHandInstance = Cast<UPlayerAnim>(MeshLeft->GetAnimInstance());
	RightHandInstance = Cast<UPlayerAnim>(MeshRight->GetAnimInstance());

	PlayerHasRightObject = false;
	PlayerHasLeftObject = false;

	IsRightGrip = false;
	IsLeftGrip = false;

	PlayerStage = MyGameInstance->GetPlayerStage("Player");
	TotalMonsterKill = MyGameInstance->GetAICount(PlayerStage);
	StartVRSound = MyGameInstance->GetSound("StartVRSound");
	StageChangeSound = MyGameInstance->GetSound("StageChange");

	if (PlayerStage == 0)
	{
		MyPlayerState = EMyPlayerState::E_Start;
	}

	else if (PlayerStage == 1)
	{
		MyPlayerState = EMyPlayerState::E_Ready;
	}

	else if (PlayerStage == 7)
	{
		MyPlayerState = EMyPlayerState::E_Exit;
	}

	else
	{
		MyPlayerState = EMyPlayerState::E_Play;
		GameStatic->PlaySoundAtLocation(GetWorld(), StageChangeSound, GetActorLocation());
	}

	GetWorldSettings()->SetTimeDilation(1.0f);
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

	//PlayerInputComponent->BindAction("TriggerLeft", IE_Pressed, this, &AMyCharacter::PressedLeftGrip);
	//PlayerInputComponent->BindAction("TriggerLeft", IE_Released, this, &AMyCharacter::ReleasedLeftGrip);
	//PlayerInputComponent->BindAction("TriggerRight", IE_Pressed, this, &AMyCharacter::PressedRightGrip);
	//PlayerInputComponent->BindAction("TriggerRight", IE_Released, this, &AMyCharacter::ReleasedRightGrip);
}

void AMyCharacter::PressedLeftGrip()
{
	if (!IsLeftGrip)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LeftPunchPressed"));
		LeftHandInstance->bGrip = true;
	}
}

void AMyCharacter::ReleasedLeftGrip()
{
	if (!IsLeftGrip)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LeftPunchReleased"));
		LeftHandInstance->bGrip = false;
	}
}

void AMyCharacter::PressedRightGrip()
{
	if (!IsRightGrip)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("RightPunchPressed"));
		RightHandInstance->bGrip = true;
	}
}

void AMyCharacter::ReleasedRightGrip()
{
	if (!IsRightGrip)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("RightPunchReleased"));
		RightHandInstance->bGrip = false;
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

void AMyCharacter::PlayerDead()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerDead"));

	MyGameInstance->SetPlayerStage("Player", 1);
	
	UGameplayStatics::OpenLevel(GetWorld(), "ReadyMap");
}

void AMyCharacter::KillingMonster()
{
	CurrentMonsterKill++;

	if (CurrentMonsterKill == TotalMonsterKill)
	{
		OnAllKillMonster();
		MyGameInstance->SetPlayerStage("Player", MyGameInstance->GetPlayerStage("Player") + 1);
		/*
		FName fnMapName = FName(MyGameInstance->GetNextMapName(PlayerStage));

		MyGameInstance->SetPlayerStage("Player", PlayerStage + 1);

		UGameplayStatics::OpenLevel(GetWorld(), fnMapName);
		*/
	}
}

bool AMyCharacter::PlayerPlaying()
{
	if (MyPlayerState == EMyPlayerState::E_Play)
	{
		return true;
	}

	else
	{
		return false;
	}
}

void AMyCharacter::PlayerGameStart()
{
	MyGameInstance->SetPlayerStage("Player", PlayerStage + 1);
	UGameplayStatics::OpenLevel(GetWorld(), "ReadyMap");
	//UGameplayStatics::OpenLevel(GetWorld(), fnMapName);
}