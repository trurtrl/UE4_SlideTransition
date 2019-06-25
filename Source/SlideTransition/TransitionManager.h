// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Engine/Texture.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Classes/Materials/MaterialInterface.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "TransitionManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SLIDETRANSITION_API UTransitionManager : public UObject
{
	GENERATED_BODY()

public:

	UTransitionManager();
	
	UMaterialInstanceDynamic* GetMaterialFade();

	void InitTransition(UTexture* SlideFirst, UTexture* SlideSecond, float Duration);

	void StartTransition();

	//UPROPERTY(EditAnywhere, meta = (DisplayName = "Material Transition Fade"))
	//TSubclassOf<UMaterialInterface> m_MaterialTransitionFade;


	UPROPERTY(EditAnywhere, meta = (DisplayName = "Transition Param"))
	float m_TransitionParam;


private:

	UPROPERTY()
	UMaterialInstanceDynamic* m_MaterialInstanceDynamic;

	UPROPERTY()
	UMaterialInterface* m_MaterialInterface;

	FTimerHandle		m_TimerHandle;

	float				m_TransitionDuration;
	float				m_Rate;
	float				m_TransitionProgress;

	void Transit();
};
