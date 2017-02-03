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


	if (TeleportTrigger) {
		UE_LOG(LogTemp, Warning, TEXT("TEle trigger found!"));
	}
	
	for (TActorIterator<ATriggerVolume> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		FString ActorLabel = *ActorItr->GetActorLabel();
		if (ActorLabel.Equals("Trigger_tech")) {
			TeleportTrigger = *ActorItr;
			bDidPassValidation = true;
		}
		
	}



	// ...
	
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
		if (Actor->GetActorLabel().Equals("Glow_Sphere_Blueprint")) { 
			OnTriggerHitsKey.Broadcast(); 
			GetOwner()->SetActorTickEnabled(false);
		}
	}


	// ...
	// ...
}

