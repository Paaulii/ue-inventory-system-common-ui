#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "IS_StatProgressBarWidget.generated.h"

class UImage;
class UProgressBar;

UCLASS()
class INVENTORYSYSTEM_API UIS_StatProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

private:
	UFUNCTION(BlueprintCallable)
	void VM_SetProgressBarFillAmount(float FillValue);

	UPROPERTY(EditAnywhere)
	FLinearColor FillColor = {};

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> Icon = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> StatIconImage = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar = nullptr;
};
