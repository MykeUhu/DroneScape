// Copyright by MykeUhu

#include "Drone/UhuDrone.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AUhuDrone::AUhuDrone()
{
	// Create and attach Camera component for drone view
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0, 0, 50)); // Position der Kamera direkt hinter der Drohne
	Camera->bUsePawnControlRotation = false; 
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
