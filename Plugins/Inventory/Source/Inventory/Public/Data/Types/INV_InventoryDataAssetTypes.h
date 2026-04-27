#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "INV_ItemEquipType.h"
#include "INV_ItemRarity.h"
#include "INV_InventoryDataAssetTypes.generated.h"

class UGameplayEffect;
enum class EINV_ItemEquipType : uint8;

USTRUCT(BlueprintType)
struct FINV_ItemDetailsData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag CategoryTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> SmallImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> LargeImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EINV_ItemRarity Rarity = EINV_ItemRarity::Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrencyValue = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredLevel = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxQuantity = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsConsumable = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEquippable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIsEquippable", EditConditionHides))
	EINV_ItemEquipType EquipType = EINV_ItemEquipType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIsEquippable", EditConditionHides))
	FName SocketAttachPoint = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDroppable = true;
};

USTRUCT(BlueprintType)
struct FINV_ItemAssetDefinition
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FINV_ItemDetailsData ItemDetails;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="StaticMesh == nullptr", EditConditionHides))
	TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="SkeletalMesh == nullptr", EditConditionHides))
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterial> Material = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> Effects = {};
};

USTRUCT(BlueprintType)
struct FINV_CategoryDefinitionData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag CategoryTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CategoryName = {};
};
