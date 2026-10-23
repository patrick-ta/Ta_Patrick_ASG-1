
#include "Obstacle.h"

#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "RunnerCharacter.h"

AObstacle::AObstacle()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the flipbook component
    FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(
        TEXT("FlipbookComponent")
    );

    RootComponent = FlipbookComponent;

    // Create the collision box
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(
        TEXT("CollisionBox")
    );

    CollisionBox->SetupAttachment(RootComponent);

    // Configure collision to detect overlaps
    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
    CollisionBox->SetGenerateOverlapEvents(true);

    // Bind the overlap event
    CollisionBox->OnComponentBeginOverlap.AddDynamic(
        this,
        &AObstacle::OnObstacleOverlap
    );
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

void AObstacle::OnObstacleOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComponent,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (ARunnerCharacter* Runner = Cast<ARunnerCharacter>(OtherActor))
    {
        Runner->TriggerGameOver();
    }
}
