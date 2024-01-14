#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateBase.h"
#include "StateManagerComponent.generated.h"

/**
 *  The State Manager Component is responsible for managing the states of an actor.
 *  It can be used to switch between states and to tick the current state.
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CUSTOMSTATEMACHINE_API UStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStateManagerComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "State Machine Debug")
	bool bDebug = false;
	
	/**
	 * Initializes the State Manager. Should be called after all states have been added.
	 */
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void InitStateManager();
	
	/**
	 * Switches to the state with the given key.
	 * @param Key The key of the state to switch to.
	 */
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void SwitchStateByKey(FString Key);
	void PrintDebugMessage(const FString& Message) const;
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void SwitchState(UStateBase* NewState);

	/**
	 * Returns the current state.
	 * @return The current state.
	 */
	UStateBase* GetCurrentState() const { return CurrentState; }

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "State Machine")
	FString InitialState;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "State Machine")
	TMap<FString, TSubclassOf<UStateBase>> AvailableStates;

	UPROPERTY(BlueprintReadOnly)
	TArray<UStateBase*> StateHistory;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "State Machine Debug")
	int32 StateHistoryLength;
	UPROPERTY(BlueprintReadOnly)
	UStateBase* CurrentState = nullptr;
	
	UPROPERTY()
	TMap<FString, UStateBase*> StateMap;

private:
	bool bInitialized;
	bool bCanTickState = false;
	void InitializeStates();
};
