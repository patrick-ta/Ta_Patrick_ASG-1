#include "RunnerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

ARunnerCharacter::ARunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = false; 
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* Movement = GetCharacterMovement();

	// Lock to a 2D plane; the world scrolls, the player doesn't move sideways
	Movement->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
	Movement->SetPlaneConstraintEnabled(true);
	Movement->bSnapToPlaneAtStart = true;

	Movement->JumpZVelocity = 600.f;
	Movement->GravityScale = 2.f;
	Movement->AirControl = 0.f;

	// Duck = built-in crouch (shrinks the capsule/hitbox)
	Movement->NavAgentProps.bCanCrouch = true;
	Movement->SetCrouchedHalfHeight(20.f);

	GetCapsuleComponent()->InitCapsuleSize(20.f, 40.f);
	GetSprite()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetAnimation(RunAnimation);
}

void ARunnerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (GameplayContext) Subsystem->AddMappingContext(GameplayContext, 0);
		}
	}
}

void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* Enhanced = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!ensure(Enhanced && JumpAction && DuckAction)) return;

	Enhanced->BindAction(JumpAction, ETriggerEvent::Started, this, &ARunnerCharacter::BeginJump);
	Enhanced->BindAction(JumpAction, ETriggerEvent::Completed, this, &ARunnerCharacter::EndJump);
	Enhanced->BindAction(JumpAction, ETriggerEvent::Canceled, this, &ARunnerCharacter::EndJump);

	Enhanced->BindAction(DuckAction, ETriggerEvent::Started, this, &ARunnerCharacter::BeginDuck);
	Enhanced->BindAction(DuckAction, ETriggerEvent::Completed, this, &ARunnerCharacter::EndDuck);
	Enhanced->BindAction(DuckAction, ETriggerEvent::Canceled, this, &ARunnerCharacter::EndDuck);
}

// Input handlers 
void ARunnerCharacter::BeginJump()
{
	if (bIsGameOver) return;
	if (bIsCrouched) UnCrouch(); // stand up first
	Jump();
}

void ARunnerCharacter::EndJump()
{
	StopJumping();
}

void ARunnerCharacter::BeginDuck()
{
	if (bIsGameOver) return;
	if (!GetCharacterMovement()->IsFalling()) Crouch(); // ground only
}

void ARunnerCharacter::EndDuck()
{
	UnCrouch();
}

// Animation
void ARunnerCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	SetAnimation(JumpAnimation);
}

void ARunnerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	SetAnimation(RunAnimation);
}

void ARunnerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	SetAnimation(DuckAnimation);
}

void ARunnerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	SetAnimation(RunAnimation);
}

void ARunnerCharacter::SetAnimation(UPaperFlipbook* Animation)
{
	if (Animation && GetSprite()->GetFlipbook() != Animation)
	{
		GetSprite()->SetFlipbook(Animation);
	}
}

// Game over
void ARunnerCharacter::TriggerGameOver()
{
	if (bIsGameOver) return;
	bIsGameOver = true;

	StopJumping();
	UnCrouch();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		DisableInput(PC);
	}
}