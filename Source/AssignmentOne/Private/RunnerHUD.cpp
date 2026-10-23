#include "RunnerHUD.h"
#include "RunnerHUDWidget.h"
#include "RunnerGameOverWidget.h"
#include "Engine/Canvas.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

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

	if (!Canvas) return;

	// Draw in-game score if canvas fallback is enabled and game is not over
	if (bDrawCanvasHUD && !bIsGameOver)
	{
		const FString DisplayText = FString::Printf(TEXT("Obstacles Passed: %d"), ObstaclesPassed);

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

	// Draw canvas Game Over overlay if no UMG GameOver widget is assigned
	if (bIsGameOver && !GameOverWidgetInstance)
	{
		// Dark semi-transparent background
		DrawRect(
			FLinearColor(0.0f, 0.0f, 0.0f, 0.65f),
			0.0f,
			0.0f,
			Canvas->SizeX,
			Canvas->SizeY
		);

		// Center "GAME OVER"
		const FString GameOverText = TEXT("GAME OVER");
		const FString ScoreText = FString::Printf(TEXT("Final Score: %d"), ObstaclesPassed);

		float TextW = 0.0f;
		float TextH = 0.0f;
		GetTextSize(GameOverText, TextW, TextH, nullptr, 3.0f);
		DrawText(
			GameOverText,
			FLinearColor::Red,
			(Canvas->SizeX - TextW) * 0.5f,
			(Canvas->SizeY * 0.4f) - TextH,
			nullptr,
			3.0f,
			false
		);

		GetTextSize(ScoreText, TextW, TextH, nullptr, 2.0f);
		DrawText(
			ScoreText,
			FLinearColor::White,
			(Canvas->SizeX - TextW) * 0.5f,
			Canvas->SizeY * 0.5f,
			nullptr,
			2.0f,
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

void ARunnerHUD::ShowGameOver()
{
	if (bIsGameOver) return;
	bIsGameOver = true;

	APlayerController* PC = GetOwningPlayerController();

	if (GameOverWidgetClass && PC)
	{
		GameOverWidgetInstance = CreateWidget<URunnerGameOverWidget>(PC, GameOverWidgetClass);
		if (GameOverWidgetInstance)
		{
			GameOverWidgetInstance->SetupGameOver(ObstaclesPassed);
			GameOverWidgetInstance->AddToViewport(10); // Above in-game HUD

			// Enable mouse cursor and set input mode for UI interaction
			PC->SetShowMouseCursor(true);
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(GameOverWidgetInstance->TakeWidget());
			PC->SetInputMode(InputMode);
		}
	}
	else if (PC)
	{
		PC->SetShowMouseCursor(true);
	}
}

void ARunnerHUD::RestartLevel()
{
	if (APlayerController* PC = GetOwningPlayerController())
	{
		PC->SetShowMouseCursor(false);
		PC->SetInputMode(FInputModeGameOnly());

		if (APawn* PlayerPawn = PC->GetPawn())
		{
			PlayerPawn->EnableInput(PC);
		}
	}

	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
}
