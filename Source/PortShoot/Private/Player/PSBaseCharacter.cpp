


#include "Player/PSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/Size/ParticleModuleSizeBase.h"
#include "Components/PSCharacterMovementComponent.h"
#include "Components/PSHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Weapon/PSBaseWeapon.h"
DEFINE_LOG_CATEGORY_STATIC(BaseCharLog, All, All);

// Sets default values
APSBaseCharacter::APSBaseCharacter(const FObjectInitializer& ObjInit):Super(ObjInit.SetDefaultSubobjectClass<UPSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f,80.f);

    
    CameraComponent=CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UPSHealthComponent>("HealthComponent");

    HealthTextComponent=CreateDefaultSubobject<UTextRenderComponent>("HealthRenderComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
    HealthTextComponent->SetOwnerNoSee(true);
    
}

// Called when the game starts or when spawned
void APSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());
    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &APSBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &APSBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &APSBaseCharacter::OnGroundLanded);

    SpawnWeapon();
}

// Called every frame
void APSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

   
   
    
}

// Called to bind functionality to input
void APSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APSBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APSBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &APSBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &APSBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &APSBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run",IE_Pressed, this, &APSBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run",IE_Released, this, &APSBaseCharacter::OnStopRunning);
}

bool APSBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float APSBaseCharacter::GetMovementDirection() const
{
    if(GetVelocity().IsZero()) return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct=FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees:Degrees * FMath::Sign(CrossProduct.Z);
}

void APSBaseCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount>0.0f;
    if(Amount==0.0f) return;
    AddMovementInput(GetActorForwardVector(),Amount);
    
}

void APSBaseCharacter::MoveRight(float Amount)
{
    if(Amount==0.0f) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void APSBaseCharacter::OnStartRunning()
{
   WantsToRun = true;
}

void APSBaseCharacter::OnStopRunning()
{
    WantsToRun = false;
}




void APSBaseCharacter::OnDeath()
{
    UE_LOG(BaseCharLog, Display, TEXT("Player %s is dead"), *GetName());
    PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(5.0f);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void APSBaseCharacter::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void APSBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;
    UE_LOG(BaseCharLog, Display, TEXT("Fall Velocity %f"), FallVelocityZ)

    if(FallVelocityZ<LandedDamageVelocity.X) return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity,
        LandedDamage, FallVelocityZ);
    UE_LOG(BaseCharLog, Display, TEXT("Final damage %f"), FinalDamage)
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void APSBaseCharacter::SpawnWeapon()
{
    if (!GetWorld()) return;
    const auto Weapon = GetWorld()->SpawnActor<APSBaseWeapon>(WeaponClass);
    if (Weapon)
    {
        FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,false) ;
        Weapon->AttachToComponent(GetMesh(),AttachmentRules, "WeaponSocket");
    }
}

