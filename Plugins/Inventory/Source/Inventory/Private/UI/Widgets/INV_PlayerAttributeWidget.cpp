#include "UI/Widgets/INV_PlayerAttributeWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UINV_PlayerAttributeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	StatIconImage->SetBrushFromTexture(StatIcon);
	StatNameText->SetText(StatName);
}

void UINV_PlayerAttributeWidget::VM_SetAttributeValue(FText Value)
{
	StatValueText->SetText(Value);
}
