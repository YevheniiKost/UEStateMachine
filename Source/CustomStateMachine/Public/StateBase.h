#pragma once

#include "CoreMinimal.h"

#include "StateBase.generated.h"

class UStateManagerComponent;

/** 
 * Base class for all states.
 *  - CanTick: If true, TickState will be called every frame.
 *  - CanRepeat: If true, the state can be switched to itself.
 *  - StateDisplayName: The name of the state. Use this name to switch to this state.
 */
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
