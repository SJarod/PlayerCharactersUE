// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERFRAMEWORK_API ACharacterController : public APlayerController
{
	GENERATED_BODY()

private:

public:
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate = 45.f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	TSubclassOf<ACharacter> DefaultCharacterToSpawn;

	UFUNCTION(BlueprintCallable)
	void SpawnCharacter();
	
};
