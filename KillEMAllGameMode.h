// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Simple_ShooterGameModeBase.h"
#include "KillEMAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API AKillEMAllGameMode : public ASimple_ShooterGameModeBase
{
	GENERATED_BODY()
public:

		virtual void PawnKilled(APawn* PawnKilled) override;
		
public:
	void EndGame(bool bIsPlayerWinner);
};
