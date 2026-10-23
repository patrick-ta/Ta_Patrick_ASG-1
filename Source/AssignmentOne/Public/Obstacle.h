
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "Obstacle.generated.h"

class UBoxComponent;
class UPrimitiveComponent;

UCLASS(Blueprintable)
class ASSIGNMENTONE_API AObstacle : public AActor
{
    GENERATED_BODY()

public:
    AObstacle();

protected:
    virtual void BeginPlay() override;

    // Obstacle animation
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle")
    UPaperFlipbookComponent* FlipbookComponent;

    // Collision box used to detect the player
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle")
    UBoxComponent* CollisionBox;

    // Movement speed in Unreal units per second
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    float MoveSpeed = 175.0f;

    // Tracks if this obstacle has already been counted as passed
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle")
    bool bHasPassedPlayer = false;

    // X threshold behind the player where obstacles get destroyed
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    float DespawnXThreshold = -500.0f;

    // Called when another actor overlaps the obstacle
    UFUNCTION()
    void OnObstacleOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComponent,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

public:
    virtual void Tick(float DeltaTime) override;
};
