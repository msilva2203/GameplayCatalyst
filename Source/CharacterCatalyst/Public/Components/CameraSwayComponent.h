// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraSwayComponent.generated.h"


UCLASS( ClassGroup=(GameplayCatalyst), meta = (BlueprintSpawnableComponent))
class CHARACTERCATALYST_API UCameraSwayComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraSwayComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Sway Behaviour")
	float SwayRollAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Sway Behaviour")
	float SwayInterpSpeed;

private:
	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY()
	float CurrentSwayRoll;
};
