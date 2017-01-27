// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "KeySpotlightTrigger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UKeySpotlightTrigger : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKeySpotlightTrigger();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	bool bGetIsActivated();

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TriggerSpotLight;

	UPROPERTY(EditAnywhere)
		AActor* ActorThatTriggers;

	USpotLightComponent* Spotlight = nullptr;

	bool bHasAllDependancies();

	bool bIsActivated = false;
	
};
