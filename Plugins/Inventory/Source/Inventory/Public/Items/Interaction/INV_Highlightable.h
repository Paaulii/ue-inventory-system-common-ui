#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "INV_Highlightable.generated.h"

UINTERFACE(MinimalAPI)
class UINV_Highlightable : public UInterface
{
	GENERATED_BODY()
};

class INVENTORY_API IINV_Highlightable
{
	GENERATED_BODY()
	
public:
	virtual void Highlight() = 0;
	virtual void Unhighlight() = 0;
};
