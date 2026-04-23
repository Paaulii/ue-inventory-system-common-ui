#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "INV_PlayerAttributeWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class INVENTORY_API UINV_PlayerAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	void VM_SetAttributeValue(const FText& Value);
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> StatIcon = nullptr;
	
	UPROPERTY(EditAnywhere)
	FText StatName = {};
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> StatIconImage = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StatNameText = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StatValueText = nullptr;
};
