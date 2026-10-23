#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RunnerHUDWidget.generated.h"

class UTextBlock;

/**
 * UMG Widget class for displaying the runner HUD (e.g. obstacles passed count).
 */
UCLASS(Blueprintable)
class ASSIGNMENTONE_API URunnerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Updates the displayed obstacle count. Can be handled or overridden in Blueprints.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD")
	void UpdateObstacleCount(int32 NewCount);
	virtual void UpdateObstacleCount_Implementation(int32 NewCount);

	// Current number of obstacles passed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	int32 ObstaclesPassed = 0;

protected:
	// Optional text block in the widget hierarchy bound by name
	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly, Category = "HUD")
	TObjectPtr<UTextBlock> ObstacleCountText;
};
