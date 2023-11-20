#include "CustomStateMachine/Public/StateBase.h"

void UStateBase::OnEnterState(AActor* Owner)
{
	
}

void UStateBase::TickState()
{
	
}

void UStateBase::OnExitState()
{
	
}

void UStateBase::SetStateManager(UStateManagerComponent* StateManager)
{
	StateManagerComponent = StateManager;
}
