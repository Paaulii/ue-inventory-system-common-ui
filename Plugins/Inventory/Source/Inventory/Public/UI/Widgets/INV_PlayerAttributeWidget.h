// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "INV_PlayerAttributeWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_PlayerAttributeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void VM_SetAttributeValue(const FText& Value);
	
	UPROPERTY(EditAnywhere)
	UTexture2D* StatIcon;
	
	UPROPERTY(EditAnywhere)
	FText StatName;
	
protected:
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_StatIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_StatName;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_StatValue;
};
