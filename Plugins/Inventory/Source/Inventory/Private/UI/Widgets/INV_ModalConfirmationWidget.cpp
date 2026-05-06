#include "UI/Widgets/INV_ModalConfirmationWidget.h"
#include "CommonTextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/ViewModels/INV_ItemActionViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "View/MVVMView.h"

void UINV_ModalConfirmationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (QuantitySlider)
	{
		QuantitySlider->OnValueChanged.AddDynamic(this, &ThisClass::OnSliderValueChanged);
		QuantitySlider->OnMouseCaptureBegin.AddDynamic(this, &ThisClass::UINV_ModalConfirmationWidget::SnapSliderToValue);
		QuantitySlider->SetValue(0);
	}
}

void UINV_ModalConfirmationWidget::CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager)
{
	UINV_SelectionViewModel* SelectionVM = UIManager.GetViewModel<UINV_SelectionViewModel>();
	checkf(SelectionVM, TEXT("UIManager cannot find SelectionViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("SelectionViewModel"), SelectionVM);
	CachedSelectionVM = SelectionVM;

	UINV_ItemActionViewModel* ItemActionVM = UIManager.GetViewModel<UINV_ItemActionViewModel>();
	checkf(ItemActionVM, TEXT("UIManager cannot find ItemActionViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("ItemActionViewModel"), ItemActionVM);
	CachedItemActionVM = ItemActionVM;
}

void UINV_ModalConfirmationWidget::OnConfirmAction()
{
	if (const UINV_ItemViewModel* ItemViewModel = CachedSelectionVM->GetSelectedItem())
	{
		int32 QuantityValue = IsSingleItemDisplayed() ? MinValue : QuantitySlider->GetValue();
		CachedItemActionVM->DelegatePerformAction(*ItemViewModel, QuantityValue);
	}
}

void UINV_ModalConfirmationWidget::OnSliderValueChanged(float Value)
{
	SnapSliderToValue();
	QuantityText->SetText(FText::FromString(FString::FromInt(QuantitySlider->GetValue())));
}

void UINV_ModalConfirmationWidget::SnapSliderToValue()
{
	int32 Value = QuantitySlider->GetValue();
	QuantitySlider->SetValue(Value);
}

bool UINV_ModalConfirmationWidget::IsSingleItemDisplayed() const
{
	return SliderParent->GetVisibility() == ESlateVisibility::Collapsed;
}

void UINV_ModalConfirmationWidget::VM_SetupSlider(const int32 ItemQuantity)
{
	if (IsSingleItemDisplayed())
	{
		return;
	}
	
	LeftSliderValueText->SetText(FText::FromString(FString::FromInt(MinValue)));
	RightSliderValueText->SetText(FText::FromString(FString::FromInt(ItemQuantity)));
	QuantitySlider->SetMinValue(MinValue);
	QuantitySlider->SetMaxValue(ItemQuantity);
	QuantitySlider->SetValue(MinValue);
	MaxValue = ItemQuantity;
}

void UINV_ModalConfirmationWidget::VM_ToggleQuantityDisplayInfo(bool bState)
{
	ESlateVisibility CurrentVisibility = bState? ESlateVisibility::Collapsed : ESlateVisibility::Visible;
	QuantityText->SetVisibility(CurrentVisibility);
	SliderParent->SetVisibility(CurrentVisibility);
}

void UINV_ModalConfirmationWidget::VM_OnItemImageChanged(UTexture2D* ItemImage)
{
	ImageIcon->SetBrushFromTexture(ItemImage);
}

