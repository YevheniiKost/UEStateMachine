# UE State Machine Plugin 

The UE State Machine Plugin is a tool for managing state transitions and behaviors in Unreal Engine. It includes two main components: StateBase and StateManagerComponent.  

## Overview
### StateBase
Properties

**bool bCanTick** Determines whether the state can tick. If set to true, the TickState method will be called every frame.

**bool bCanRepeat** Determines whether the state can be repeated. If set to true, the state can be re-entered after it has been exited.

**FName StateDisplayName** Holds the display name of the state. Useful for debugging and logging purposes.

### StateManagerComponent Class
StateManagerComponent is a component that manages the states in a state machine.  

**void SwitchStateByKey(FString Key)** Switches to the state with the given key. Use StateDisplayName as key

**UStateBase GetCurrentState()** Returns a pointer to the current state in the state machine.


## Usage
To use the UE State Machine Plugin, you need to create a subclass of StateBase and override the OnEnterState, TickState, and OnExitState methods as needed. You can also set the bCanTick and bCanRepeat properties to control the behavior of the state. The StateDisplayName property can be set to a meaningful name for debugging and logging purposes.  The StateManagerComponent can be added to any AActor object. You can add states to the state machine using the AddState method and set the current state using the SetCurrentState method. The GetCurrentState method can be used to retrieve the current state.
