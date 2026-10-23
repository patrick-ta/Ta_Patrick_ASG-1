#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RunnerHUD.generated.h"

class URunnerHUDWidget;
class URunnerGameOverWidget;

/**
 * HUD class that tracks and displays the number of obstacles passed
 * and displays the Game Over HUD when the player hits an obstacle.
 */
UCLASS(Blueprintable)
class ASSIGNMENTONE_API ARunnerHUD : public AHUD
{
	GENERATED_BODY()

public:
	ARunnerHUD();

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	// Increments the count of obstacles passed by 1
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void IncrementObstaclesPassed();

	// Sets the obstacles passed count
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetObstaclesPassed(int32 Count);

	// Resets the count
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ResetObstaclesPassed();

	// Gets the current count of obstacles passed
	UFUNCTION(BlueprintPure, Category = "HUD")
	int32 GetObstaclesPassed() const { return ObstaclesPassed; }

	// Displays the Game Over HUD and configures input/cursor
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowGameOver();

	// Restarts the current level
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void RestartLevel();

protected:
	// Number of obstacles successfully cleared
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	int32 ObstaclesPassed = 0;

	// Indicates if the game is over
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	bool bIsGameOver = false;

	// Optional UMG Widget class to create and display in-game score
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<URunnerHUDWidget> HUDWidgetClass;

	// Active instance of the in-game score widget
	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	TObjectPtr<URunnerHUDWidget> HUDWidgetInstance;

	// Optional UMG Widget class to display when the game is over
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<URunnerGameOverWidget> GameOverWidgetClass;

	// Active instance of the Game Over widget
	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	TObjectPtr<URunnerGameOverWidget> GameOverWidgetInstance;

	// Whether to draw fallback canvas text when no UMG widget is used
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	bool bDrawCanvasHUD = true;
};
