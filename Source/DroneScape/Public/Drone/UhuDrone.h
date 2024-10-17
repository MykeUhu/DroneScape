// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Character/UhuCharacterBase.h"
#include "UhuDrone.generated.h"

UCLASS()
class DRONESCAPE_API AUhuDrone : public AUhuCharacterBase
{
	GENERATED_BODY()
public:
	AUhuDrone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Type")
	bool bIsDrone = true;
};
