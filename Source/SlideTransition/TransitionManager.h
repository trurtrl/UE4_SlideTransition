// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Engine/Texture.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Classes/Materials/MaterialInterface.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "TransitionManager.generated.h"

enum class ETransitionMaterial : uint8
{
	None,
	Fade,
	Angle,
	Radial,
	Linear,
	WideStripes,
	HorizStripes,
	InclineStrpies
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SLIDETRANSITION_API UTransitionManager : public UObject
{
	GENERATED_BODY()

public:

	UTransitionManager();
	
	UMaterialInstanceDynamic* GetMaterial(ETransitionMaterial Type);


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
	UMaterialInterface* m_MaterialInterfaceFade;

	UPROPERTY()
	UMaterialInterface* m_MaterialInterfaceAngle;

	UPROPERTY()
	UMaterialInterface* m_MaterialInterfaceRadial;

	UPROPERTY()
	UMaterialInterface* m_MaterialInterfaceLinear;

	UPROPERTY()
	UMaterialInterface* m_MaterialInterfaceWideStripes;

	UPROPERTY()
	UMaterialInterface* m_MaterialInterfaceHorizStripes;

	UPROPERTY()
	UMaterialInterface* m_MaterialInterfaceInclineStripes;

	FTimerHandle		m_TimerHandle;

	float				m_TransitionDuration;
	float				m_Rate;
	float				m_TransitionProgress;
	float				m_TransitionStart;
	float				m_TransitionFinish;

	void Transit();
};
