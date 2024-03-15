// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial_UW.h"
#include "Components/TextBlock.h"
#include "MyGameInstance.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"

void UTutorial_UW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextInfo")));
	TextNext = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextNext")));
	TextPrev = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextPrev")));
}

void UTutorial_UW::NativeConstruct()
{
	Super::NativeConstruct();
	// BeginPlay ó�� Ȱ��
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	SetTutorialText(MyGameInstance->GetTutorialText(0));

	TextInfo->SetVisibility(ESlateVisibility::Visible);
	TextNext->SetVisibility(ESlateVisibility::Visible);
	TextPrev->SetVisibility(ESlateVisibility::Visible);
}

void UTutorial_UW::VisibleBackImage(bool bVisible)
{
	if (bVisible)
	{
		IsVisible = true;
		TransparencyImage(0.01, 0.0f, 1.0f);
	}

	else
	{
		IsVisible = false;
		TransparencyImage(0.01, 1.0f, 0.0f);
	}
}

void UTutorial_UW::TransparencyImage(float fSpeed, float fBegin, float fEnd)
{
	FLinearColor NewColor = FLinearColor(0.5f, 0.5f, 0.5f, LerpFun(fBegin, fEnd, fSpeed));
	SetColorAndOpacity(NewColor);
}

void UTutorial_UW::SetTutorialText(FString myText)
{
	FText myT = FText::FromString(myText);
	TextInfo->SetText(myT);
}

void UTutorial_UW::WidgetTick(float DeltaTime)
{
	if (IsFading)
	{
		// ȭ���� Ȱ��ȭ �� ��
		if (IsFadeIn)
		{
			CurrentFadeValue += DeltaTime;
		}

		// ȭ���� �� ��
		else
		{
			CurrentFadeValue += -DeltaTime;
		}

		CurrentFadeValue = FMath::Clamp(CurrentFadeValue, 0.0f, 1.0f);

		// ���̵� ��/�ƿ��� ���� ���� ������Ʈ �Լ��� ȣ���մϴ�.
		TransparencyImage(CurrentFadeValue, 0.0f, 1.0f);

		// ���̵尡 �Ϸ�Ǿ����� Ȯ���ϰ�, �ʿ��� ��� �߰� �׼��� �����մϴ�.
		if (CurrentFadeValue == 0.0f || CurrentFadeValue == 1.0f)
		{
			IsFading = false;
		}
	}
}

void UTutorial_UW::TutorialFadeIn(int nSequence)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	SetTutorialText(MyGameInstance->GetTutorialText(nSequence));
	TextInfo->SetVisibility(ESlateVisibility::Visible);

	if (nSequence == 0)
	{
		TextNext->SetVisibility(ESlateVisibility::Visible);
		TextPrev->SetVisibility(ESlateVisibility::Hidden);
	}

	else if (nSequence == DefaultSequence - 1)
	{
		TextNext->SetVisibility(ESlateVisibility::Hidden);
		TextPrev->SetVisibility(ESlateVisibility::Visible);
	}

	else 
	{
		TextNext->SetVisibility(ESlateVisibility::Visible);
		TextPrev->SetVisibility(ESlateVisibility::Visible);
	}

	IsFadeIn = true;
	IsFading = true;
}

void UTutorial_UW::TutorialFadeOut()
{
	TextInfo->SetVisibility(ESlateVisibility::Hidden);
	TextNext->SetVisibility(ESlateVisibility::Hidden);
	TextPrev->SetVisibility(ESlateVisibility::Hidden);

	IsFadeIn = false;
	IsFading = true;
}
