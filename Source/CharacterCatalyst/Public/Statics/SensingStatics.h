// © 2024 Marco Silva. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SensingStatics.generated.h"

UENUM(BlueprintType)
enum class ESenseResult : uint8
{
	CanSee			UMETA(DisplayName = "CAN_SEE"),
	OutOfView		UMETA(Displayname = "OUT_OF_VIEW"),
	Blocked			UMETA(DisplayName = "BLOCKED")
};

/**
 * 
 */
UCLASS()
class CHARACTERCATALYST_API USensingStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Sensing Statics")
	static bool CouldSeeActor(AActor* InActor, FVector ViewLocation, FRotator DesiredRotation, float SightRadius = 45.0f);

	UFUNCTION(BlueprintCallable, Category = "Sensing Statics")
	static bool CanSeeExtent(FVector Direction, FVector ViewLocation, AActor* Actor, ETraceTypeQuery TraceType, 
		EDrawDebugTrace::Type DebugType, FVector& OutExtent);

	UFUNCTION(BlueprintCallable, Category = "Sensing Statics")
	static bool CanSeeActor(AActor* InActor, FVector ViewLocation, FRotator DesiredRotation, 
		float SightRadius, ETraceTypeQuery TraceType, bool bDebug = false, float DebugDuration = 0.2f);

	UFUNCTION(BlueprintCallable, Category = "Sensing Statics")
	static ESenseResult SenseActor(AActor* InActor, FVector ViewLocation, FRotator DesiredRotation, 
		float SightRadius, ETraceTypeQuery TraceType, bool bDebug = false, float DebugDuration = 0.2f);
};
