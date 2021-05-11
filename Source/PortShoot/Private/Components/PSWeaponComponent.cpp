


#include "Components/PSWeaponComponent.h"
#include "Weapon/PSBaseWeapon.h"
#include "GameFramework/Character.h"

UPSWeaponComponent::UPSWeaponComponent()
{

	PrimaryComponentTick.bCanEverTick = false;


}




void UPSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    
	SpawnWeapon();
	
}


void UPSWeaponComponent::SpawnWeapon()
{
    if (!GetWorld()) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;
    
    CurrentWeapon = GetWorld()->SpawnActor<APSBaseWeapon>(WeaponClass);
    if (!CurrentWeapon) return;
    
    
        
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,false) ;
    CurrentWeapon->AttachToComponent(Character->GetMesh(),AttachmentRules, WeaponAttachPointName);
    CurrentWeapon->SetOwner(Character);
}

void UPSWeaponComponent::Fire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->Fire();
}