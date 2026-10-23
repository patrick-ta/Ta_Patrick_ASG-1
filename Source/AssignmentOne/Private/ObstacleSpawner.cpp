#include "ObstacleSpawner.h"
#include "TimerManager.h"

AObstacleSpawner::AObstacleSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AObstacleSpawner::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(
        SpawnTimerHandle,
        this,
        &AObstacleSpawner::SpawnObstacle,
        SpawnInterval,
        true
    );
}

void AObstacleSpawner::SpawnObstacle()
{
    TSubclassOf<AObstacle> SelectedObstacleClass =
        FMath::RandBool() ? SnakeObstacleClass : ArrowObstacleClass;

    if (!SelectedObstacleClass)
    {
        return;
    }

    FVector SpawnLocation = GetActorLocation() + SpawnOffset;

    // If the selected obstacle is an arrow, randomize its Z position
    if (SelectedObstacleClass == ArrowObstacleClass)
    {
        const float ZOffsets[] = { 0.0f, 30.0f };

        SpawnLocation.Z += ZOffsets[FMath::RandRange(0, 1)];
    }

    const FRotator SpawnRotation = GetActorRotation();

    GetWorld()->SpawnActor<AObstacle>(
        SelectedObstacleClass,
        SpawnLocation,
        SpawnRotation
    );
}

void AObstacleSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}