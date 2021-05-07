

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PSHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTSHOOT_API UPSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPSHealthComponent();

    float GetHealth() const {return  Health;}

    UFUNCTION(BlueprintCallable)
    bool IsDead() const {return FMath::IsNearlyZero(Health);}

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;
protected:
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health", meta = (ClampMin = "0", ClampMax="1000.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal")
    bool AutoHeal;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta = (EditionCondition = "Autoheal"))
    float HealUpdateTime = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta = (EditionCondition = "Autoheal"))
    float HealDelay = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta = (EditionCondition = "Autoheal"))
    float HealModifier = 3.0f;


    virtual void BeginPlay() override;

private:
    float Health = 0.0f;
    FTimerHandle HealTimeHandle;
    UFUNCTION()
    void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );


    void HealUpdate();
    void SetHealth(float NewHealth);
};
