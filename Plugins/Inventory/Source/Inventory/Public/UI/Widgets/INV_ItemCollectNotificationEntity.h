#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MVVM/UIS_MVVMUserWidget.h"
#include "INV_ItemCollectNotificationEntity.generated.h"

class UINV_RarityMarker;
class UDynamicEntryBox;
enum class EINV_ItemRarity : uint8;
class UCommonTextBlock;
class UMVVMView;
class UINV_ItemViewModel;

UCLASS()
class INVENTORY_API UINV_ItemCollectNotificationEntity : public UUserWidget
{
	GENERATED_BODY()
	
public:
	DECLARE_DELEGATE(FINV_HideDelegate)
	FINV_HideDelegate OnHide;
	
	virtual void NativeOnInitialized() override;
	void SetViewModel(UINV_ItemViewModel* ItemVM);
	void Show();
	void Hide();
	UINV_ItemViewModel* GetViewModel() const { return CachedItemVM; }
	
protected:
	UFUNCTION(BlueprintCallable)
	void VM_DisplayRarity(EINV_ItemRarity Rarity);
	
	UFUNCTION(BlueprintCallable)
	void VM_ItemQuantityChanged(int32 Quantity);

private:
	UFUNCTION()
	void NotifyAnimationFinished();
	
	void PopulateRarityMarkers();
	
	UPROPERTY(EditDefaultsOnly, Category = "Display")
	FText MultipleItemsHeaderText;
	
	UPROPERTY(EditDefaultsOnly, Category = "Display")
	FText SingleItemHeaderText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> RarityMarkersDynamicEntryBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> HeaderText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> QuantityText;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> ShowAnimation;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> HideAnimation;

	UPROPERTY()
	TObjectPtr<UMVVMView> MVVMView;

	UPROPERTY()
	TArray<UINV_RarityMarker*> RarityMarkers;

	UPROPERTY()
	TObjectPtr<UINV_ItemViewModel> CachedItemVM;
	
	FWidgetAnimationDynamicEvent AnimationFinishedEvent;
};
