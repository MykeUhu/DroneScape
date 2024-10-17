// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Character/UhuCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UhuDrone.generated.h"

UCLASS()
class DRONESCAPE_API AUhuDrone : public AUhuCharacterBase
{
	GENERATED_BODY()

public:
	AUhuDrone();

	// Autopilot toggle function
	UFUNCTION(BlueprintCallable, Category = "Drone Control")
	void ToggleAutopilot();

	// Airship Actor reference to use for autopilot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Autopilot")
	AActor* AirshipActor;

	// Autopilot speed variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Autopilot")
	float AutopilotSpeed;

	// Autopilot landing added height
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Autopilot")
	float LandingPointZOffset;

	// Radius for successful landing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Autopilot")
	float LandingRadius;

protected:
	virtual void BeginPlay() override;

	// Variable for the autopilot mode (only visible in C++)
	bool bIsAutopilotActive;

	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	// Target position for landing
	FVector LandingTargetPosition;
};
