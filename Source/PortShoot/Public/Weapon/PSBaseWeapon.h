

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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USkeletalMeshComponent* WeaponMesh;
	virtual void BeginPlay() override;



};
