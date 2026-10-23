#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.h"
#include "ObstacleSpawner.generated.h"

UCLASS(Blueprintable)
class ASSIGNMENTONE_API AObstacleSpawner : public AActor
{
    GENERATED_BODY()

public:
    AObstacleSpawner();

protected:
    virtual void BeginPlay() override;

    // Available obstacle types
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Spawning")
    TSubclassOf<AObstacle> SnakeObstacleClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Spawning")
    TSubclassOf<AObstacle> ArrowObstacleClass;

    // Time between spawns, in seconds
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Spawning", meta = (ClampMin = "0.1"))
    float SpawnInterval = 2.0f;

    // Location where obstacles spawn
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Spawning")
    FVector SpawnOffset = FVector(1000.0f, 0.0f, 0.0f);

    FTimerHandle SpawnTimerHandle;

    void SpawnObstacle();

public:
    virtual void Tick(float DeltaTime) override;
};