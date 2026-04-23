#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIS_UIManagerSubsystem.generated.h"

class UUIS_GameUIPolicy;
class UUIS_LocalPlayer;

UCLASS(Abstract, config = UISystem)
class UISYSTEM_API UUIS_UIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void NotifyPlayerAdded(UUIS_LocalPlayer* NewPlayer);
	virtual void NotifyPlayerDestroyed(UUIS_LocalPlayer* LocalPlayer);
	const UUIS_GameUIPolicy* GetCurrentUIPolicy() const { return CurrentPolicy; }
	UUIS_GameUIPolicy* GetCurrentUIPolicy() { return CurrentPolicy; }
	
protected:
	void SwitchToPolicy(UUIS_GameUIPolicy* InPolicy);
	
private:
	UPROPERTY(Config, EditDefaultsOnly)
	TSoftClassPtr<UUIS_GameUIPolicy> DefaultUIPolicyClass = nullptr;
	
	UPROPERTY(Transient)
	TObjectPtr<UUIS_GameUIPolicy> CurrentPolicy = nullptr;
};
