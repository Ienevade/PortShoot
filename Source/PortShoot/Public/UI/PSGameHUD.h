

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PSGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PORTSHOOT_API APSGameHUD : public AHUD
{
	GENERATED_BODY()

public:
    
    virtual void DrawHUD() override;

private:
    void DrawCrossHair();
};
