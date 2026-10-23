#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "Obstacle.generated.h"

UCLASS(Blueprintable)
class ASSIGNMENTONE_API AObstacle : public AActor
{
    GENERATED_BODY()

public:
    AObstacle();

protected:
    virtual void BeginPlay() override;

    // Flipbook component for the obstacle animation
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle")
    UPaperFlipbookComponent* FlipbookComponent;

    // Movement speed in Unreal units per second
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    float MoveSpeed = 150.0f;

public:
    virtual void Tick(float DeltaTime) override;
};