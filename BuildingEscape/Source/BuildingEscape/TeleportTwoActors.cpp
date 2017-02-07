// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "TeleportTwoActors.h"


// Sets default values for this component's properties
UTeleportTwoActors::UTeleportTwoActors()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTeleportTwoActors::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UTeleportTwoActors::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (TeleportTrigger->IsOverlappingActor(PlayerToTeleport)) {
		UE_LOG(LogTemp, Warning, TEXT("hit"));
		TeleportAndRemoveVelocity(TeleportLocation,PlayerToTeleport);
		float TeleportOffset = 700.f;
		TeleportAndRemoveVelocity(
			/*TeleportLocation,*/
			FVector(
				TeleportLocation.X,
				TeleportLocation.Y + 200.f,
				TeleportLocation.Z + 100.f
			), 
			ActorToTeleport
		);
	}
}

void UTeleportTwoActors::TeleportAndRemoveVelocity(FVector Location, AActor* ActorThatWillBeTeleported)
{
	//set actort location + rotation
	ActorThatWillBeTeleported->TeleportTo(Location, FRotator(0.f, 0.f, 0.f),false,true);
	//remove physics so actor will not retain old velocity
	ActorThatWillBeTeleported->FindComponentByClass<UPrimitiveComponent>()->SetAllPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
}

