// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Character/UhuCharacterBase.h"
#include "UhuCharacter.generated.h"

UCLASS()
class DRONESCAPE_API AUhuCharacter : public AUhuCharacterBase
{
	GENERATED_BODY()
public:
	AUhuCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Type")
	bool bIsCharacter = true;
};
