
#include "RunnerHUDWidget.h"
#include "Components/TextBlock.h"

void URunnerHUDWidget::UpdateObstacleCount_Implementation(int32 NewCount)
{
    ObstaclesPassed = NewCount;

    if (ObstacleCountText)
    {
        ObstacleCountText->SetText(
            FText::Format(
                FText::FromString(TEXT("Score: {0}")),
                FText::AsNumber(NewCount)
            )
        );
    }
}
