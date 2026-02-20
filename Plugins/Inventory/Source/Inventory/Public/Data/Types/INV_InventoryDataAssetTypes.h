#pragma once

#include "CoreMinimal.h"
#include "INV_ItemRarity.h"
#include "StructUtils/InstancedStruct.h"
#include "INV_InventoryDataAssetTypes.generated.h"
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FINV_ItemAssetDefinition
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CategoryId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SmallImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* LargeImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EINV_ItemRarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrencyValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStacks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* Material;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> Effects;
};

USTRUCT(BlueprintType)
struct FSkeletalItemData : public FINV_ItemAssetDefinition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayAfter = "Material"))
	USkeletalMesh* SkeletalMesh;
};

USTRUCT(BlueprintType)
struct FStaticItemData : public FINV_ItemAssetDefinition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayAfter = "Material"))
	UStaticMesh* StaticMesh;
};

USTRUCT(BlueprintType)
struct FINV_CategoryDefinitionData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CategoryName;
};
