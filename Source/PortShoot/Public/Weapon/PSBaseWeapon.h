

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSBaseWeapon.generated.h"


class USkeletalMeshComponent;

UCLASS()
class PORTSHOOT_API APSBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APSBaseWeapon();
    virtual void Fire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    float TraceMaxDistance = 1500.0f;

    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USkeletalMeshComponent* WeaponMesh;
	virtual void BeginPlay() override;


    void MakeShot();

};
