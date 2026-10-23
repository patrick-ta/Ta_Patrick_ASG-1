#include "Obstacle.h"

AObstacle::AObstacle()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the flipbook component
    FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(
        TEXT("FlipbookComponent")
    );

    RootComponent = FlipbookComponent;
}

void AObstacle::BeginPlay()
{
    Super::BeginPlay();
}

void AObstacle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Move left at a constant rate
    AddActorWorldOffset(
        FVector(-MoveSpeed * DeltaTime, 0.0f, 0.0f)
    );
}