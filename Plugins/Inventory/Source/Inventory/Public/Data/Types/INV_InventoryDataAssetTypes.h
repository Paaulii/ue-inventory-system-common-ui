#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "INV_ItemEquipType.h"
#include "INV_ItemRarity.h"
#include "StructUtils/InstancedStruct.h"
#include "INV_InventoryDataAssetTypes.generated.h"
enum class EINV_ItemEquipType : uint8;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FINV_ItemAssetDefinition
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag CategoryTag;
	
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
	int32 MaxQuantity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsConsumable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEquippable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIsEquippable", EditConditionHides))
	FName SocketAttachPoint {NAME_None};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIsEquippable", EditConditionHides))
	EINV_ItemEquipType EquipType {EINV_ItemEquipType::None};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDroppable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition= "StaticMesh == nullptr", EditConditionHides))
	USkeletalMesh* SkeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition= "SkeletalMesh == nullptr", EditConditionHides))
	UStaticMesh* StaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* Material;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> Effects;

	//TODO: Move SkeletalMesh and StaticMesh field here, add condition that if one is set then other cannot be set
};

USTRUCT(BlueprintType)
struct FINV_CategoryDefinitionData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag CategoryTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CategoryName;
};
