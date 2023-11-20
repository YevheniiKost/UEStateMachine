#pragma once

#include "CoreMinimal.h"

#include "StateBase.generated.h"

class UStateManagerComponent;

UCLASS(Blueprintable)
class CUSTOMSTATEMACHINE_API UStateBase : public UObject
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
    bool bCanTick = false;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
    bool bCanRepeat = false;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
    FName StateDisplayName;

public:
	virtual void OnEnterState(AActor* Owner);
	virtual void TickState();
	virtual void OnExitState();
	void SetStateManager(UStateManagerComponent* StateManager);

protected:
	UPROPERTY()
	UStateManagerComponent* StateManagerComponent;
};
