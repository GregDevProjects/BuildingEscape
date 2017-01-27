// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "KeySpotlightTrigger.h"


// Sets default values for this component's properties
UKeySpotlightTrigger::UKeySpotlightTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKeySpotlightTrigger::BeginPlay()
{
	Super::BeginPlay();
	bHasAllDependancies();

	
}


// Called every frame
void UKeySpotlightTrigger::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	//if actor set in uproperty matches trigger set in uproperty 
	if (TriggerSpotLight->IsOverlappingActor(ActorThatTriggers)) {
		bIsActivated = true;
		Spotlight->SetLightColor(FLinearColor(0.f, 255.f, 0.f));
	}
	else {
		bIsActivated = false;
		Spotlight->SetLightColor(FLinearColor(1.f, 1.f, 1.f));
	}
	// ...
}

bool UKeySpotlightTrigger::bGetIsActivated()
{
	return bIsActivated;
}

bool UKeySpotlightTrigger::bHasAllDependancies()
{
	Spotlight = GetOwner()->FindComponentByClass<USpotLightComponent>();
	if (!Spotlight || !TriggerSpotLight || !ActorThatTriggers) {
		FString ObjectName = GetOwner()->GetName();
		UE_LOG(LogTemp, Error, TEXT("KeySpotlightTrigger on %s requires a USpotLightComponent and both UProperties to be set"), *ObjectName);
		return false;
	}
	return true;
}

