// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PlayerTelePort.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPlayerTelePort : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerTelePort();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//// The actor that will be teleported 
	//UPROPERTY(EditAnywhere)
	//	AActor* ActorToTeleport;
		
	UPROPERTY(EditAnywhere)
		FVector TeleportLocation;

	//teleport actor on overlap with this trigger
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TeleportTrigger;

private:
	// The actor that will be teleported 
	AActor* ActorToTeleport = nullptr;

	void InitializeComponent();
	
};
