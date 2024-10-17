// Copyright by MykeUhu

#include "Character/UhuCharacterBase.h"

AUhuCharacterBase::AUhuCharacterBase()
{
    // Set default movement settings
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character rotates towards movement direction
    bUseControllerRotationYaw = false; // Disable controller rotation
}

void AUhuCharacterBase::BeginPlay()
{
    Super::BeginPlay(); // Aufruf der Basisklasse
   
}

void AUhuCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // Setup input bindings here (e.g., movement, camera control)
}
