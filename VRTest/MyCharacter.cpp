// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "PlayerAnim.h"
#include "PlayerPistol.h"
#include "MotionControllerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "MyGameInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ReadyObject.h"
#include "PlayerGround.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MotionLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MOTIONLEFT"));
	MotionRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MOTIONRIGHT"));

	MeshLeft = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESHLEFT"));
	MeshRight = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESHRIGHT"));

	CameraHolder = CreateDefaultSubobject<USceneComponent>(TEXT("CAMERAHOLDER"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MYCAMERA"));

	MotionLeft->SetupAttachment(GetCapsuleComponent());
	MotionRight->SetupAttachment(GetCapsuleComponent());
	CameraHolder->SetupAttachment(GetCapsuleComponent());

	MeshLeft->SetupAttachment(MotionLeft);
	MeshRight->SetupAttachment(MotionRight);

	MyCamera->SetupAttachment(CameraHolder);

	PlayerHasRightObject = false;
	PlayerHasLeftObject = false;

	IsRightGrip = false;
	IsLeftGrip = false;
	IsMenuOn = false;

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

	else if (PlayerStage == 8)
	{
		MyPlayerState = EMyPlayerState::E_Test;
	}

	else
	{
		MyPlayerState = EMyPlayerState::E_Play;
		GameStatic->PlaySoundAtLocation(GetWorld(), StageChangeSound, GetActorLocation());
	}

	GetWorldSettings()->SetTimeDilation(1.0f);

	FVector customPosition = MyGameInstance->GetPlayerPosition("Player");
	FVector curPosition = GetCapsuleComponent()->GetComponentLocation();

	curPosition.X += customPosition.X;
	curPosition.Y += customPosition.Y;
	curPosition.Z += customPosition.Z;

	GetCapsuleComponent()->SetWorldLocation(curPosition);
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

	PlayerInputComponent->BindAction("MenuUp", IE_Pressed, this, &AMyCharacter::PressedMenuUpButton);
	PlayerInputComponent->BindAction("MenuDown", IE_Released, this, &AMyCharacter::PressedMenuDownButton);
	PlayerInputComponent->BindAction("MenuClick", IE_Pressed, this, &AMyCharacter::PressedMenuClickButton);
	PlayerInputComponent->BindAction("PositionUp", IE_Pressed, this, &AMyCharacter::PositionUp);
	PlayerInputComponent->BindAction("PositionDown", IE_Pressed, this, &AMyCharacter::PositionDown);
	PlayerInputComponent->BindAction("PositionGo", IE_Pressed, this, &AMyCharacter::PositionGo);
	PlayerInputComponent->BindAction("PositionBack", IE_Pressed, this, &AMyCharacter::PositionBack);
	PlayerInputComponent->BindAction("PositionLeft", IE_Pressed, this, &AMyCharacter::PositionLeft);
	PlayerInputComponent->BindAction("PositionRight", IE_Pressed, this, &AMyCharacter::PositionRight);
	PlayerInputComponent->BindAction("TutorialPrev", IE_Pressed, this, &AMyCharacter::PressedTutorialPrevButton);
	PlayerInputComponent->BindAction("TutorialNext", IE_Pressed, this, &AMyCharacter::PressedTutorialNextButton);
	PlayerInputComponent->BindAction("TutorialClose", IE_Pressed, this, &AMyCharacter::PressedTutorialCloseButton);
}

void AMyCharacter::PressedLeftGrip()
{
	if (!IsLeftGrip)
	{
		LeftHandInstance->bGrip = true;
	}
}

void AMyCharacter::ReleasedLeftGrip()
{
	if (!IsLeftGrip)
	{
		LeftHandInstance->bGrip = false;
	}
}

void AMyCharacter::PressedRightGrip()
{
	if (!IsRightGrip)
	{
		RightHandInstance->bGrip = true;
	}
}

void AMyCharacter::ReleasedRightGrip()
{
	if (!IsRightGrip)
	{
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
}

void AMyCharacter::PressedMenuButton()
{
	if (!IsMenuOn)
	{
		OnPlayerMenuDelegate.Broadcast();
		IsMenuOn = true;
	}

	else
	{
		OnPlayerMenuDelegate.Broadcast();
		IsMenuOn = false;
	}
}

void AMyCharacter::PressedMenuUpButton()
{
	if (IsMenuOn)
	{
		OnPlayerMenuUpDelegate.Broadcast();
	}
}

void AMyCharacter::PressedMenuDownButton()
{
	if (IsMenuOn)
	{
		OnPlayerMenuDownDelegate.Broadcast();
	}
}

void AMyCharacter::PressedMenuClickButton()
{
	if (IsMenuOn)
	{
		OnPlayerMenuClickDelegate.Broadcast();
	}
}

void AMyCharacter::PressedTutorialNextButton()
{
	if (PlayerStage == 8)
	{
		OnPlayerTutorialNextDelegate.Broadcast();
	}
}

void AMyCharacter::PressedTutorialPrevButton()
{
	if (PlayerStage == 8)
	{
		OnPlayerTutorialPrevDelegate.Broadcast();
	}
}

void AMyCharacter::PressedTutorialCloseButton()
{
	if (PlayerStage == 8)
	{
		OnPlayerTutorialCloseDelegate.Broadcast();
	}
}

void AMyCharacter::PositionUp()
{
	if (PlayerStage != 8)
	{
		return;
	}

	if (myGround == nullptr)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			TArray<AActor*> FoundActors;

			FString GroundTag = "PlayerGround";

			UGameplayStatics::GetAllActorsWithTag(world, FName(*GroundTag), FoundActors);

			if (FoundActors.Num() > 0)
			{
				myGround = Cast<APlayerGround>(FoundActors[0]);
			}
		}
	}

	myGround->UpGround();

	FVector curLocation = GetCapsuleComponent()->GetComponentLocation();
	curLocation.Z = curLocation.Z + 11.0f;
	GetCapsuleComponent()->SetWorldLocation(curLocation);

	FVector curPosition = MyGameInstance->GetPlayerPosition("Player");
	curPosition.Z = curPosition.Z + 11.0f;

	MyGameInstance->SetPlayerPosition("Player", curPosition);
}

