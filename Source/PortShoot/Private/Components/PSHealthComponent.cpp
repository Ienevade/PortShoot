


#include "Components/PSHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"
// Sets default values for this component's properties

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);
UPSHealthComponent::UPSHealthComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	
}



void UPSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    SetHealth(MaxHealth);
   

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UPSHealthComponent::OnTakeAnyDamageHandle);
    }
}


void UPSHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
   AActor* DamageCauser)
{
    OnHealthChanged.Broadcast(Health);
    if (Damage<=0.0f|| IsDead() || !GetWorld()) return;
    SetHealth(Health - Damage);

    
    
    if (IsDead())
    {
        OnDeath.Broadcast();
    }
   else if (AutoHeal )
   {
       GetWorld()->GetTimerManager().SetTimer(HealTimeHandle, this, &UPSHealthComponent::HealUpdate,
           HealUpdateTime, true, HealDelay);
   }
    
}

void UPSHealthComponent::HealUpdate()
{
    SetHealth(Health+  HealModifier);
    

    if(FMath::IsNearlyEqual(Health,MaxHealth&&GetWorld()))
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimeHandle);
    }
}

void UPSHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}
