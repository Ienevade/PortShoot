

#pragma once

#include "CoreMinimal.h"

#include "PSBaseWeapon.h"
#include "PSHealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "PSBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPSHealthComponent;
class UTextRenderComponent;
class APSBaseWeapon;
UCLASS()
class PORTSHOOT_API APSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
    APSBaseCharacter(const FObjectInitializer& ObjInit);
	// Sets default values for this character's properties
	

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UPSHealthComponent* HealthComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UTextRenderComponent* HealthTextComponent;

    UPROPERTY(EditDefaultsOnly,  Category="Animation")
    UAnimMontage* DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly,  Category="Movement")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

    UPROPERTY(EditDefaultsOnly,  Category="Movement")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

    UPROPERTY(EditDefaultsOnly,  Category="Weapon")
    TSubclassOf<APSBaseWeapon> WeaponClass;
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category= "Movement")
    bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category= "Movement")
    float GetMovementDirection() const;
    
private:
    bool WantsToRun = false;
    bool IsMovingForward = false;
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnStartRunning();
    void OnStopRunning();
    void OnDeath();
    void OnHealthChanged(float);


    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);

    void SpawnWeapon();
};