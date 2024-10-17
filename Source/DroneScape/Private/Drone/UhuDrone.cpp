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

void AUhuDrone::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsAutopilotActive && AirshipActor)
    {
        // Berechne die Landeposition auf Grundlage des Airship-Zentrums und des ZOffsets
        FVector AirshipLocation = AirshipActor->GetActorLocation();
        LandingTargetPosition = FVector(AirshipLocation.X, AirshipLocation.Y, AirshipLocation.Z + LandingPointZOffset);

        // Bewege die Drohne zur LandingTargetPosition
        FVector CurrentPosition = GetActorLocation();
        FVector Direction = (LandingTargetPosition - CurrentPosition).GetSafeNormal();
        FVector NewPosition = CurrentPosition + (Direction * AutopilotSpeed * DeltaTime);
        SetActorLocation(NewPosition);

        // Überprüfe, ob die Drohne innerhalb des LandingRadius ist
        if (FVector::Dist(CurrentPosition, LandingTargetPosition) < LandingRadius)
        {
            // Drohne hat das Ziel erreicht
            bIsAutopilotActive = false;
            UE_LOG(LogTemp, Warning, TEXT("Drone has landed successfully!"));
        }
    }
}

void AUhuDrone::ToggleAutopilot()
{
    bIsAutopilotActive = !bIsAutopilotActive;
    UE_LOG(LogTemp, Warning, TEXT("AirshipActor: %s"), *AirshipActor->GetName());
    UE_LOG(LogTemp, Warning, TEXT("Autopilot %s"), bIsAutopilotActive ? TEXT("activated") : TEXT("deactivated"));
}

void AUhuDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // Setup input bindings here (e.g., movement, camera control)
}
