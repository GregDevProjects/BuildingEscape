// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	


	OpenGameWinningDoor = GetOwner()->FindComponentByClass<UOpenGameWinningDoor>();

	if ( !OpenGameWinningDoor) {
		UE_LOG(LogTemp, Warning, TEXT("OpenGameWinningDoor on %s is null!"), *GetOwner()->GetName());
	}
	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
		
	if (!OpenGameWinningDoor) { return; }
	if (OpenGameWinningDoor->GetAllTriggersHit()) {
		OnOpenRequest.Broadcast();
	}
		//TODO broacast close door 
		//OnCloseRequest.Broadcast();
	
}


