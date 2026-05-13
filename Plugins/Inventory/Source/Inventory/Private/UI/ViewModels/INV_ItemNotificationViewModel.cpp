#include "UI/ViewModels/INV_ItemNotificationViewModel.h"
#include "UI/ViewModels/INV_ItemViewModel.h"
#include "Subsystems/ItemNotification/INV_ItemNotificationSystem.h"

void UINV_ItemNotificationViewModel::Initialize()
{
	Super::Initialize();

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			ItemNotificationSystem = LocalPlayer->GetSubsystem<UINV_ItemNotificationSystem>();
			checkf(ItemNotificationSystem, TEXT("Cannot find LocalPlayerSubsystem called UINV_ItemNotificationSystem. Check if you created BP and set it in AssetManager Project Settings."));

			if (ItemNotificationSystem)
			{
				ItemNotificationSystem->OnShowNotification.AddUObject(this, &UINV_ItemNotificationViewModel::OnShowItemNotification);
				ItemNotificationSystem->OnHideNotification.AddUObject(this, &UINV_ItemNotificationViewModel::OnHideItemNotification);
			}
		}
	}
}

void UINV_ItemNotificationViewModel::Deinitialize()
{
	if (ItemNotificationSystem)
	{
		ItemNotificationSystem->OnShowNotification.RemoveAll(this);
		ItemNotificationSystem->OnHideNotification.RemoveAll(this);
	}
	
	Super::Deinitialize();
}

void UINV_ItemNotificationViewModel::OnItemNotificationHidden(const UINV_ItemViewModel* ItemVM) const 
{
	ItemNotificationSystem->OnNotificationHidden(ItemVM->GetItemIdentification());
}

void UINV_ItemNotificationViewModel::OnShowItemNotification(const FINV_ItemDisplayData& ItemDisplayData)
{
	
	UINV_ItemViewModel* ItemVM = PopulateItemVM(ItemDisplayData);
	ActiveNotifications.Add(ItemVM);
	UE_MVVM_SET_PROPERTY_VALUE(ItemToShow, ItemVM);
}

void UINV_ItemNotificationViewModel::OnHideItemNotification(const FINV_ItemIdentification& ItemId)
{
	for (int32 i = 0; i < ActiveNotifications.Num(); i++)
	{
		if (ActiveNotifications[i]->GetItemIdentification() == ItemId)
		{
			UE_MVVM_SET_PROPERTY_VALUE(ItemToHide, ActiveNotifications[i]);
			ActiveNotifications.RemoveAt(i);
			return;
		}
	}
}

UINV_ItemViewModel* UINV_ItemNotificationViewModel::PopulateItemVM(const FINV_ItemDisplayData& ItemDisplayData)
{
	UINV_ItemViewModel* ItemVM = NewObject<UINV_ItemViewModel>(this);
	ItemVM->Initialize(ItemDisplayData, nullptr);
	return ItemVM;
}
