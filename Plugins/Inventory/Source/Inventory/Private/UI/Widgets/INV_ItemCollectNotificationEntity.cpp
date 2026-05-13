#include "UI/Widgets/INV_ItemCollectNotificationEntity.h"
#include "CommonTextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "Components/DynamicEntryBox.h"
#include "UI/Widgets/INV_RarityMarker.h"
#include "UI/ViewModels/INV_ItemViewModel.h"
#include "View/MVVMView.h"

void UINV_ItemCollectNotificationEntity::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PopulateRarityMarkers();
	MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass()));
}

void UINV_ItemCollectNotificationEntity::SetViewModel(UINV_ItemViewModel* ItemVM)
{
	if (MVVMView)
	{
		CachedItemVM = ItemVM;
		MVVMView->SetViewModel(FName("ItemViewModel"), ItemVM);
	}
}

void UINV_ItemCollectNotificationEntity::Show()
{
	PlayAnimationForward(ShowAnimation);
}

void UINV_ItemCollectNotificationEntity::Hide()
{
	AnimationFinishedEvent.BindDynamic(this, &UINV_ItemCollectNotificationEntity::NotifyAnimationFinished);
	BindToAnimationFinished(HideAnimation, AnimationFinishedEvent);
	PlayAnimationForward(HideAnimation);
}

void UINV_ItemCollectNotificationEntity::PopulateRarityMarkers()
{
	int32 RarityTypeAmount = StaticEnum<EINV_ItemRarity>()->NumEnums() - 1;
	
	for (int32 i = 0; i < RarityTypeAmount; i++)
	{
		UINV_RarityMarker* RarityMarker = Cast<UINV_RarityMarker>(RarityMarkersDynamicEntryBox->CreateEntry());
		RarityMarkers.Add(RarityMarker);
	}
}

void UINV_ItemCollectNotificationEntity::VM_ItemQuantityChanged(int32 Quantity)
{
	QuantityText->SetText(FText::FromString(FString::Printf(TEXT("x %d"), Quantity)));
	HeaderText->SetText(Quantity > 1 ? MultipleItemsHeaderText : SingleItemHeaderText);
}

void UINV_ItemCollectNotificationEntity::NotifyAnimationFinished()
{
	UnbindFromAnimationFinished(ShowAnimation, AnimationFinishedEvent);
	OnHide.ExecuteIfBound();
}

void UINV_ItemCollectNotificationEntity::VM_DisplayRarity(EINV_ItemRarity Rarity)
{
	int32 ActiveMarkersCount = static_cast<int32>(Rarity);

	for (int32 i = 0; i < RarityMarkers.Num(); i++)
	{
		bool bShouldBeActive = i <= ActiveMarkersCount;
		RarityMarkers[i]->SetActiveState(bShouldBeActive);
	}
}


