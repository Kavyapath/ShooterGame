// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"


class AGun;

UCLASS()
class SIMPLE_SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame 

	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	UFUNCTION(BlueprintPure)
		float GetHealthPercentage() const;


	virtual void Tick(float DeltaTime) override;
	void Shoot();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void MoveForward(float AxisValue);
	//void LookUp(float AxisValue);
	//void LookRight(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	UPROPERTY(EditAnywhere)
		float RotationRate=150;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> GunClass;
	UPROPERTY()
		 AGun* Gun;
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere)
		float Health;
};
