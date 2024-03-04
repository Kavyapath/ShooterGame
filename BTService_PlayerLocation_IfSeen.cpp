// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation_IfSeen.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include"AIController.h"

UBTService_PlayerLocation_IfSeen::UBTService_PlayerLocation_IfSeen() {
	NodeName = "Updated Player Location If Seen";
}
void UBTService_PlayerLocation_IfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	//we are calling this function at every frame

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);//to get the actor to which our ai sees
	if (PlayerPawn == nullptr) {
		return;
	}
	if (OwnerComp.GetAIOwner() == nullptr) {
		return;
	}
	if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)) {

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);//function to know the ai about he player location it takes a selectedBlackboardKey and the player pawn which ai wants to see and through that we can get its location using getactorLocation()
	}
	else {
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
 }