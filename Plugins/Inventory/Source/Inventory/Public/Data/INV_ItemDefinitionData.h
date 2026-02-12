#pragma once
#include "CoreMinimal.h"
#include "INV_ItemRarity.h"
#include "INV_ItemDefinitionData.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FINV_ItemDefinitionData
{
	GENERATED_BODY()
	
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
struct FSkeletalItemData : public FINV_ItemDefinitionData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayAfter = "Material"))
	USkeletalMesh* SkeletalMesh;
};

USTRUCT(BlueprintType)
struct FStaticItemData : public FINV_ItemDefinitionData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayAfter = "Material"))
	UStaticMesh* StaticMesh;
};	