

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
    float Damage = 10.0f;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USkeletalMeshComponent* WeaponMesh;
	virtual void BeginPlay() override;


    void MakeDamage(const FHitResult& HitResult);
    void MakeShot();
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    UFUNCTION(BlueprintCallable)
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
};
