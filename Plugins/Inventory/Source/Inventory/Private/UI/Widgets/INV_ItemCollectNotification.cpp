#include "UI/Widgets/INV_ItemCollectNotification.h"
#include "Components/DynamicEntryBox.h"
#include "UI/MVVM/UIS_MVVMUIManagerSubsystem.h"
#include "UI/Widgets/INV_ItemCollectNotificationEntity.h"
#include "UI/ViewModels/INV_ItemNotificationViewModel.h"
#include "View/MVVMView.h"

void UINV_ItemCollectNotification::CacheViewModels(UUIS_MVVMUIManagerSubsystem& UIManager, UMVVMView* View)
{
	Super::CacheViewModels(UIManager, View);

	UINV_ItemNotificationViewModel* ItemNotificationVM = UIManager.GetViewModel<UINV_ItemNotificationViewModel>();
	checkf(ItemNotificationVM, TEXT("UIManager cannot find ItemNotificationViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	CachedItemNotificationVM = ItemNotificationVM;
	MVVMView->SetViewModel(FName("ItemNotificationViewModel"), ItemNotificationVM);
}

void UINV_ItemCollectNotification::VM_OnItemShow(UINV_ItemViewModel* ItemViewModel)
{
	if (ItemViewModel)
	{
		UINV_ItemCollectNotificationEntity* NotificationEntity = Cast<UINV_ItemCollectNotificationEntity>(ItemNotificationDynamicEntryBox->CreateEntry());
		ActiveNotifications.Add(NotificationEntity);
		NotificationEntity->SetViewModel(ItemViewModel);
		NotificationEntity->Show();
	}
}

void UINV_ItemCollectNotification::VM_OnItemHide(UINV_ItemViewModel* ItemViewModel)
{
	if (!ItemViewModel)
	{
		return;
	}
	
	for (const auto NotificationEntry : ActiveNotifications)
	{
		if (NotificationEntry->GetViewModel() == ItemViewModel)
		{
			NotificationEntry->OnHide.BindLambda( [NotificationEntry, ItemViewModel, this]
			{
				NotificationEntry->OnHide.Unbind();
				ItemNotificationDynamicEntryBox->RemoveEntry(NotificationEntry);
				CachedItemNotificationVM->OnItemNotificationHidden(ItemViewModel);
			});
			
			NotificationEntry->Hide();
		}
	}
}