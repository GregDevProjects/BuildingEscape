// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "TeleportOrRaise.h"


// Sets default values for this component's properties
UTeleportOrRaise::UTeleportOrRaise()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTeleportOrRaise::BeginPlay()
{
	Super::BeginPlay();
	
	
	Player = GetWorld()->GetFirstPlayerController();


	if (TeleportTrigger && KeyToRaisePlatform) {
		bDidPassValidation = true;
		
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No TriggerVolume found for %s"), *GetOwner()->GetName());
	}
	
	
}


// Called every frame
void UTeleportOrRaise::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!bDidPassValidation) return;
	//find all the overlapping actors 
	TArray<AActor*> OverLappingActors;

	TeleportTrigger->GetOverlappingActors(OUT OverLappingActors);
	//Itrate through them adding their masses 
	for (const auto& Actor : OverLappingActors)
	{
		if (Actor == KeyToRaisePlatform) {
			OnTriggerHitsKey.Broadcast(); 
			GetOwner()->SetActorTickEnabled(false);
		}
	}


	// ...
	// ...
}

