// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gun.h"
#include"Engine/DamageEvents.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = MaxHealth;
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Gun=GetWorld()->SpawnActor<AGun>(GunClass); //for spawning guns unthe actors hand
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);//for hiding the previous gun from the mesh
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));//creating a new socket then now dynamically adding the gun to the weapon socket
	Gun->SetOwner(this);//that  this gun owner is the object pointer of the shooter character class and we will use it in damage function to get owner instigator

}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0  ;
	//return false;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,  &AShooterCharacter::MoveForward); 
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);//PlayerInputComponent->BindAxis(TEXT("LookUp"), this, AShooterCharacter::LookUp);//this addcontrollerpitch input is define in the pawn class which is a parent class of the character so we can directly call from this also
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this,&ACharacter::Jump);//this jump is define in the character class
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

void AShooterCharacter::MoveForward(float AxisValue) {
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

/*

void AShooterCharacter::LookUp(float AxisValue) {
	AddControllerPitchInput(AxisValue);
}*/

void AShooterCharacter::MoveRight(float AxisValue) {
	AddMovementInput(GetActorRightVector() * AxisValue);
}


void  AShooterCharacter::LookUpRate(float AxisValue) {
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void  AShooterCharacter::LookRightRate(float AxisValue) {
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}
float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply=Super::TakeDamage(DamageAmount, DamageEvent,EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health is = %f"), Health);

	return DamageToApply;
 }

