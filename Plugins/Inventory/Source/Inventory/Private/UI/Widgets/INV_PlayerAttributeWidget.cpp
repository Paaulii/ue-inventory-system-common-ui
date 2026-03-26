// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_PlayerAttributeWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UINV_PlayerAttributeWidget::VM_SetAttributeValue(const FText& Value)
{
	Text_StatValue->SetText(Value);
}

void UINV_PlayerAttributeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	Image_StatIcon->SetBrushFromTexture(StatIcon);
	Text_StatName->SetText(StatName);
}
