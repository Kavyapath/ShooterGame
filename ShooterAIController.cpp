// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"


void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);//to get the actor to which our ai sees

	if (AIBehavior != nullptr) {
		RunBehaviorTree(AIBehavior);
	
	
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
	
	}
void AShooterAIController::Tick(float DeltaTime)
{
	/*APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);//to get the actor to which our ai sees
	SetFocus(PlayerPawn);// to set the aiming focus for the ai

	if (LineOfSightTo(PlayerPawn)) {


		//SetFocus(PlayerPawn);// to set the aiming focus for the ai
		//MoveToActor(PlayerPawn, AcceptanceRadius);//for moving to the shooter actor
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	}
	
	else {
		//ClearFocus(EAIFocusPriority::Gameplay);
		//StopMovement();
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}*/
}

bool AShooterAIController::IsDead() const
{

	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter != nullptr) {
		return ControlledCharacter->IsDead();
	}
	return true;
}
