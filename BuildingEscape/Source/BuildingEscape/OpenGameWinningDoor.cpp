// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenGameWinningDoor.h"


// Sets default values for this component's properties
UOpenGameWinningDoor::UOpenGameWinningDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenGameWinningDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialIzeKeyTriggers();
	
	// ...
	
}


// Called every frame
void UOpenGameWinningDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	bool bGameIsWon = true;
	for (const auto& KeyTrigger : KeyTriggersRequiredToWin)
	{
		if (!KeyTrigger->bGetIsActivated()) {
			bGameIsWon = false;
		}
	}

	if (bGameIsWon) {
		bAllTriggersAreHit = true; 
		GetOwner()->SetActorTickEnabled(false);
	}

	// ...
}

bool UOpenGameWinningDoor::GetAllTriggersHit()
{
	return bAllTriggersAreHit;
}

void UOpenGameWinningDoor::InitialIzeKeyTriggers()
{
	if (TriggerSpotLight1 && TriggerSpotLight2 && TriggerSpotLight3) {
		KeyTriggersRequiredToWin.Add(TriggerSpotLight1->FindComponentByClass<UKeySpotlightTrigger>());
		KeyTriggersRequiredToWin.Add(TriggerSpotLight2->FindComponentByClass<UKeySpotlightTrigger>());
		KeyTriggersRequiredToWin.Add(TriggerSpotLight3->FindComponentByClass<UKeySpotlightTrigger>());
	} else {
		UE_LOG(LogTemp, Error, TEXT("UOpenGameWinningDoor Missing 3 UKeySpotlightTrigger"));
	}
}

