// Paulina Hałatek All Rights Reserved
#include "UI/UIS_PrimaryGameLayout.h"

void UUIS_PrimaryGameLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (!IsDesignTime())
	{
		Layers.Add(LayerTag, LayerWidget);
	}
}

UCommonActivatableWidgetContainerBase* UUIS_PrimaryGameLayout::GetLayerWidget(FGameplayTag LayerName) const
{
	if (Layers.Num() <= 0)
	{
		return nullptr;
	}
	
	return Layers.FindRef(LayerName);
}
