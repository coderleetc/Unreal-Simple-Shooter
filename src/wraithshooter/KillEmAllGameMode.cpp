// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld())) 
    {
        if (!Controller->IsDead())
        {
            return;
        }
    }
    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) 
{
    //如果是player的controller就输入
    for (AController* Controller : TActorRange<AController>(GetWorld())) 
    {
        bool bIsPlayerController = Controller->IsPlayerController();
        if (bIsPlayerWinner)
        {
            Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerController);
        }
        else
        {
            Controller->GameHasEnded(Controller->GetPawn(), !bIsPlayerController);
        }
    }
}