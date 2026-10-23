
#include "Obstacle.h"

#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "RunnerCharacter.h"
#include "RunnerHUD.h"

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

    // Check if the obstacle has safely passed the player
    if (!bHasPassedPlayer)
    {
        if (const APlayerController* PC = GetWorld()->GetFirstPlayerController())
        {
            if (const APawn* PlayerPawn = PC->GetPawn())
            {
                if (GetActorLocation().X < PlayerPawn->GetActorLocation().X)
                {
                    bHasPassedPlayer = true;

                    if (ARunnerHUD* HUD = Cast<ARunnerHUD>(PC->GetHUD()))
                    {
                        HUD->IncrementObstaclesPassed();
                    }
                }
            }
        }
    }

    // Clean up obstacle once it is far off screen to the left
    if (GetActorLocation().X < DespawnXThreshold)
    {
        Destroy();
    }
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
        bHasPassedPlayer = true;
        Runner->TriggerGameOver();
    }
}
