// Copyright by MykeUhu


#include "Character/UhuCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

AUhuCharacterBase::AUhuCharacterBase()
{
    // Setze die Charakterbewegungseinstellungen
    GetCharacterMovement()->bOrientRotationToMovement = true; // Charakter dreht sich in Bewegungsrichtung
    bUseControllerRotationYaw = false; // Deaktiviere die Steuerungsrotation

    // Erstelle SpringArm-Komponente und setze sie als Root-Komponente
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.0f; // Abstand der Kamera vom Charakter
    SpringArm->bUsePawnControlRotation = true; // SpringArm folgt der Steuerungsrotation

    // Erstelle Kamera-Komponente und setze sie als Kind von SpringArm
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false; // Kamera folgt nicht der Steuerungsrotation
}

void AUhuCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}