// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "UIS_ViewModelBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UISYSTEM_API UUIS_ViewModelBase : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	virtual void Initialize()
	{
		UE_LOG(LogTemp, Warning, TEXT("INITIALIZE VIEW MODEL"));
	};
	virtual void Deinitialize(){};
};
