#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_InteractionViewModel.generated.h"

class UINV_ItemTracerComponent;

UCLASS()
class INVENTORY_API UINV_InteractionViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Initialize();;
	virtual void Deinitialize();;
	bool GetbIsItemHovered() const { return bIsItemHovered; }
	void SetbIsItemHovered(bool bState);
	
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	bool bIsItemHovered = false;

private:
	UPROPERTY()
	TObjectPtr<UINV_ItemTracerComponent> ItemTracerComponent = nullptr;
};
