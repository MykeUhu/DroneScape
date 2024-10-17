// Copyright by MykeUhu

#include "Drone/UhuDrone.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AUhuDrone::AUhuDrone()
{
    
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);

    SpringArm->TargetArmLength = 500.0f; // Set to approximately 5 meters
    SpringArm->bUsePawnControlRotation = false;
    
    // Create and attach Camera component for drone view
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
    Camera->bUsePawnControlRotation = false;
    
    // Set default movement settings
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character rotates towards movement direction
    bUseControllerRotationYaw = false; // Disable controller rotation
}

void AUhuDrone::BeginPlay()
{
    Super::BeginPlay();
    // Initial setup if needed
}

void AUhuDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // Setup input bindings here (e.g., movement, camera control)
}