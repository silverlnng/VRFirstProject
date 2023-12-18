// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacter.h"
#include "MotionControllerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" //바인딩 하는 함수 SetupPlayerInputComponent
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(GetCapsuleComponent());
	//GetCapsuleComponent()->SetCapsuleSize(1.f,1.f);
	GetMesh()->SetupAttachment(RootComponent);
	GetArrowComponent()->SetupAttachment(RootComponent);

	
	VROrigin =CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	VROrigin->SetupAttachment(RootComponent);
	
	//GetCapsuleComponent()->SetupAttachment(RootComponent);
	
	leftController =  CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftCon"));
	leftController->MotionSource = FName("Left");
	leftController->SetupAttachment(VROrigin);
	
	rightController =  CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightCon"));
	rightController->MotionSource = FName("Right");
	rightController->SetupAttachment(VROrigin);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("HMD"));
	CameraComp->SetupAttachment(VROrigin);
}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem <UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
			//UInputMappingContext* PlayerMappingContext 를 에디터에서 할당하고 AddMappingContext으로 사용 ! 
		}
	}
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Locomotion();
}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_LeftThumbstick, ETriggerEvent::Triggered, this, &AVRCharacter::Move);
		EnhancedInputComponent->BindAction(IA_LeftTrigger, ETriggerEvent::Triggered, this, &AVRCharacter::Func2);
		EnhancedInputComponent->BindAction(IA_RightThumbstick_X, ETriggerEvent::Triggered, this, &AVRCharacter::Turn);
		EnhancedInputComponent->BindAction(IA_LeftTriggerTouch, ETriggerEvent::Triggered, this, &AVRCharacter::Func4);	
	}
}

void AVRCharacter::Move(const FInputActionValue& Value)
{
	const FVector _currentValue = Value.Get<FVector>();
	moveDirection.Y = _currentValue.X;
	moveDirection.X = _currentValue.Y;
	//AddMovementInput(moveDirection);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("LeftThumbstick"));
}
void AVRCharacter::Turn(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("rightThumbstick_X"));
}

void AVRCharacter::Func2(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("LeftTrigger"));
}


void AVRCharacter::Func4(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("LeftTriggerTouch"));
}

void AVRCharacter::Locomotion()
{
	moveDirection = FTransform(GetControlRotation()).TransformVector(moveDirection);
	AddMovementInput(moveDirection);
	moveDirection = FVector::ZeroVector;
}

