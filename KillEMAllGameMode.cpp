// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEMAllGameMode.h"
#include "EngineUtils.h"
#include"GameFrameWork/Controller.h"
#include "ShooterAIController.h"

void AKillEMAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	//UE_LOG(LogTemp, Warning, TEXT("A Pawn was killed"));
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());//Get hold of the player controller so thatr we can define the win and the loose condition
	if (PlayerController != nullptr) {
		PlayerController->GameHasEnded(nullptr,false);///it is not the winnig player controller because the player has died
	}
	//for loop to iterate over the  Shooter ai character
	//If  one of the ai charcter  not Dead we will do an early return 
	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld())) {
		if (!AIController->IsDead()) {	//if any of the ai controller is not dead it means that we did not won so we will do the early return
			return;
		}
	}
	//if all the ai is dead now we are going to call the endgame function and passing true for our player controller that he has won the game
	EndGame(true);
 }

void AKillEMAllGameMode::EndGame(bool bIsPlayerWinner)
{
	
	for (AController* Controller : TActorRange<AController>(GetWorld())) {
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);//so that the focus is should be on our player
		
	}
}
