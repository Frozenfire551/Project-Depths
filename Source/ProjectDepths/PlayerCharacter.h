// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "PlayerCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
UCLASS()

class PROJECTDEPTHS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCameraComponent* Carema;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		TObjectPtr<UInputAction> IA_Move;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		TObjectPtr<UInputAction> IA_CameraMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		TObjectPtr<UInputAction> IA_Jump;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		TObjectPtr<UInputAction> IA_Crouch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		TObjectPtr<UInputAction> IA_Interact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		TObjectPtr<UInputAction> IA_EquipmentWheel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void move(const FInputActionValue& _Value);
	void look(const FInputActionValue& _Value);
	void jump();
	void couch();
	void intact();
	void changeItem();
};
