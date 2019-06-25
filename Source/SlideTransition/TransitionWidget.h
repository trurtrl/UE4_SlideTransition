// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "Image.h"
//#include "Runtime/Engine/Classes/Materials/MaterialInterface.h"
//#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Button.h"
#include "TransitionManager.h"
#include "Engine/StaticMeshActor.h"
#include "TransitionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SLIDETRANSITION_API UTransitionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//void SetImage(UTexture* Texture);

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* m_ButtonFade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item) 
	TAssetPtr<UTexture> m_SlideFirst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TAssetPtr<UTexture> m_SlideSecond;

private:

	UFUNCTION()
	void ButtonFadeClicked();

	UPROPERTY()
	UTransitionManager* m_TransitionManager;

	UPROPERTY()
	AStaticMeshActor* m_Plane;
};
