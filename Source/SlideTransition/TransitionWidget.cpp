// Fill out your copyright notice in the Description page of Project Settings.


#include "TransitionWidget.h"
#include "Materials/Material.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


//void UTransitionWidget::SetImage(UTexture* Texture)
//{
//	UMaterialInterface* materialInterface = Cast<UMaterialInterface>(m_MaterialTransition.Get());
//
//	float someFloat = 1.85f;
//
//	m_MID = UMaterialInstanceDynamic::Create(materialInterface, this);
//
//	m_MID->SetScalarParameterValue("MyFloatParameter", someFloat);
//	m_MID->SetVectorParameterValue("Color", FLinearColor::Green);
//	m_MID->SetTextureParameterValue("MyTexture", Texture);
//
//	//	TODO set dynamic material to image
//}



void UTransitionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_TransitionManager = NewObject<UTransitionManager>(this);

	//for (TActorIterator<AStaticMeshActor> actorItr(GetWorld()); actorItr; ++actorItr)
	//{
	//	m_Plane = *actorItr;
	//}

	TArray<AActor*> planeArray;
	UGameplayStatics::GetAllActorsWithTag(this, "TransitionPlane", planeArray);
	for (AActor* plane : planeArray)
	{
		m_Plane = Cast<AStaticMeshActor>(plane);
	}


	if (m_ButtonFade && !m_ButtonFade->OnClicked.IsBound())
	{
		m_ButtonFade->OnClicked.AddDynamic(this, &UTransitionWidget::ButtonFadeClicked);
	}
	if (m_ButtonAngle && !m_ButtonAngle->OnClicked.IsBound())
	{
		m_ButtonAngle->OnClicked.AddDynamic(this, &UTransitionWidget::ButtonAngleClicked);
	}
	if (m_ButtonRadial && !m_ButtonRadial->OnClicked.IsBound())
	{
		m_ButtonRadial->OnClicked.AddDynamic(this, &UTransitionWidget::ButtonRadialClicked);
	}
	if (m_ButtonLinear && !m_ButtonLinear->OnClicked.IsBound())
	{
		m_ButtonLinear->OnClicked.AddDynamic(this, &UTransitionWidget::ButtonLinearClicked);
	}
	if (m_ButtonWideStripes && !m_ButtonWideStripes->OnClicked.IsBound())
	{
		m_ButtonWideStripes->OnClicked.AddDynamic(this, &UTransitionWidget::ButtonWideStripesClicked);
	}

	m_First = m_SlideFirst.LoadSynchronous();
	m_Second = m_SlideSecond.LoadSynchronous();
}

void UTransitionWidget::ButtonFadeClicked()
{
	if (m_TransitionManager)
	{
		UMaterialInstanceDynamic* materialInstanceDynamic = m_TransitionManager->GetMaterial(ETransitionMaterial::Fade);

		InitAndStartTransition(materialInstanceDynamic);
	}
}

void UTransitionWidget::ButtonAngleClicked()
{
	if (m_TransitionManager)
	{
		UMaterialInstanceDynamic* materialInstanceDynamic = m_TransitionManager->GetMaterial(ETransitionMaterial::Angle);

		InitAndStartTransition(materialInstanceDynamic);
	}
}

void UTransitionWidget::ButtonRadialClicked()
{
	if (m_TransitionManager)
	{
		UMaterialInstanceDynamic* materialInstanceDynamic = m_TransitionManager->GetMaterial(ETransitionMaterial::Radial);

		InitAndStartTransition(materialInstanceDynamic);
	}
}

void UTransitionWidget::ButtonLinearClicked()
{
	if (m_TransitionManager)
	{
		UMaterialInstanceDynamic* materialInstanceDynamic = m_TransitionManager->GetMaterial(ETransitionMaterial::Linear);

		InitAndStartTransition(materialInstanceDynamic);
	}
}

void UTransitionWidget::ButtonWideStripesClicked()
{
	if (m_TransitionManager)
	{
		UMaterialInstanceDynamic* materialInstanceDynamic = m_TransitionManager->GetMaterial(ETransitionMaterial::WideStripes);

		InitAndStartTransition(materialInstanceDynamic);
	}
}

void UTransitionWidget::InitAndStartTransition(UMaterialInstanceDynamic* MaterialInstanceDynamic)
{
	if (m_Plane && m_First && m_Second)
	{
		m_TransitionManager->InitTransition(m_First, m_Second, 1.5);
		m_Plane->GetStaticMeshComponent()->SetMaterial(0, MaterialInstanceDynamic);
		m_TransitionManager->StartTransition();

		Swap(m_First, m_Second);
	}
}