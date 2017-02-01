// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "TeleportAnyActor.h"


// Sets default values for this component's properties
UTeleportAnyActor::UTeleportAnyActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTeleportAnyActor::BeginPlay()
{
	Super::BeginPlay();
	if (TeleportTrigger) { bDidPassValidation = true; }
	// ...
	
}


// Called every frame
void UTeleportAnyActor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (!bDidPassValidation) return;
	//find all the overlapping actors 
	TArray<AActor*> OverLappingActors;

	TeleportTrigger->GetOverlappingActors(OUT OverLappingActors);
	//Itrate through them adding their masses 
	for (const auto& Actor : OverLappingActors)
	{
		//set actort location + rotation
		Actor->TeleportTo(TeleportLocation, FRotator(0.f, 0.f, 0.f), false, true);
		//remove physics so actor will not retain old velocity
		Actor->FindComponentByClass<UPrimitiveComponent>()->SetAllPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
	}
	// ...
}

