


#include "Weapon/PSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

APSBaseWeapon::APSBaseWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}


void APSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}



