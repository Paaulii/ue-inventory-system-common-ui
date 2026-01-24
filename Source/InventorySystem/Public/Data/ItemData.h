#pragma once
#include "CoreMinimal.h"
#include "ItemRarity.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	// // FInstanceStruct constructors
	//
	// FItemData(){}
	//
	// FItemData(const FItemData&) = default;
	//
	// // assignment operator -copy operations
	// FItemData& operator = (const FItemData&) = default;
	//
	// // move operator - universal reference
	// FItemData(FItemData&&) = default;
	//
	// // move assignment operator w/ universal reference
	// FItemData& operator = (FItemData&&) = default;
	// virtual ~FItemData(){}
	// //
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SmallImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* LargeImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrencyValue;

	// TODO: Move IsEquipped to a Items logic not
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// bool bIsEquipped = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredLevel;
	
	// TODO: Add fragments such as Stackable, Consumbale ( Modifiers : Mana Fragment)), Equippable

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* Material;
};

USTRUCT(BlueprintType)
struct FSkeletalItemData : public FItemData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayAfter = "Material"))
	USkeletalMesh* SkeletalMesh;
};

USTRUCT(BlueprintType)
struct FStaticItemData : public FItemData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayAfter = "Material"))
	UStaticMesh* StaticMesh;
};	