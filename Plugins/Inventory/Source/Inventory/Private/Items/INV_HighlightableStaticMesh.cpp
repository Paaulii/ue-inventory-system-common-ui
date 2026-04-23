#include "Items/INV_HighlightableStaticMesh.h"

void UINV_HighlightableStaticMesh::Highlight()
{
	SetOverlayMaterial(HighlightMaterial);
}

void UINV_HighlightableStaticMesh::Unhighlight()
{
	SetOverlayMaterial(nullptr);
}
