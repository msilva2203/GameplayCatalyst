// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CameraSwayComponent.h"

// Sets default values for this component's properties
UCameraSwayComponent::UCameraSwayComponent() :
	SwayRollAmount(5.0f),
	SwayInterpSpeed(2.0f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraSwayComponent::BeginPlay()
{
	Super::BeginPlay();

	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
	
}


// Called every frame
void UCameraSwayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Camera) return;

	// Find normalized actor velocity
	FVector NormalizedVelocity = GetOwner()->GetVelocity();
	NormalizedVelocity.Normalize();

	// Calculate dot product of normalized velocity and actor right vector
	float Dot = FVector::DotProduct(NormalizedVelocity, GetOwner()->GetActorRightVector());

	// Find target roll value
	float TargetRoll = FMath::Lerp(0.0f, SwayRollAmount, Dot);

	// Interpolate the current sway roll value to target value
	CurrentSwayRoll = FMath::FInterpTo(CurrentSwayRoll, TargetRoll, DeltaTime, SwayInterpSpeed);

	// Set the camera roll to new value
	FRotator NewRotation = Camera->GetComponentRotation();
	NewRotation.Roll = CurrentSwayRoll;

	Camera->SetWorldRotation(NewRotation);
}

