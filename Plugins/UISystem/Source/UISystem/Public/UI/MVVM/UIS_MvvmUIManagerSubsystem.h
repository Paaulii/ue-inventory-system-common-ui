// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UIS_UIManagerSubsystem.h"
#include "UIS_MvvmUIManagerSubsystem.generated.h"

class UUIS_ViewModelBase;
class UMVVMViewModelBase;
class UINV_SelectionViewModel;
class UINV_InventoryViewModel;
/**
 * 
 */
UCLASS(Blueprintable)
class UISYSTEM_API UUIS_MvvmUIManagerSubsystem : public UUIS_UIManagerSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	void InitializeViewModels();
	void DeinitializeViewModels();

	template <typename T>
	T* GetViewModel()
	{
		for (const auto& ViewModel : ViewModels)
		{
			if (T* CastedViewModel = Cast<T>(ViewModel.Get()))
			{
				return CastedViewModel;
			}
		}

		return nullptr;
	}
protected:
	UPROPERTY(EditDefaultsOnly )
	TArray<TSubclassOf<UUIS_ViewModelBase>> ViewModelsToSpawn;
private:
	TArray<TObjectPtr<UUIS_ViewModelBase>> ViewModels;
};
