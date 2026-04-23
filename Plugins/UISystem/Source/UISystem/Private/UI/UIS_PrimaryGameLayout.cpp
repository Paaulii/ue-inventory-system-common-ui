#include "UI/UIS_PrimaryGameLayout.h"

void UUIS_PrimaryGameLayout::RegisterLayer(const FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (!IsDesignTime())
	{
		Layers.Add(LayerTag, LayerWidget);
	}
}

UCommonActivatableWidgetContainerBase* UUIS_PrimaryGameLayout::GetLayerWidget(const FGameplayTag& LayerName) const
{
	if (Layers.Num() <= 0)
	{
		return nullptr;
	}
	
	return Layers.FindRef(LayerName);
}
