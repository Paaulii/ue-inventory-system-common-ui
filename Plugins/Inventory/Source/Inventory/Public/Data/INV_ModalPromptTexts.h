// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "INV_ModalPromptTexts.generated.h"

enum class FINV_ItemActionType : uint8;

UCLASS(Blueprintable)
class INVENTORY_API UINV_ModalPromptTexts : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FINV_ItemActionType, FText> Prompts;
};
