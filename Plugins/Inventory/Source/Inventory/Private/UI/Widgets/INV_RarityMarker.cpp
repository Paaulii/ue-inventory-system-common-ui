#include "UI/Widgets/INV_RarityMarker.h"
#include "Components/Image.h"

void UINV_RarityMarker::SetActiveState(bool bState) const
{
	MarkerImage->SetBrushTintColor(bState? ActiveTintColor: DisabledTintColor);
}
