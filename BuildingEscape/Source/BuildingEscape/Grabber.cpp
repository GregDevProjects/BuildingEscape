// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	//look for attached physics and input handle
	SetupInputComponent();
	FindPhysicsHandlerComponent();
}

void UGrabber::FindPhysicsHandlerComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		//physicshandler is found
		UE_LOG(LogTemp, Warning, TEXT("Found dat physicshandle"));
	}
	else {
		FString ObjectName = GetOwner()->GetName();
		UE_LOG(LogTemp, Error, TEXT("Grabber Component on %s requires PhysicsHandle"), *ObjectName);
	}
}

void UGrabber::SetupInputComponent()
{
	InputHandler = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputHandler) {
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found!"));
		// Bind the input axis 
		InputHandler->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputHandler->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Grabber Component on %s requires InputComponent"), *GetOwner()->GetName());
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerViewPointLocation = GetPawnLineTracePosition(ELineTracePosition::StartOfLineTrace);
	FVector LineTraceEnd = GetPawnLineTracePosition(ELineTracePosition::EndOfLineTrace);
	//debug trace line 
	//DrawDebugLine(
	//	GetWorld(),
	//	PlayerViewPointLocation,
	//	LineTraceEnd,
	//	FColor(255, 0, 0),
	//	false,
	//	0.f,
	//	0.f,
	//	10.f
	//);
	//Setup query parameters 
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	//Ray-cast out to reach distance 
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorCollision = Hit.GetActor();
	if (ActorCollision) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorCollision->GetName());
	}

	return Hit;
}

const FVector UGrabber::GetPawnLineTracePosition(ELineTracePosition TracePosition)
{
	// get player view point 
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	FVector LineTraceDirection = PlayerViewPointRotation.Vector();
	if (TracePosition == ELineTracePosition::StartOfLineTrace) {
		return LineTraceDirection;
	} 
	//else return end of line trace
	FVector LineTraceEnd = PlayerViewPointLocation + LineTraceDirection * Reach;
	return LineTraceEnd;
	
}



void UGrabber::Grab() {
	if (!PhysicsHandle ) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));

	//LINE TRACE Try and reach any actors with physics body collision channel set 
	auto HitResult = GetFirstPhysicsBodyInReach();
	ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	//If we hit something then attach a physics handle 
	//TODO	Attach physics handle
	if (ActorHit) {
		//allow overlapping with the player so they don't collide and push each other around
		ComponentToGrab->BodyInstance.SetResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true //allow rotation
		);
	}
}

void UGrabber::Release() {
	if (!PhysicsHandle || !ComponentToGrab) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
	
	PhysicsHandle->ReleaseComponent();
	//allow collisions with the player after release
	ComponentToGrab->BodyInstance.SetResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	ComponentToGrab = nullptr;
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	//if physics handle is attached 
	if (!PhysicsHandle ) {return;}
	if (PhysicsHandle->GrabbedComponent) {
		//move the object that we're holding 
		PhysicsHandle->SetTargetLocation(GetPawnLineTracePosition(ELineTracePosition::EndOfLineTrace));
	}
		
}