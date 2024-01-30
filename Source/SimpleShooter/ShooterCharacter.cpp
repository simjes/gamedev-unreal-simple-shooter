// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void AShooterCharacter::MoveForward(const FInputActionValue& Value)
{
	const float Direction = Value.Get<float>();
	AddMovementInput(GetActorForwardVector() * Direction);
}

void AShooterCharacter::MoveRight(const FInputActionValue& Value)
{
	const float Direction = Value.Get<float>();
	AddMovementInput(GetActorRightVector() * Direction);
}

void AShooterCharacter::Look(const FInputActionValue& Value)
{
	const FVector2d Input = Value.Get<FVector2d>();
	AddControllerYawInput(Input.X * RotationRate);
	// How to best handle inverted look 🤔? Create a separate mapping context?
	AddControllerPitchInput(-Input.Y * RotationRate);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(
			MoveForwardAction, ETriggerEvent::Triggered, this, &AShooterCharacter::MoveForward
		);
		EnhancedInputComponent->BindAction(
			MoveRightAction, ETriggerEvent::Triggered, this, &AShooterCharacter::MoveRight
		);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Jump);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Look);
	}
}
