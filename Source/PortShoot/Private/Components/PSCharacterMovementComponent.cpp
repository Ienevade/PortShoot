


#include "Components/PSCharacterMovementComponent.h"
#include "Player/PSBaseCharacter.h"

float UPSCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const APSBaseCharacter* Player=Cast<APSBaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier: MaxSpeed;
}
