// Copyright by MykeUhu


#include "Drone/UhuDroneBase.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

// Sets default values
AUhuDroneBase::AUhuDroneBase()
{
    PrimaryActorTick.bCanEverTick = true;

    DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DroneMesh"));
    RootComponent = DroneMesh;

    FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));

    EnhancedInputComponent = CreateDefaultSubobject<UEnhancedInputComponent>(TEXT("EnhancedInputComponent"));
}

void AUhuDroneBase::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void AUhuDroneBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AUhuDroneBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInput->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AUhuDroneBase::MoveForward);
        EnhancedInput->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AUhuDroneBase::MoveRight);
        EnhancedInput->BindAction(MoveUpAction, ETriggerEvent::Triggered, this, &AUhuDroneBase::MoveUp);
    }
}

void AUhuDroneBase::MoveForward(const FInputActionValue& Value)
{
    const float MovementValue = Value.Get<float>();
    if (FloatingMovement && (FloatingMovement->UpdatedComponent == RootComponent))
    {
        FloatingMovement->AddInputVector(GetActorForwardVector() * MovementValue);
    }
}

void AUhuDroneBase::MoveRight(const FInputActionValue& Value)
{
    const float MovementValue = Value.Get<float>();
    if (FloatingMovement && (FloatingMovement->UpdatedComponent == RootComponent))
    {
        FloatingMovement->AddInputVector(GetActorRightVector() * MovementValue);
    }
}

void AUhuDroneBase::MoveUp(const FInputActionValue& Value)
{
    const float MovementValue = Value.Get<float>();
    if (FloatingMovement && (FloatingMovement->UpdatedComponent == RootComponent))
    {
        FloatingMovement->AddInputVector(GetActorUpVector() * MovementValue);
    }
}