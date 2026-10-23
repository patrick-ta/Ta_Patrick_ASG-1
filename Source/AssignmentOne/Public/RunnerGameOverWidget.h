#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RunnerGameOverWidget.generated.h"

class UTextBlock;
class UButton;

/**
 * UMG Widget class displayed when the player hits an obstacle and the game ends.
 */
UCLASS(Blueprintable)
class ASSIGNMENTONE_API URunnerGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// Sets up the game over screen with the final score
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Over")
	void SetupGameOver(int32 FinalScore);
	virtual void SetupGameOver_Implementation(int32 FinalScore);

	// Restarts the current level
	UFUNCTION(BlueprintCallable, Category = "Game Over")
	void OnRestartClicked();

	// Final number of obstacles passed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Over")
	int32 FinalObstacleCount = 0;

protected:
	// Optional text block bound to display the final score
	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly, Category = "Game Over")
	TObjectPtr<UTextBlock> FinalScoreText;

	// Optional button bound to reload the level
	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly, Category = "Game Over")
	TObjectPtr<UButton> RestartButton;
};
