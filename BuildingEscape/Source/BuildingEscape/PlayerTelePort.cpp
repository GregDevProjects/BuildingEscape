// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PlayerTelePort.h"


// Sets default values for this component's properties
UPlayerTelePort::UPlayerTelePort()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerTelePort::BeginPlay()
{
	Super::BeginPlay();
	InitializeComponent();
	// ...
	
}




// Called every frame
void UPlayerTelePort::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (TeleportTrigger->IsOverlappingActor(ActorToTeleport)) {
		//set actort location + rotation
		ActorToTeleport->TeleportTo(TeleportLocation, FRotator(0.f, 0.f, 0.f));
		//remove physics so actor will not retain old velocity
		ActorToTeleport->FindComponentByClass<UPrimitiveComponent>()->SetAllPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
	}
}

void UPlayerTelePort::InitializeComponent()
{
	ActorToTeleport = GetOwner();
	if (!TeleportTrigger || !ActorToTeleport ) {
		UE_LOG(LogTemp, Error, TEXT("Playerteleport must be played on an AActor and requires TeleportTrigger property set"));
	}
}

