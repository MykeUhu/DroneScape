// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Character/UhuCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "UhuDrone.generated.h"

UCLASS()
class DRONESCAPE_API AUhuDrone : public AUhuCharacterBase
{
	GENERATED_BODY()

public:
	AUhuDrone();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
};
