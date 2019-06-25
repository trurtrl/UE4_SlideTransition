// Fill out your copyright notice in the Description page of Project Settings.


#include "TransitionManager.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"


UTransitionManager::UTransitionManager()
	: Super()
	, m_TransitionParam(0.f)
	, m_MaterialInstanceDynamic(nullptr)
	, m_MaterialInterface(nullptr)
	, m_Rate(0.033333f)
	, m_TransitionProgress(0.f)
{
	static ConstructorHelpers::FObjectFinder<UMaterial> materialFade(TEXT("Material'/Game/FadeMaterial.FadeMaterial'"));
	if (materialFade.Object != NULL)
	{
		m_MaterialInterface = (UMaterial*)materialFade.Object;
	}
}

UMaterialInstanceDynamic* UTransitionManager::GetMaterialFade()
{
	if (m_MaterialInterface)
	{
		m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterface, this);
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
	m_TransitionProgress = 0.f;
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.ClearTimer(m_TimerHandle);
	timerManager.SetTimer(m_TimerHandle, this, &UTransitionManager::Transit, m_Rate, true, 0.f);
}

void UTransitionManager::Transit()
{
	m_TransitionProgress += m_Rate / m_TransitionDuration;
	FMath::Clamp(m_TransitionDuration, 0.f, 1.f);
	m_MaterialInstanceDynamic->SetScalarParameterValue("AlphaParam", m_TransitionProgress);

	if (FMath::IsNearlyEqual(m_TransitionProgress, 1.f))
	{
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.ClearTimer(m_TimerHandle);
	}
}