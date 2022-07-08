


#include "Weapon/PSBaseWeapon.h"

#include <ocidl.h>

#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"


APSBaseWeapon::APSBaseWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}


void APSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
}

void APSBaseWeapon::MakeDamage(const FHitResult& HitResult)
{
    HitResult.Actor->TakeDamage(Damage,FDamageEvent(), nullptr, this);
}


void APSBaseWeapon::MakeShot()
{
    if(!GetWorld()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;


    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);
    if(HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24,
            FColor::Red, false, 5.0f);
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false,
       3.0f, 0, 3.0f);

        
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false,
       3.0f, 0, 3.0f);
    }


    
}

void APSBaseWeapon::Fire()
{
    
    MakeShot();
}

APlayerController* APSBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}


bool APSBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if(!Controller) return false;
    
    
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

FVector APSBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool APSBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return  false;
   
    
    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection*TraceMaxDistance;
    return true;
}


void APSBaseWeapon::MakeHit (FHitResult& HitResult, const FVector& TraceStart,const FVector& TraceEnd)
{
    if (!GetWorld()) return;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,CollisionParams);

}