// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

enum ELineTracePosition { StartOfLineTrace, EndOfLineTrace };

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;

	
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
private:
	//how far ahead the player can reach in cm
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputHandler = nullptr;
	//Ray-cast and grab what's in reach
	void Grab();
	//release grabbed object 
	void Release();
	//log
	void FindPhysicsHandlerComponent();
	//Setup (assumed) attached input component 
	void SetupInputComponent();
	//Return hit for first physics body in reach 
	const FHitResult GetFirstPhysicsBodyInReach();

	UPrimitiveComponent* ComponentToGrab = nullptr;

	const FVector GetPawnLineTracePosition( ELineTracePosition);

};

