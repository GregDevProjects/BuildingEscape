// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TeleportOrRaise.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerHitsKey);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UTeleportOrRaise : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeleportOrRaise();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable, Category = "Somehing")
		FOnTriggerHitsKey OnTriggerHitsKey;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* TeleportTrigger;

	UPROPERTY(EditAnywhere)
		AActor* KeyToRaisePlatform;

private:
	bool bDidPassValidation = false;

	AActor* Player = nullptr;

	//ATriggerVolume* TeleportTrigger = nullptr;
		
	
};
