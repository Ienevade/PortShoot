

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PSWeaponComponent.generated.h"

class APSBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTSHOOT_API UPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UPSWeaponComponent();

    void Fire();
protected:
    UPROPERTY(EditDefaultsOnly,  Category="Weapon")
    TSubclassOf<APSBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly,  Category="Weapon")
    FName WeaponAttachPointName = "WeaponSocket";
    
	virtual void BeginPlay() override;
private:
    UPROPERTY()
    APSBaseWeapon* CurrentWeapon = nullptr;
    void SpawnWeapon();
};