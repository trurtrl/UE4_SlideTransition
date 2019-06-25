// Fill out your copyright notice in the Description page of Project Settings.


#include "TransitionManager.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"


UTransitionManager::UTransitionManager()
	: Super()
	, m_TransitionParam(0.f)
	, m_MaterialInstanceDynamic(nullptr)
	, m_MaterialInterfaceFade(nullptr)
	, m_MaterialInterfaceAngle(nullptr)
	, m_MaterialInterfaceRadial(nullptr)
	, m_MaterialInterfaceLinear(nullptr)
	, m_TransitionDuration(0.f)
	, m_Rate(0.033333f)
	, m_TransitionProgress(0.f)
	, m_TransitionStart(0.f)
	, m_TransitionFinish(1.f)
{
	static ConstructorHelpers::FObjectFinder<UMaterial> materialFade(TEXT("Material'/Game/FadeMaterial.FadeMaterial'"));
	if (materialFade.Object != NULL)
	{
		m_MaterialInterfaceFade = (UMaterial*)materialFade.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> materialAngle(TEXT("Material'/Game/AngleCutoff.AngleCutoff'"));
	if (materialAngle.Object != NULL)
	{
		m_MaterialInterfaceAngle = (UMaterial*)materialAngle.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> materialRadial(TEXT("Material'/Game/RadialCutoff.RadialCutoff'"));
	if (materialRadial.Object != NULL)
	{
		m_MaterialInterfaceRadial = (UMaterial*)materialRadial.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> materialLinear(TEXT("Material'/Game/LinearCutoff.LinearCutoff'"));
	if (materialLinear.Object != NULL)
	{
		m_MaterialInterfaceLinear = (UMaterial*)materialLinear.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> materialWideStripes(TEXT("Material'/Game/WideStripesMaterial.WideStripesMaterial'"));
	if (materialWideStripes.Object != NULL)
	{
		m_MaterialInterfaceWideStripes = (UMaterial*)materialWideStripes.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> materialHorizStripes(TEXT("Material'/Game/HorizStripesMaterial.HorizStripesMaterial'"));
	if (materialHorizStripes.Object != NULL)
	{
		m_MaterialInterfaceHorizStripes = (UMaterial*)materialHorizStripes.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> materialInclineStripes(TEXT("Material'/Game/InclineStripesMaterial.InclineStripesMaterial'"));
	if (materialInclineStripes.Object != NULL)
	{
		m_MaterialInterfaceInclineStripes = (UMaterial*)materialInclineStripes.Object;
	}
}

UMaterialInstanceDynamic* UTransitionManager::GetMaterial(ETransitionMaterial Type)
{
	switch (Type)
	{
	case ETransitionMaterial::None:
		break;
	case ETransitionMaterial::Fade:
		if (m_MaterialInterfaceFade)
		{
			m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterfaceFade, this);
		}
		break;
	case ETransitionMaterial::Angle:
		if (m_MaterialInterfaceAngle)
		{
			m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterfaceAngle, this);
		}
		break;
	case ETransitionMaterial::Radial:
		if (m_MaterialInterfaceRadial)
		{
			m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterfaceRadial, this);
		}
		break;
	case ETransitionMaterial::Linear:
		if (m_MaterialInterfaceLinear)
		{
			m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterfaceLinear, this);
		}
		break;
	case ETransitionMaterial::WideStripes:
		if (m_MaterialInterfaceWideStripes)
		{
			m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterfaceWideStripes, this);
		}
		break;
	case ETransitionMaterial::HorizStripes:
		if (m_MaterialInterfaceHorizStripes)
		{
			m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterfaceHorizStripes, this);
		}
		break;
	case ETransitionMaterial::InclineStrpies:
		if (m_MaterialInterfaceInclineStripes)
		{
			m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterfaceInclineStripes, this);
		}
		break;
	default:
		break;
	}

	return m_MaterialInstanceDynamic;
}

void UTransitionManager::InitTransition(UTexture* SlideFirst, UTexture* SlideSecond, float Duration)
{
	if (m_MaterialInstanceDynamic)
	{
		m_MaterialInstanceDynamic->SetTextureParameterValue("SlideFirst", SlideFirst);
		m_MaterialInstanceDynamic->SetTextureParameterValue("SlideSecond", SlideSecond);
	}

	m_TransitionDuration = Duration;
}

void UTransitionManager::StartTransition()
{
	m_TransitionProgress = m_TransitionStart;
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.ClearTimer(m_TimerHandle);
	timerManager.SetTimer(m_TimerHandle, this, &UTransitionManager::Transit, m_Rate, true, m_TransitionStart);
}

void UTransitionManager::Transit()
{
	m_TransitionProgress += m_Rate / m_TransitionDuration;

	if (FMath::IsNegativeFloat(m_TransitionFinish - m_TransitionProgress))
	{
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.ClearTimer(m_TimerHandle);
		m_TransitionProgress = m_TransitionFinish;
	}

	if (m_MaterialInstanceDynamic)
	{
		m_MaterialInstanceDynamic->SetScalarParameterValue("AlphaParam", m_TransitionProgress);
	}

//	UE_LOG(LogTemp, Warning, TEXT("Pregress = %f"), m_TransitionProgress)
}