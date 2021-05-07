


#include "PSGameModeBase.h"

#include "PSGameHUD.h"
#include "Player/PSBaseCharacter.h"
#include "Player/PSPlayerController.h"
#include "UI/PSGameHUD.h"

APSGameModeBase::APSGameModeBase()
{
    DefaultPawnClass=APSBaseCharacter::StaticClass();
    PlayerControllerClass = APSPlayerController::StaticClass();
    HUDClass = APSGameHUD::StaticClass();
    
}
