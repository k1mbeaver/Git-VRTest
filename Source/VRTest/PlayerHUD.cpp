// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "PlayerUI_UW.h"

APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UPlayerUI_UW> WB_Main(TEXT("WidgetBlueprint'/Game/Widget/PlayerUI_WB'"));
	if (WB_Main.Succeeded())
	{
		MainUIClass = WB_Main.Class;
	}
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject(); // �����ϸ� UI�� �����Ѵ�.
}

bool APlayerHUD::CheckUIObject()
{
	if (MainUIObject == nullptr) // UI�� ���ٸ� ����.
	{
		return CreateUIObject();
	}
	return true; // �ִٸ� True.
}

bool APlayerHUD::CreateUIObject()
{
	if (MainUIClass)
	{
		MainUIObject = CreateWidget<UPlayerUI_UW>(GetOwningPlayerController(), MainUIClass);
		if (MainUIObject)
		{
			MainUIObject->AddToViewport();
			return true; // ������ٸ� true.
		}
	}
	return false; // �� ������ٸ� false.
}