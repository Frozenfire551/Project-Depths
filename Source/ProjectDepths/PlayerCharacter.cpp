// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine/GameEngine.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Carema = CreateDefaultSubobject<UCameraComponent>(TEXT("Carema"));
	Carema->SetupAttachment(SpringArm);

	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerCont = Cast<APlayerController>(GetController()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("sec 1"));
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerCont->GetLocalPlayer()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("sec 2"));
			subsystem->AddMappingContext(InputMapping, 0);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("input added"));
		}

	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (TObjectPtr<UEnhancedInputComponent> enchancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enchancedInputComp->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::move);
		enchancedInputComp->BindAction(IA_CameraMove, ETriggerEvent::Triggered, this, &APlayerCharacter::look);
		enchancedInputComp->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::jump);
		enchancedInputComp->BindAction(IA_Crouch, ETriggerEvent::Started, this, &APlayerCharacter::couch);
		enchancedInputComp->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &APlayerCharacter::intact);
		enchancedInputComp->BindAction(IA_EquipmentWheel, ETriggerEvent::Triggered, this, &APlayerCharacter::changeItem);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Controller Failed"));
	}
}

void APlayerCharacter::move(const FInputActionValue& _Value)
{
	FVector2D PlayersVector = _Value.Get<FVector2D>();
	if (GetController())
	{

		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, PlayersVector.Y);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, PlayersVector.X);
		
	}
}

void APlayerCharacter::look(const FInputActionValue& _Value)
{
	FVector2D cameraVector = _Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(cameraVector.X);
		AddControllerPitchInput(cameraVector.Y);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Controller Failed %f"), cameraDirection.Y));
	}
}

void APlayerCharacter::jump()
{
	Jump();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player Press A"));
}

void APlayerCharacter::couch()
{
	if (IsCrouching == true)
	{
		UnCrouch();
		SkeletalMesh->AddRelativeLocation(FVector(0,0,-50));
		IsCrouching = false;
		
	}
	else
	{
		Crouch();
		SkeletalMesh->AddRelativeLocation(FVector(0, 0, 50));
		IsCrouching = true;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Player Press B %s"), IsCrouching ? TEXT("true") : TEXT("false")));
}

void APlayerCharacter::intact()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player Press X"));
}

void APlayerCharacter::changeItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player Press Y"));
}