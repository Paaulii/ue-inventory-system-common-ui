#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "INV_RarityMarker.generated.h"

class UImage;

UCLASS()
class INVENTORY_API UINV_RarityMarker : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetActiveState(bool bState) const;
	
private:
	UPROPERTY(EditDefaultsOnly)
	FColor DisabledTintColor;

	UPROPERTY(EditDefaultsOnly)
	FColor ActiveTintColor;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> MarkerImage;
};
