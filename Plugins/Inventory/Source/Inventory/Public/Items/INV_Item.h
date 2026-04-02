// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/Types/INV_ItemSaveDataTypes.h"
#include "GameFramework/Actor.h"
#include "Interaction/INV_Highlightable.h"
#include "StructUtils/InstancedStruct.h"
#include "INV_Item.generated.h"

struct FINV_ItemAssetDefinition;
class UINV_InventoryDataAsset;
class URotatingMovementComponent;
class UINV_HighlightableStaticMesh;

UCLASS(Abstract)
class INVENTORY_API AINV_Item : public AActor, public IINV_Highlightable
{
	GENERATED_BODY()

public:
	AINV_Item();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Highlight_Implementation() override;
	virtual void UnHighlight_Implementation() override;
	virtual void ChangeMesh(const FINV_ItemAssetDefinition*  ItemAssetDefinition) PURE_VIRTUAL(AINVItem::ChangeMesh, );;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	void PickUp();
	FINV_ItemData& GetItemDefinition() { return ItemData; };
	void Initialize(const FINV_ItemData& Data);
protected:
	UPROPERTY(EditInstanceOnly, Category= "Inventory")
	FINV_ItemData ItemData;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory" )
	TObjectPtr<UINV_InventoryDataAsset> InventoryDataAsset;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UMaterialInterface> HighlightMaterial;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMeshComponent> MeshComponent;
private:
	void Setup();
	void SetupMesh();
	
	UPROPERTY()
	TObjectPtr<URotatingMovementComponent> RotatingComponent;
};
