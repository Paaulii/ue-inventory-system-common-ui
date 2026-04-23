#pragma once

#include "CoreMinimal.h"
#include "Data/Types/INV_ItemSaveDataTypes.h"
#include "GameFramework/Actor.h"
#include "Interaction/INV_Highlightable.h"
#include "INV_Item.generated.h"

class UINV_InventoryDataAsset;
class UINV_HighlightableStaticMesh;
class URotatingMovementComponent;
struct FINV_ItemAssetDefinition;

UCLASS(Abstract)
class INVENTORY_API AINV_Item : public AActor, public IINV_Highlightable
{
	GENERATED_BODY()

public:
	AINV_Item();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Highlight() override;
	virtual void Unhighlight() override;
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	void Initialize(const FINV_ItemData& Data);
	void PickUp();
	FINV_ItemData& GetItemDefinition() { return ItemData; }
	
protected:
	virtual void ChangeMesh(const FINV_ItemAssetDefinition* ItemAssetDefinition) PURE_VIRTUAL(AINVItem::ChangeMesh, );
	
	UPROPERTY(EditInstanceOnly, Category= "Inventory")
	FINV_ItemData ItemData = {};
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory" )
	TObjectPtr<UINV_InventoryDataAsset> InventoryDataAsset = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UMaterialInterface> HighlightMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMeshComponent> MeshComponent = nullptr;
	
private:
	void Setup();
	void SetupMesh();
	
	UPROPERTY()
	TObjectPtr<URotatingMovementComponent> RotatingComponent = nullptr;
};
