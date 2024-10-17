// Copyright by MykeUhu

#include "Character/UhuCharacterBase.h"

AUhuCharacterBase::AUhuCharacterBase()
{

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
