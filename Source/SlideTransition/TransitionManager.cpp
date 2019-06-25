// Fill out your copyright notice in the Description page of Project Settings.


#include "TransitionManager.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


UTransitionManager::UTransitionManager()
	: Super()
	, m_TransitionParam(0.f)
	, m_MaterialInstanceDynamic(nullptr)
	, m_MaterialInterface(nullptr)
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
		m_MaterialInstanceDynamic->SetScalarParameterValue("AlphaParam", 0.3);
	}
}
