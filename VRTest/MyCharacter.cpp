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

	PlayerStage = MyGameInstance->GetPlayerStage("Player");
	TotalMonsterKill = MyGameInstance->GetAICount(PlayerStage);
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

void AMyCharacter::SetPlayerWeapon(EPlayerWeapon myPlayerWeapon)
{
	PlayerWeapon = myPlayerWeapon;
}

EPlayerWeapon AMyCharacter::GetPlayerWeapon()
{
	return PlayerWeapon;
}

void AMyCharacter::PlayerDead()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerDead"));
	
	// 정확히 말하자면 서버에서 나간다기 보다는 아래맵으로 탈출한다는 개념이 더 정확홤
	// PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);

	UWorld* World = GetWorld();
	if (World != nullptr) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (PlayerController != nullptr) return;

	PlayerController->ConsoleCommand("quit");
}

void AMyCharacter::KillingMonster()
{
	CurrentMonsterKill++;

	if (CurrentMonsterKill == TotalMonsterKill)
	{
		FName fnMapName = FName(MyGameInstance->GetNextMapName(PlayerStage));

		MyGameInstance->SetPlayerStage("Player", PlayerStage + 1);

		UGameplayStatics::OpenLevel(GetWorld(), fnMapName);
	}
}