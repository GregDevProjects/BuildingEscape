// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TeleportTwoActors.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UTeleportTwoActors : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeleportTwoActors();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	


	//the other actor to teleport
	UPROPERTY(EditAnywhere)
		AActor* PlayerToTeleport;

	//the other actor to teleport
	UPROPERTY(EditAnywhere)
		AActor* ActorToTeleport;

	//teleport actor on overlap with this trigger
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TeleportTrigger;

	UPROPERTY(EditAnywhere)
		FVector TeleportLocation;
private:
	void TeleportAndRemoveVelocity(FVector, AActor*);
	
};
