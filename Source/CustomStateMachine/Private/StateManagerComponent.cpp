#include "StateManagerComponent.h"

UStateManagerComponent::UStateManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeStates();
}

void UStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	if(!bInitialized)
	{
		PrintDebugMessage(FString::Printf(TEXT(" State Manager not initialized!")));
		return;
	}
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bCanTickState)
	{
		if (CurrentState && CurrentState->bCanTick)
		{
			CurrentState->TickState();
		}
	}
}

void UStateManagerComponent::SwitchStateByKey(FString Key)
{
	if(!bInitialized)
	{
		PrintDebugMessage(FString::Printf(TEXT(" State Manager not initialized!")));
		return;
	}
	
	if (StateMap.Contains(Key))
	{
		UStateBase* NewState = StateMap.FindRef(Key);
		SwitchState(NewState);
	}
	else
	{
		PrintDebugMessage(FString::Printf(TEXT(" Failed to switch state. State with key %s not found!"), *Key));
	}
}


void UStateManagerComponent::SwitchState(UStateBase* NewState)
{
	if(!bInitialized)
	{
		PrintDebugMessage(FString::Printf(TEXT(" State Manager not initialized!")));
		return;
	}
	
	if (NewState->IsValidLowLevel())
	{
		if (!CurrentState)
		{
			CurrentState = NewState;
		}
		else
		{
			if (CurrentState->GetClass() == NewState->GetClass() && !NewState->bCanRepeat)
			{
				PrintDebugMessage(FString::Printf(TEXT(" Failed to switch state. State already active!")));
				return;
			}

			bCanTickState = false;
			CurrentState->OnExitState();
			if (StateHistory.Num() >= StateHistoryLength)
			{
				StateHistory.RemoveAt(0);
			}
			StateHistory.Add(CurrentState);
			CurrentState = NewState;
		}

		if (CurrentState)
		{
			CurrentState->OnEnterState(GetOwner());
			bCanTickState = true;
			PrintDebugMessage(
				FString::Printf(TEXT(" Entered state: %s"), *CurrentState->StateDisplayName.ToString()));
		}
	}
	else
	{
		PrintDebugMessage(FString::Printf(TEXT(" Failed to switch state. Invalid state!")));
	}
}

void UStateManagerComponent::InitStateManager()
{
	SwitchStateByKey(InitialState);
}

void UStateManagerComponent::InitializeStates()
{
	if(!AvailableStates.Num() || bInitialized)
	{
		PrintDebugMessage(FString::Printf(TEXT(" No states available!")));
		return;
	}
	
	for (auto It = AvailableStates.CreateIterator(); It; ++It)
	{
		UStateBase* State = NewObject<UStateBase>(this, It->Value);
		State->StateDisplayName = FName(*It->Key);
		State->SetStateManager(this);
		StateMap.Add(State->StateDisplayName.ToString(), State);
		PrintDebugMessage(FString::Printf(TEXT(" Initialized state: %s"), *State->StateDisplayName.ToString()));
	}
	bInitialized = true;
}

void UStateManagerComponent::PrintDebugMessage(const FString& Message) const
{
	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Red, this->GetOwner()->GetName() + Message);
	}
}
