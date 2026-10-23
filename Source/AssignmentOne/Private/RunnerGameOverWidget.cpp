#include "RunnerGameOverWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

void URunnerGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &URunnerGameOverWidget::OnRestartClicked);
	}
}

void URunnerGameOverWidget::SetupGameOver_Implementation(int32 FinalScore)
{
	FinalObstacleCount = FinalScore;

	if (FinalScoreText)
	{
		FinalScoreText->SetText(
			FText::Format(
				FText::FromString(TEXT("Final Score: {0}")),
				FText::AsNumber(FinalScore)
			)
		);
	}
}

void URunnerGameOverWidget::OnRestartClicked()
{
	if (APlayerController* PC = GetOwningPlayer())
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
