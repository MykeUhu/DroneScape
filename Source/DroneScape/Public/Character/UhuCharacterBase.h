// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UhuCharacterBase.generated.h"

UCLASS()
class DRONESCAPE_API AUhuCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AUhuCharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
