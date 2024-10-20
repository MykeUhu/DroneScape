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

// Define custom log category for better filtering
DEFINE_LOG_CATEGORY_STATIC(LogUhuController, Log, All);


void AUhuPlayerControllerBase::BeginPlay()
{
    Super::BeginPlay();

    bIsControllingDrone = false; // Start with character control
}

AUhuPlayerControllerBase::AUhuPlayerControllerBase()
    : InputMappingContext(nullptr)      // Input Mapping Context für die Eingaben
    , Ia_MoveForward(nullptr)           // Input Action für Vorwärtsbewegung
    , Ia_MoveRight(nullptr)             // Input Action für Rechtsbewegung
    , Ia_MoveUp(nullptr)                // Input Action für Aufwärtsbewegung
    , Ia_Jump(nullptr)                  // Input Action für Springen
    , Ia_ToggleUIAndCamera(nullptr)     // Input Action zum Wechseln zwischen UI und Kamera
    , PlayerUIWidget(nullptr)           // Widget für die Spieler-UI
    , DroneUIWidget(nullptr)            // Widget für die Drohnen-UI
    , bIsDroneUIActive(false)           // Status, ob die Drohnen-UI aktiv ist
{
    // Weitere Initialisierungen können hier durchgeführt werden, falls nötig
}

void AUhuPlayerControllerBase::SwitchControl()
{
    UE_LOG(LogUhuController, Log, TEXT("SwitchControl called"));
    // Implementiere hier deine Logik zum Wechseln der Steuerung
}

