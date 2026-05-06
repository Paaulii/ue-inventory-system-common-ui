#include "UI/Widgets/IS_StatProgressBarWidget.h"
#include "Components/ProgressBar.h"

void UIS_StatProgressBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	ProgressBar->SetFillColorAndOpacity(FillColor);
}

void UIS_StatProgressBarWidget::VM_SetProgressBarFillAmount(float FillValue)
{
	ProgressBar->SetPercent(FillValue);
}
