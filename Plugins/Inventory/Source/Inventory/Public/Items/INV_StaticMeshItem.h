#pragma once

#include "CoreMinimal.h"
#include "INV_Item.h"
#include "INV_StaticMeshItem.generated.h"

UCLASS()
class INVENTORY_API AINV_StaticMeshItem : public AINV_Item
{
	GENERATED_BODY()

public:
	AINV_StaticMeshItem();

protected:
	virtual void ChangeMesh(const FINV_ItemAssetDefinition*  ItemAssetDefinition) override;
};
