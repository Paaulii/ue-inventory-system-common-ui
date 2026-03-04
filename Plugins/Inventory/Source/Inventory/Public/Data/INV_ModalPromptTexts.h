// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "INV_ModalPromptTexts.generated.h"

UCLASS(Blueprintable)
class INVENTORY_API UINV_ModalPromptTexts : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FText> Prompts;
};
