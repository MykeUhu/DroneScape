// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h" // Füge dies hinzu
#include "UhuPlayerControllerBase.generated.h"

UCLASS()
class DRONESCAPE_API AUhuPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	void MoveForward(const FInputActionValue& InputActionValue);
	void MoveRight(const FInputActionValue& InputActionValue);
	void MoveUp(const FInputActionValue& InputActionValue);
	void Jump();

	void SwitchCharacter();
	void ToggleUIAndCamera();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* Ia_MoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* Ia_MoveRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* Ia_MoveUp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Input")
	UInputAction* Ia_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Input")
	UInputAction* Ia_ToggleUIAndCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> DroneUIClass;

private:
	APawn* PlayerCharacter;
	APawn* DroneCharacter;
	APawn* CurrentCharacter;

	UPROPERTY()
	UUserWidget* PlayerUIWidget;

	UPROPERTY()
	UUserWidget* DroneUIWidget;

	bool bIsDroneUIActive;
};
