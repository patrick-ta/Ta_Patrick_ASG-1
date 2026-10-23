#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RunnerHUD.generated.h"

class URunnerHUDWidget;

/**
 * HUD class that tracks and displays the number of obstacles passed.
 * Automatically draws the count via Canvas by default, and optionally
 * spawns a UMG widget if HUDWidgetClass is assigned.
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

protected:
	// Number of obstacles successfully cleared
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	int32 ObstaclesPassed = 0;

	// Optional UMG Widget class to create and display on screen
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<URunnerHUDWidget> HUDWidgetClass;

	// Active instance of the UMG Widget
	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	TObjectPtr<URunnerHUDWidget> HUDWidgetInstance;

	// Whether to draw the score text via Canvas (active when no UMG widget is used)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	bool bDrawCanvasHUD = true;
};
