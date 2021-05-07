

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PSCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PORTSHOOT_API UPSCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly,  BlueprintReadWrite, Category="Movement", meta = (ClampMin = "1.5", ClampMax="10.0"))
    float RunModifier = 2.0f;
    virtual float GetMaxSpeed() const override;
};
