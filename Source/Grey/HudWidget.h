// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "HudWidget.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()



protected:
	UPROPERTY (BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image0;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image4;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image5;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image6;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image7;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image8;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image9;

public:
	void SetSlotIcon(int32 Index, UTexture2D* Icon);

};
