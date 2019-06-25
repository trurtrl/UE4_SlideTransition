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
}

void UTransitionWidget::ButtonFadeClicked()
{
	if (m_Plane && m_TransitionManager)
	{
		UMaterialInstanceDynamic* materialInstanceDynamic = m_TransitionManager->GetMaterialFade();

		UTexture* first = m_SlideFirst.LoadSynchronous();
		UTexture* second = m_SlideSecond.LoadSynchronous();

		if (first && second)
		{
			m_TransitionManager->InitTransition(first, second, 1.5);
			m_Plane->GetStaticMeshComponent()->SetMaterial(0, materialInstanceDynamic);
			m_TransitionManager->StartTransition();
		}
	}
}
