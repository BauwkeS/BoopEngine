#include "States.h"

booble::PlayerStateMachine::PlayerStateMachine(boop::BaseState* state, boop::Component* comp)
	: StateMachine(comp, state)
{
}
