// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCharacterLegacy.h"

#include "Camera/CameraComponent.h"
#include "CharacterFramework/CharacterController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "GameFramework/SpringArmComponent.h"

ACharacterController* AThirdPersonCharacterLegacy::GetCharacterController() const
{
	ACharacterController* c = Cast<ACharacterController>(Controller);
	if (!c)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is not a ACharacterController"), Controller);
		return nullptr;
	}
	return c;
}

void AThirdPersonCharacterLegacy::TurnAtRate(float Rate)
{
	if (!CharacterController)
	return;
	
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * CharacterController->BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonCharacterLegacy::LookUpAtRate(float Rate)
{
	if (!CharacterController)
	return;
	
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * CharacterController->BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonCharacterLegacy::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AThirdPersonCharacterLegacy::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AThirdPersonCharacterLegacy::Jump()
{
	Super::Jump();
}

void AThirdPersonCharacterLegacy::StopJumping()
{
	Super::StopJumping();
}

// Sets default values
AThirdPersonCharacterLegacy::AThirdPersonCharacterLegacy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void AThirdPersonCharacterLegacy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AThirdPersonCharacterLegacy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	CharacterController = GetCharacterController();
}

// Called every frame
void AThirdPersonCharacterLegacy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThirdPersonCharacterLegacy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AThirdPersonCharacterLegacy::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AThirdPersonCharacterLegacy::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonCharacterLegacy::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonCharacterLegacy::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThirdPersonCharacterLegacy::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThirdPersonCharacterLegacy::LookUpAtRate);
}

