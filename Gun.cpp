// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include"Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include"Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleSoundSocket"));
	FHitResult Hit;
	FVector ShotDirection;
	AController* OwnerController = GetOwnerContoller();
	if (OwnerController == nullptr) { return ; }
	bool bSuccess = GunTrace(Hit, ShotDirection);
	if (bSuccess) {
		//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Blue, true);//hitlocation because we wanted to know the hit location
		
	 	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect,Hit.Location,ShotDirection.Rotation());//hit is the object point where we are hitting and it contain all the information about the point 3rd parameter is a end location,4th is the rotation
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound,Hit.Location);
		AActor* HitActor=Hit.GetActor();//to whomever actor our hit result hit we apply damage to that
		if (HitActor) {
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage,DamageEvent,OwnerController,this);
		}
	}

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
bool  AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection) {

	FVector Location;
	FRotator Rotation;
	AController* OwnerController = GetOwnerContoller();

	if (OwnerController == nullptr) { return false; }

	OwnerController->GetPlayerViewPoint(Location, Rotation);// to draw degub camera at exact location at which my gun is locating and its rotation,Here location and rotation are out parameters it will find the correct location and rotaion og the gun and stoe it in those out parameters value and pass them in to the draw debug sphere
	//DrawDebugCamera(GetWorld(), Location, Rotation,90,2,FColor::Blue,true);//drawing debug camera to get the view port of the gun for the ray tracing
	//now for the line trace we need to find the final location
	 ShotDirection = -Rotation.Vector();// in which direction player is facing and its negativeis the direction from where the shot is coming 

	FVector End = Location + Rotation.Vector() * MaxRange;//2 nd one is ther to find the vector in that rotaion direction
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());//for avoid the avtor and the gun itself so the bullet does not hit the capsule and the gun

	return  GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}
AController* AGun:: GetOwnerContoller() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());//we are gettin the owner of the gun and then finding its controller 
	if (OwnerPawn == nullptr) { return nullptr; }
	AController* OwnerController = OwnerPawn->GetController();
	return OwnerController;
}

