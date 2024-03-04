// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (OwnerComp.GetAIOwner() == nullptr) {// to get the hold of ai controller then from ai controller we gove have the acess of the player pawn
		return EBTNodeResult::Failed;

	}
	AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());//get pawn return the pointer that value of the pawn or the character that our ai controller is controlling
	if (Character == nullptr) {
		return EBTNodeResult::Failed;
	}
	//now we can call the shoot
	Character->Shoot();
	return EBTNodeResult::Succeeded;

}