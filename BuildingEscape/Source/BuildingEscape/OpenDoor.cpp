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
	

	Owner = GetOwner();
	
}

void UOpenDoor::OpenDoor()
{
	//find the owning actor
	//AActor *Owner = GetOwner();
	//set the door rotation
	
	FRotator Rotation = Owner->GetActorRotation();
	Owner->SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	//find the owning actor
	//ctor *Owner = GetOwner();
	//set the door rotation
	FRotator Rotation = Owner->GetActorRotation();
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//Poll the Trigger 
	if (GetTotalMassOfActorsOnPlate() > MassRequiredToOpenDoor) //TODO make into a parameter
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (LastDoorOpenTime + DoorCloseDelay <= CurrentTime) {
		CloseDoor();
	}
	
	
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	//find all the overlapping actors 
	TArray<AActor*> OverLappingActors;
	
	PressurePlate->GetOverlappingActors(OUT OverLappingActors);
	//Itrate through them adding their masses 
	for (const auto* Actor : OverLappingActors)
	{
		TotalMass += Actor->GetRootPrimitiveComponent()->GetMass();
		//UE_LOG(LogTemp, Error, TEXT("total mass+= %s"), *Actor->GetName());
	}
	return TotalMass;
}

