// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IS_StatProgressBarWidget.generated.h"

class UImage;
class UProgressBar;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UIS_StatProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void VM_SetProgressBarFillAmount(float FillValue);
protected:
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	FLinearColor FillColor;
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_StatIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;
};
