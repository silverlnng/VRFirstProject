// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class VRFIRSTPROJECT_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	UPROPERTY(EditAnywhere, Category="Controller")
	class UMotionControllerComponent* leftController;
	
	UPROPERTY(EditAnywhere, Category="Controller")
	class UMotionControllerComponent* rightController;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PlayerMappingContext;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USceneComponent* VROrigin;
	
protected:
	UPROPERTY(EditAnywhere,Category="Input")
	class UInputAction* IA_LeftThumbstick;
	UPROPERTY(EditAnywhere,Category="Input")
	class UInputAction* IA_RightThumbstick_X;
	UPROPERTY(EditAnywhere,Category="Input")
	class UInputAction* IA_LeftTrigger;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_LeftTriggerTouch;
public:
	UFUNCTION()
	void Turn(const FInputActionValue& Value);
	UFUNCTION()
	void Func2(const FInputActionValue& Value);
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Func4(const FInputActionValue& Value);
	
private:
	FVector moveDirection;
	void Locomotion();
};
