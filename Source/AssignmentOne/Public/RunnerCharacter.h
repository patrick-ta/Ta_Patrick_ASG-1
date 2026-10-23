#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "RunnerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class UPaperFlipbook;

UCLASS(Blueprintable)
class ASSIGNMENTONE_API ARunnerCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	ARunnerCharacter();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PawnClientRestart() override;

	// Animation swaps happen on these events instead of every frame
	virtual void OnJumped_Implementation() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	UFUNCTION(BlueprintCallable, Category = "Runner")
	void TriggerGameOver();

	UFUNCTION(BlueprintPure, Category = "Runner")
	bool IsGameOver() const { return bIsGameOver; }

	// Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> DuckAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> GameplayContext;

	// Animation 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UPaperFlipbook> RunAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UPaperFlipbook> JumpAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UPaperFlipbook> DuckAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runner")
	bool bIsGameOver = false;

private:
	void BeginJump();
	void EndJump();
	void BeginDuck();
	void EndDuck();

	void SetAnimation(UPaperFlipbook* Animation);
};