void AUhuPlayerControllerBase::SetupInputComponent()
{
    Super::SetupInputComponent();

    UE_LOG(LogUhuController, Log, TEXT("SetupInputComponent called"));

    // Bind input actions only if EnhancedInputComponent is valid
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(Ia_MoveForward, ETriggerEvent::Triggered, this, &AUhuPlayerControllerBase::MoveForward);
        EnhancedInputComponent->BindAction(Ia_MoveRight, ETriggerEvent::Triggered, this, &AUhuPlayerControllerBase::MoveRight);
        EnhancedInputComponent->BindAction(Ia_MoveUp, ETriggerEvent::Triggered, this, &AUhuPlayerControllerBase::MoveUp);
        EnhancedInputComponent->BindAction(Ia_Jump, ETriggerEvent::Triggered, this, &AUhuPlayerControllerBase::Jump);
        EnhancedInputComponent->BindAction(Ia_ToggleUIAndCamera, ETriggerEvent::Started, this, &AUhuPlayerControllerBase::ToggleUIAndCamera);
    }

    // Adding the Input Mapping Context
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(InputMappingContext, 0);
        UE_LOG(LogUhuController, Log, TEXT("Input Mapping Context added"));
    }

    // Initialize the Player and Drone characters safely
    PlayerCharacter = Cast<APawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AUhuCharacter::StaticClass()));
    DroneCharacter = Cast<APawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AUhuDrone::StaticClass()));
    CurrentCharacter = PlayerCharacter;

    // Possess the player character initially
    if (CurrentCharacter.IsValid())
    {
        Possess(CurrentCharacter.Get());
        UE_LOG(LogUhuController, Log, TEXT("Possessed initial character: %s"), *CurrentCharacter->GetName());
    }
    else
    {
        UE_LOG(LogUhuController, Warning, TEXT("CurrentCharacter is invalid, cannot possess."));
    }

    // Initialize the UI Widgets
    if (PlayerUIClass)
    {
        PlayerUIWidget = CreateWidget<UUserWidget>(this, PlayerUIClass);
        if (PlayerUIWidget.IsValid())  // .IsValid() verwenden, um sicherzustellen, dass der Weak Pointer gültig ist
        {
            PlayerUIWidget->AddToViewport();
            UE_LOG(LogUhuController, Log, TEXT("Player UI added"));
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
    UE_LOG(LogUhuController, Log, TEXT("ToggleUIAndCamera called"));

    // Check if switching back to Player character
    if (bIsDroneUIActive)
    {
        SwitchToCharacter(PlayerCharacter.Get(), PlayerUIWidget.Get(), DroneUIWidget.Get(), TEXT("PlayerCharacter"));
    }
    else
    {
        SwitchToCharacter(DroneCharacter.Get(), DroneUIWidget.Get(), PlayerUIWidget.Get(), TEXT("DroneCharacter"));
    }

    bIsDroneUIActive = !bIsDroneUIActive;
    UE_LOG(LogUhuController, Log, TEXT("bIsDroneUIActive: %s"), bIsDroneUIActive ? TEXT("true") : TEXT("false"));
}

// Helper function to switch between characters and handle UI changes
void AUhuPlayerControllerBase::SwitchToCharacter(APawn* NewCharacter, UUserWidget* NewWidget, UUserWidget* OldWidget, const FString& CharacterName)
{
    if (NewCharacter)
    {
        // Possess the new character
        Possess(NewCharacter);

        // Deactivate the old UI
        if (OldWidget && OldWidget->IsInViewport())
        {
            OldWidget->RemoveFromParent();  // Updated from RemoveFromViewport to RemoveFromParent
        }

        // Show the new UI
        if (NewWidget)
        {
            NewWidget->AddToViewport();
        }

        UE_LOG(LogUhuController, Log, TEXT("Switched to %s"), *CharacterName);
    }
    else
    {
        UE_LOG(LogUhuController, Warning, TEXT("NewCharacter is null!"));
    }
}

// Movement functions
void AUhuPlayerControllerBase::MoveForward(const FInputActionValue& InputActionValue)
{
    HandleMovement(InputActionValue, EAxis::X, TEXT("MoveForward"));
}

void AUhuPlayerControllerBase::MoveRight(const FInputActionValue& InputActionValue)
{
    HandleMovement(InputActionValue, EAxis::Y, TEXT("MoveRight"));
}

// TODO: Drone can move up and down before first switch to drone and back
void AUhuPlayerControllerBase::MoveUp(const FInputActionValue& InputActionValue)
{
    if (const float Value = InputActionValue.Get<float>(); DroneCharacter.IsValid() && Value != 0.0f)
    {
        // Add vertical movement based on Up/Down input
        const FVector UpDirection = FVector::UpVector;
        DroneCharacter->AddMovementInput(UpDirection, Value);

        UE_LOG(LogUhuController, Log, TEXT("MoveUp for %s"), *DroneCharacter->GetName());
    }
}

void AUhuPlayerControllerBase::HandleMovement(const FInputActionValue& InputActionValue, EAxis::Type Axis, const FString& ActionName)
{
    // Ensure we have a valid pawn to control
    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn) return; // Exit if no pawn is controlled

    FVector Direction;

    // Determine the direction based on the axis
    switch (Axis)
    {
    case EAxis::X: // Forward / Backward
        Direction = ControlledPawn->GetActorForwardVector();
        break;
    case EAxis::Y: // Right / Left
        Direction = ControlledPawn->GetActorRightVector();
        break;
    case EAxis::Z: // Up / Down
        Direction = FVector::UpVector; // Up direction for Z-axis input
        break;
    default:
        UE_LOG(LogUhuController, Warning, TEXT("Unhandled axis type: %s"), *ActionName);
        return; // Early return if the axis is not handled
    }

    // Execute the movement
    if (const float Value = InputActionValue.Get<float>(); Value != 0.0f)
    {
        // Calculate new movement and execute it
        const FVector Movement = Direction * Value;
        ControlledPawn->AddMovementInput(Movement);
        UE_LOG(LogUhuController, Log, TEXT("Move %s for %s"), *ActionName, *ControlledPawn->GetName());
    }
}

void AUhuPlayerControllerBase::Jump()
{
    if (PlayerCharacter.IsValid())
    {
        if (AUhuCharacter* LocalCharacter = Cast<AUhuCharacter>(PlayerCharacter.Get()))
        {
            LocalCharacter->Jump();
            UE_LOG(LogUhuController, Log, TEXT("Jump executed for: %s"), *LocalCharacter->GetName());
        }
        else
        {
            UE_LOG(LogUhuController, Warning, TEXT("Failed to cast PlayerCharacter to AUhuCharacter."));
        }
    }
    else
    {
        UE_LOG(LogUhuController, Warning, TEXT("PlayerCharacter is invalid, cannot jump."));
    }
}