void AMyCharacter::PositionDown()
{
	if (PlayerStage != 8)
	{
		return;
	}

	if (myGround == nullptr)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			TArray<AActor*> FoundActors;

			FString GroundTag = "PlayerGround";

			UGameplayStatics::GetAllActorsWithTag(world, FName(*GroundTag), FoundActors);

			if (FoundActors.Num() > 0)
			{
				myGround = Cast<APlayerGround>(FoundActors[0]);
			}
		}
	}

	myGround->DownGround();

	FVector curLocation = GetCapsuleComponent()->GetComponentLocation();
	curLocation.Z = curLocation.Z - 9.0f;
	GetCapsuleComponent()->SetWorldLocation(curLocation);

	FVector curPosition = MyGameInstance->GetPlayerPosition("Player");
	curPosition.Z = curPosition.Z - 9.0f;

	MyGameInstance->SetPlayerPosition("Player", curPosition);
}

void AMyCharacter::PositionGo()
{
	if (PlayerStage != 8)
	{
		return;
	}

	if (myGround == nullptr)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			TArray<AActor*> FoundActors;

			FString GroundTag = "PlayerGround";

			UGameplayStatics::GetAllActorsWithTag(world, FName(*GroundTag), FoundActors);

			if (FoundActors.Num() > 0)
			{
				myGround = Cast<APlayerGround>(FoundActors[0]);
			}
		}
	}

	myGround->GoGround();

	FVector curLocation = GetCapsuleComponent()->GetComponentLocation();
	curLocation.X = curLocation.X + 10.0f;
	GetCapsuleComponent()->SetWorldLocation(curLocation);

	FVector curPosition = MyGameInstance->GetPlayerPosition("Player");
	curPosition.X = curPosition.X + 10.0f;

	MyGameInstance->SetPlayerPosition("Player", curPosition);
}

void AMyCharacter::PositionBack()
{
	if (PlayerStage != 8)
	{
		return;
	}

	if (myGround == nullptr)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			TArray<AActor*> FoundActors;

			FString GroundTag = "PlayerGround";

			UGameplayStatics::GetAllActorsWithTag(world, FName(*GroundTag), FoundActors);

			if (FoundActors.Num() > 0)
			{
				myGround = Cast<APlayerGround>(FoundActors[0]);
			}
		}
	}

	myGround->BackGround();

	FVector curLocation = GetCapsuleComponent()->GetComponentLocation();
	curLocation.X = curLocation.X - 10.0f;
	GetCapsuleComponent()->SetWorldLocation(curLocation);

	FVector curPosition = MyGameInstance->GetPlayerPosition("Player");
	curPosition.X = curPosition.X + 10.0f;

	MyGameInstance->SetPlayerPosition("Player", curPosition);
}

void AMyCharacter::PositionLeft()
{
	if (PlayerStage != 8)
	{
		return;
	}

	if (myGround == nullptr)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			TArray<AActor*> FoundActors;

			FString GroundTag = "PlayerGround";

			UGameplayStatics::GetAllActorsWithTag(world, FName(*GroundTag), FoundActors);

			if (FoundActors.Num() > 0)
			{
				myGround = Cast<APlayerGround>(FoundActors[0]);
			}
		}
	}

	myGround->LeftGround();

	FVector curLocation = GetCapsuleComponent()->GetComponentLocation();
	curLocation.Y = curLocation.Y - 10.0f;
	GetCapsuleComponent()->SetWorldLocation(curLocation);

	FVector curPosition = MyGameInstance->GetPlayerPosition("Player");
	curPosition.Y = curPosition.Y - 10.0f;

	MyGameInstance->SetPlayerPosition("Player", curPosition);
}

void AMyCharacter::PositionRight()
{
	if (PlayerStage != 8)
	{
		return;
	}

	if (myGround == nullptr)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			TArray<AActor*> FoundActors;

			FString GroundTag = "PlayerGround";

			UGameplayStatics::GetAllActorsWithTag(world, FName(*GroundTag), FoundActors);

			if (FoundActors.Num() > 0)
			{
				myGround = Cast<APlayerGround>(FoundActors[0]);
			}
		}
	}

	myGround->RightGround();

	FVector curLocation = GetCapsuleComponent()->GetComponentLocation();
	curLocation.Y = curLocation.Y + 10.0f;
	GetCapsuleComponent()->SetWorldLocation(curLocation);

	FVector curPosition = MyGameInstance->GetPlayerPosition("Player");
	curPosition.Y = curPosition.Y + 10.0f;

	MyGameInstance->SetPlayerPosition("Player", curPosition);
}