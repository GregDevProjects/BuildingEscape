// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TeleportAnyActor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UTeleportAnyActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeleportAnyActor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//teleport any actor that overlaps with this trigger
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TeleportTrigger;

	UPROPERTY(EditAnywhere)
		FVector TeleportLocation;
	
private:
	bool bDidPassValidation = false;
};
