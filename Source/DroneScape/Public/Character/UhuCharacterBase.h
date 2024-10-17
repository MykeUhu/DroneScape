// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "UhuCharacterBase.generated.h"

UCLASS()
class DRONESCAPE_API AUhuCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AUhuCharacterBase();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
};