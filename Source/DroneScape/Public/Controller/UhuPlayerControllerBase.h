// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "UhuPlayerControllerBase.generated.h"

// Forward declarations
class AUhuCharacter;
class AUhuDrone;

// Player Controller for the Uhu game
UCLASS()
class DRONESCAPE_API AUhuPlayerControllerBase : public APlayerController
{
    GENERATED_BODY()

public:
    AUhuPlayerControllerBase();

    // Call this function to switch control between character and drone
    UFUNCTION(BlueprintCallable, Category = "Control")
    void SwitchControl();
    
    // Setup input component to bind actions
    virtual void SetupInputComponent() override;

protected:
    // Input actions
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* Ia_MoveForward;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* Ia_MoveRight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* Ia_MoveUp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* Ia_Jump;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* Ia_ToggleUIAndCamera;

    // UI classes
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> PlayerUIClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> DroneUIClass;

    // Character references
    TWeakObjectPtr<APawn> PlayerCharacter;
    TWeakObjectPtr<APawn> DroneCharacter;
    TWeakObjectPtr<APawn> CurrentCharacter;

    // UI widgets
    UUserWidget* PlayerUIWidget;
    UUserWidget* DroneUIWidget;

    // State
    bool bIsDroneUIActive;

    // Toggle UI and camera
    void ToggleUIAndCamera();

    // Switch between characters
    void SwitchCharacter();

    // Movement functions
    void MoveForward(const FInputActionValue& InputActionValue);
    void MoveRight(const FInputActionValue& InputActionValue);
    void MoveUp(const FInputActionValue& InputActionValue);
    void Jump();

    // Helper functions
    void SwitchToCharacter(APawn* NewCharacter, UUserWidget* NewWidget, UUserWidget* OldWidget, const FString& CharacterName);
    void HandleMovement(const FInputActionValue& InputActionValue, EAxis::Type Axis, const FString& ActionName);

private:
    UPROPERTY(BlueprintReadOnly, Category = "Control", meta = (AllowPrivateAccess = "true"))
    bool bIsControllingDrone; // true if controlling the drone, false if controlling the character
};
