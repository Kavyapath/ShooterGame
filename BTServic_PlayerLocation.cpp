// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServic_PlayerLocation.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

//for setting the player location in the world so that ai can know the location

 UBTServic_PlayerLocation::UBTServic_PlayerLocation()
{
	 NodeName = "Update Player Location";
}
 void UBTServic_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
 {
	 Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	 //we are calling this function at every frame

	 APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);//to get the actor to which our ai sees
	 if (PlayerPawn == nullptr) {
		 return;
	 }

	 OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());//function to know the ai about he player location it takes a selectedBlackboardKey and the player pawn which ai wants to see and through that we can get its location using getactorLocation()
 }