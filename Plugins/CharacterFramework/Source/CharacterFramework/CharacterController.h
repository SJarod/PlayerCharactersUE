// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

class UInputMappingContext;
class UInputAction;


/**
 * 
 */
UCLASS()
class CHARACTERFRAMEWORK_API ACharacterController : public APlayerController
{
	GENERATED_BODY()

private:

public:

	// Legacy technique
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate = 45.f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate = 45.f;

// #if ENGINE_MAJOR_VERSION == 4

// #elif ENGINE_MAJOR_VERSION == 5

	// enhanced input

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
// #endif

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	TSubclassOf<ACharacter> DefaultCharacterToSpawn;

	UFUNCTION(BlueprintCallable)
	void SpawnCharacter();
	
};
