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
}

UMaterialInstanceDynamic* UTransitionManager::GetMaterialFade()
{
	if (m_MaterialInterfaceFade)
	{
		m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterfaceFade, this);
	}

	return m_MaterialInstanceDynamic;
}

UMaterialInstanceDynamic* UTransitionManager::GetMaterialAngle()
{
	if (m_MaterialInterfaceAngle)
	{
		m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterfaceAngle, this);
	}

	return m_MaterialInstanceDynamic;
}

UMaterialInstanceDynamic* UTransitionManager::GetMaterialRadial()
{
	if (m_MaterialInterfaceRadial)
	{
		m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterfaceRadial, this);
	}

	return m_MaterialInstanceDynamic;
}

UMaterialInstanceDynamic* UTransitionManager::GetMaterialLinear()
{
	if (m_MaterialInterfaceLinear)
	{
		m_MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(m_MaterialInterfaceLinear, this);
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
	m_MaterialInstanceDynamic->SetScalarParameterValue("AlphaParam", m_TransitionProgress);

	UE_LOG(LogTemp, Warning, TEXT("Pregress = %f"), m_TransitionProgress)
}