// // Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameUIManagerSubsystem.h"
#include "UIManagerSubsystem.generated.h"

class UInventoryViewModel;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UUIManagerSubsystem : public UGameUIManagerSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void InitializeViewModels();
	UInventoryViewModel* GetInventoryVM() {return InventoryViewModel;}
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI|Viewmodels")
	TSubclassOf<UInventoryViewModel> InventoryViewModelClass = nullptr;
private:
	UPROPERTY()
	TObjectPtr<UInventoryViewModel> InventoryViewModel = nullptr;

};
