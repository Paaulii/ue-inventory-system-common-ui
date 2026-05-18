#pragma once

#include "CoreMinimal.h"
#include "UIS_UIManagerSubsystem.h"
#include "UIS_MVVMUIManagerSubsystem.generated.h"

class AUIS_PlayerController;
class UINV_InventoryViewModel;
class UINV_SelectionViewModel;
class UMVVMViewModelBase;
class UUIS_ViewModelBase;

UCLASS(Blueprintable)
class UISYSTEM_API UUIS_MVVMUIManagerSubsystem : public UUIS_UIManagerSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
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
	virtual void NotifyPlayerAdded(UUIS_LocalPlayer* LocalPlayer) override;
	
private:
	UFUNCTION()
	void OnPawnPossessed(APawn* OldPawn, APawn* NewPawn);
	
	void InitializeViewModels();
	void DeinitializeViewModels();
	
	UPROPERTY(EditDefaultsOnly, Category = "ViewModel")
	TArray<TSubclassOf<UUIS_ViewModelBase>> ViewModelsToSpawn = {};
	
	UPROPERTY()
	TArray<TObjectPtr<UUIS_ViewModelBase>> ViewModels = {};
};