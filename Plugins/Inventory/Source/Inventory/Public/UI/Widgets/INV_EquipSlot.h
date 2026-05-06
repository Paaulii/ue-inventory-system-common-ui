#pragma once
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Data/Types/INV_ItemEquipType.h"
#include "INV_EquipSlot.generated.h"

class UImage;
class UINV_ItemViewModel;
enum class EINV_ItemEquipType : uint8;

UCLASS()
class INVENTORY_API UINV_EquipSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void VM_EquippedItemsChanged(const TArray<UINV_ItemViewModel*>& EquippedItems);

	UFUNCTION(BlueprintCallable)
	void SetEquipSlotImage(const UINV_ItemViewModel* ItemVM);

	const EINV_ItemEquipType& GetEquipType() const { return EquipType;};
protected:
	UPROPERTY(EditInstanceOnly, Category = "SlotProperties")
	EINV_ItemEquipType EquipType = EINV_ItemEquipType::None;
	
	UPROPERTY(EditInstanceOnly, Category = "SlotProperties")
	UTexture2D* EmptySlotImage = nullptr;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ImageSlot = nullptr;
};
