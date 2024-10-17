// Copyright by MykeUhu


#include "Controller/UhuPlayerControllerBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Character/UhuCharacter.h"
#include "Drone/UhuDrone.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AUhuPlayerControllerBase::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    UE_LOG(LogTemp, Warning, TEXT("SetupInputComponent aufgerufen"));

    // Binde die Eingabeaktionen
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(Ia_MoveForward, ETriggerEvent::Triggered, this, &AUhuPlayerControllerBase::MoveForward);
        EnhancedInputComponent->BindAction(Ia_MoveRight, ETriggerEvent::Triggered, this, &AUhuPlayerControllerBase::MoveRight);
        EnhancedInputComponent->BindAction(Ia_MoveUp, ETriggerEvent::Triggered, this, &AUhuPlayerControllerBase::MoveUp);
        EnhancedInputComponent->BindAction(Ia_Jump, ETriggerEvent::Triggered, this, &AUhuPlayerControllerBase::Jump);
        EnhancedInputComponent->BindAction(Ia_ToggleUIAndCamera, ETriggerEvent::Started, this, &AUhuPlayerControllerBase::ToggleUIAndCamera);
    }

    // Input Mapping Context hinzufügen
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(InputMappingContext, 0);
        UE_LOG(LogTemp, Warning, TEXT("Input Mapping Context hinzugefügt"));
    }

    // Initialisiere die Charaktere
    PlayerCharacter = Cast<APawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AUhuCharacter::StaticClass()));
    DroneCharacter = Cast<APawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AUhuDrone::StaticClass()));
    CurrentCharacter = PlayerCharacter;

    // Besitze den ersten Charakter
    Possess(CurrentCharacter);

    // Initialisiere die UI-Widgets
    if (PlayerUIClass)
    {
        PlayerUIWidget = CreateWidget<UUserWidget>(this, PlayerUIClass);
        if (PlayerUIWidget)
        {
            PlayerUIWidget->AddToViewport();
            UE_LOG(LogTemp, Warning, TEXT("Player UI hinzugefügt"));
        }
    }

    if (DroneUIClass)
    {
        DroneUIWidget = CreateWidget<UUserWidget>(this, DroneUIClass);
    }

    bIsDroneUIActive = false;
}

void AUhuPlayerControllerBase::ToggleUIAndCamera()
{
    UE_LOG(LogTemp, Warning, TEXT("ToggleUIAndCamera aufgerufen"));

    if (bIsDroneUIActive)
    {
        // Wechsel zurück zum Spieler
        if (PlayerUIWidget)
        {
            PlayerUIWidget->AddToViewport();
            UE_LOG(LogTemp, Warning, TEXT("Player UI hinzugefügt"));
        }
        if (DroneUIWidget)
        {
            DroneUIWidget->RemoveFromParent();
            UE_LOG(LogTemp, Warning, TEXT("Drone UI entfernt"));
        }
        Possess(PlayerCharacter);
        CurrentCharacter = PlayerCharacter;  // Hier sicherstellen, dass CurrentCharacter gesetzt wird
        UE_LOG(LogTemp, Warning, TEXT("Besitze PlayerCharacter"));

        // Überprüfe die Besitznahme
        if (GetPawn() == PlayerCharacter)
        {
            UE_LOG(LogTemp, Warning, TEXT("Besitznahme von PlayerCharacter erfolgreich"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Besitznahme von PlayerCharacter fehlgeschlagen"));
        }

        // Aktiviere die Spieler-Kamera
        APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
        if (PC && PlayerCharacter)
        {
            PC->SetViewTargetWithBlend(PlayerCharacter, 0.5f);
            UE_LOG(LogTemp, Warning, TEXT("Spieler-Kamera aktiviert"));
        }
    }
    else
    {
        // Wechsel zur Drohne
        if (DroneUIWidget)
        {
            DroneUIWidget->AddToViewport();
            UE_LOG(LogTemp, Warning, TEXT("Drone UI hinzugefügt"));
        }
        if (PlayerUIWidget)
        {
            PlayerUIWidget->RemoveFromParent();
            UE_LOG(LogTemp, Warning, TEXT("Player UI entfernt"));
        }
        Possess(DroneCharacter);
        CurrentCharacter = DroneCharacter;  // Hier sicherstellen, dass CurrentCharacter gesetzt wird
        UE_LOG(LogTemp, Warning, TEXT("Besitze DroneCharacter"));

        // Überprüfe die Besitznahme
        if (GetPawn() == DroneCharacter)
        {
            UE_LOG(LogTemp, Warning, TEXT("Besitznahme von DroneCharacter erfolgreich"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Besitznahme von DroneCharacter fehlgeschlagen"));
        }

        // Aktiviere die Drohnen-Kamera
        APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
        if (PC && DroneCharacter)
        {
            PC->SetViewTargetWithBlend(DroneCharacter, 0.5f);
            UE_LOG(LogTemp, Warning, TEXT("Drohnen-Kamera aktiviert"));
        }
    }

    bIsDroneUIActive = !bIsDroneUIActive;
    UE_LOG(LogTemp, Warning, TEXT("bIsDroneUIActive: %s"), bIsDroneUIActive ? TEXT("true") : TEXT("false"));
}

void AUhuPlayerControllerBase::MoveForward(const FInputActionValue& InputActionValue)
{
    float Value = InputActionValue.Get<float>();
    if (CurrentCharacter && Value != 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveForward for %s"), *CurrentCharacter->GetName());

        const FRotator Rotation = CurrentCharacter->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        CurrentCharacter->AddMovementInput(Direction, Value);
        UE_LOG(LogTemp, Warning, TEXT("Bewegung hinzugefügt für: %s"), *CurrentCharacter->GetName());
    }
}

void AUhuPlayerControllerBase::MoveRight(const FInputActionValue& InputActionValue)
{
    float Value = InputActionValue.Get<float>();
    if (CurrentCharacter && Value != 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveRight for %s"), *CurrentCharacter->GetName());

        const FRotator Rotation = CurrentCharacter->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        CurrentCharacter->AddMovementInput(Direction, Value);
        UE_LOG(LogTemp, Warning, TEXT("Bewegung hinzugefügt für: %s"), *CurrentCharacter->GetName());
    }
}

void AUhuPlayerControllerBase::MoveUp(const FInputActionValue& InputActionValue)
{
    float Value = InputActionValue.Get<float>();
    if (DroneCharacter && Value != 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveUp for %s"), *DroneCharacter->GetName());

        const FVector Direction = FVector::UpVector;
        DroneCharacter->AddMovementInput(Direction, Value);
        UE_LOG(LogTemp, Warning, TEXT("Bewegung hinzugefügt für: %s"), *DroneCharacter->GetName());
    }
}

void AUhuPlayerControllerBase::Jump()
{
    if (PlayerCharacter)
    {
        if (AUhuCharacterBase* LocalCharacter = Cast<AUhuCharacterBase>(PlayerCharacter))
        {
            LocalCharacter->Jump();
            UE_LOG(LogTemp, Warning, TEXT("Jump executed for: %s"), *LocalCharacter->GetName());
        }
    }
}

void AUhuPlayerControllerBase::SwitchCharacter()
{
    UE_LOG(LogTemp, Warning, TEXT("SwitchCharacter aufgerufen"));

    if (CurrentCharacter == PlayerCharacter)
    {
        CurrentCharacter = DroneCharacter;
    }
    else
    {
        CurrentCharacter = PlayerCharacter;
    }

    Possess(CurrentCharacter);
    if (GetPawn() == CurrentCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("Possess erfolgreich"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Possess fehlgeschlagen"));
    }
}