// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KeySpotlightTrigger.h"
#include "Components/ActorComponent.h"
#include "OpenGameWinningDoor.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenGameWinningDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenGameWinningDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	UPROPERTY(EditAnywhere)
		AActor* TriggerSpotLight1;
	UPROPERTY(EditAnywhere)
		AActor* TriggerSpotLight2;
	UPROPERTY(EditAnywhere)
		AActor* TriggerSpotLight3;
	
	//array of UKeySpotlightTrigger, they must all be active for the door to open 
	TArray<UKeySpotlightTrigger*> KeyTriggersRequiredToWin;

	//extract all UKeySpotlightTrigger classes from  TriggerSpotLight components 
	void InitialIzeKeyTriggers();
};
