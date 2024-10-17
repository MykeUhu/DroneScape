// Copyright by MykeUhu

#include "Character/UhuCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AUhuCharacter::AUhuCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
    
	SpringArm->TargetArmLength = 350.0f; // Set to approximately 3.5 meters
	SpringArm->bUsePawnControlRotation = false; // SpringArm NOT follows controller rotation

	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f)); // Offset for better visibility
	SpringArm->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f)); // Tilt for a better angle

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // Camera does not follow controller rotation
}

void AUhuCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Initial setup if needed
}

void AUhuCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Setup input bindings here (e.g., movement, camera control)
}
