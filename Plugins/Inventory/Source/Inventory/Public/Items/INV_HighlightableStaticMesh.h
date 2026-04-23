#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Interaction/INV_Highlightable.h"
#include "INV_HighlightableStaticMesh.generated.h"

UCLASS()
class INVENTORY_API UINV_HighlightableStaticMesh : public UStaticMeshComponent, public IINV_Highlightable
{
	GENERATED_BODY()

public:
	virtual void Highlight() override;
	virtual void Unhighlight() override;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UMaterialInterface> HighlightMaterial = nullptr;
};
