#include "RunnerHUD.h"
#include "RunnerHUDWidget.h"
#include "Engine/Canvas.h"

ARunnerHUD::ARunnerHUD()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARunnerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		if (APlayerController* PC = GetOwningPlayerController())
		{
			HUDWidgetInstance = CreateWidget<URunnerHUDWidget>(PC, HUDWidgetClass);
			if (HUDWidgetInstance)
			{
				HUDWidgetInstance->AddToViewport();
				HUDWidgetInstance->UpdateObstacleCount(ObstaclesPassed);
				bDrawCanvasHUD = false;
			}
		}
	}
}

void ARunnerHUD::DrawHUD()
{
	Super::DrawHUD();

	if (bDrawCanvasHUD && Canvas)
	{
		const FString DisplayText = FString::Printf(TEXT("Obstacles Passed: %d"), ObstaclesPassed);

		// Draws text in the top-left area with white color and 1.5x font scale
		DrawText(
			DisplayText,
			FLinearColor::White,
			30.0f,
			30.0f,
			nullptr,
			1.5f,
			false
		);
	}
}

void ARunnerHUD::IncrementObstaclesPassed()
{
	ObstaclesPassed++;

	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->UpdateObstacleCount(ObstaclesPassed);
	}
}

void ARunnerHUD::SetObstaclesPassed(int32 Count)
{
	ObstaclesPassed = Count;

	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->UpdateObstacleCount(ObstaclesPassed);
	}
}

void ARunnerHUD::ResetObstaclesPassed()
{
	SetObstaclesPassed(0);
}
