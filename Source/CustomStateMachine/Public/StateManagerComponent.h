#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateBase.h"
#include "StateManagerComponent.generated.h"


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

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "State Machine")
	FString InitialState;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "State Machine")
	TMap<FString, TSubclassOf<UStateBase>> AvailableStates;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "State Machine Debug")
	bool bDebug = false;

	UPROPERTY(BlueprintReadOnly)
	TArray<UStateBase*> StateHistory;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "State Machine Debug")
	int32 StateHistoryLength;
	UPROPERTY(BlueprintReadOnly)
	UStateBase* CurrentState = nullptr;

	UPROPERTY()
	TMap<FString, UStateBase*> StateMap;


	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void SwitchStateByKey(FString Key);
	void PrintDebugMessage(const FString& Message) const;
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void SwitchState(UStateBase* NewState);
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void InitStateManager();

private:
	bool bCanTickState = false;
	void InitializeStates();
};
