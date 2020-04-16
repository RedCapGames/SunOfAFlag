// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SunOfAFlagCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SAFFlag.h"
#include "SAFGameMode.h"
#include "SAFPlayerState.h"

ASunOfAFlagCharacter::ASunOfAFlagCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASunOfAFlagCharacter::OnOverlapBegin);
}

void ASunOfAFlagCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ASAFFlag* flag = dynamic_cast<ASAFFlag*>(OtherActor);
		if(flag != nullptr)
		{
			if (GetWorld()->GetAuthGameMode<ASAFGameMode>()->TryPickFlag(this))
				AttachToFlag(flag);
			return;
		}
		// Turn off the light  
	}
	ASunOfAFlagCharacter* other = dynamic_cast<ASunOfAFlagCharacter*>(OtherActor);
	auto state = GetPlayerState();
	if(other != nullptr && state != nullptr && GetPlayerState<ASAFPlayerState>()->IsPlayerHasFlag())
	{
		//TakeDamage(1, FDamageEvent(), other->GetController(), other);
		DetachFromFlag();
		GetWorld()->GetAuthGameMode<ASAFGameMode>()->ReleaseFlag(this);
		GetWorld()->DestroyActor(this);
		
		//GetController().pos
	}
}

void ASunOfAFlagCharacter::AttachToFlag(ASAFFlag* flag)
{
	flag->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	GetPlayerState<ASAFPlayerState>()->GetFlag();
	_flag = flag;
}

void ASunOfAFlagCharacter::DetachFromFlag()
{
	_flag->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	_flag = nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASunOfAFlagCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASunOfAFlagCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ASunOfAFlagCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ASunOfAFlagCharacter::TouchStopped);
}

void ASunOfAFlagCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ASunOfAFlagCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ASunOfAFlagCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

