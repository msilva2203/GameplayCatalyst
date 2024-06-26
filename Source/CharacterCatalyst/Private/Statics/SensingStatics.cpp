// © 2024 Marco Silva. All Rights Reserved.


#include "Statics/SensingStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

bool USensingStatics::CouldSeeActor(AActor* InActor, FVector ViewLocation, FRotator DesiredRotation, float SightRadius)
{
	if (!InActor) return false;

	FVector SelfToOther = InActor->GetActorLocation() - ViewLocation;
	if (SelfToOther.Length() > SightRadius)
	{
		return false;
	}

	SelfToOther.Normalize();
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(DesiredRotation);
	double Dot = SelfToOther.Dot(ForwardVector);

	if (Dot >= UKismetMathLibrary::DegCos(45.0))
		return true;
	return false;
}

bool USensingStatics::CanSeeExtent(FVector Direction, FVector ViewLocation, AActor* Actor, ETraceTypeQuery TraceType, 
	EDrawDebugTrace::Type DebugType, FVector& OutExtent)
{
	if (!Actor) return false;

	FHitResult HitResult;
	FVector Origin, BoxExtent, End;
	Actor->GetActorBounds(false, Origin, BoxExtent);

	Direction = Direction * BoxExtent;
	Direction = Direction * 0.99;
	End = Direction + Origin;

	TArray<AActor*> ActorsToIgnore;
	UKismetSystemLibrary::LineTraceSingle(Actor, ViewLocation, End, TraceType,
		false, ActorsToIgnore, DebugType, HitResult, false);

	if (HitResult.GetActor() == Actor)
	{
		OutExtent = HitResult.Location;
		return true;
	}

	End = Origin - Direction;
	UKismetSystemLibrary::LineTraceSingle(Actor, ViewLocation, End, TraceType,
		false, ActorsToIgnore, DebugType, HitResult, false);

	if (HitResult.GetActor() == Actor)
	{
		OutExtent = HitResult.Location;
		return true;
	}

	return false;
}

bool USensingStatics::CanSeeActor(AActor* InActor, FVector ViewLocation, FRotator DesiredRotation, 
	float SightRadius, ETraceTypeQuery TraceType, bool bDebug, float DebugDuration)
{
	return SenseActor(InActor, ViewLocation, DesiredRotation, 
		SightRadius, TraceType, bDebug, DebugDuration) == ESenseResult::CanSee;
}

ESenseResult USensingStatics::SenseActor(AActor* InActor, FVector ViewLocation, FRotator DesiredRotation, 
	float SightRadius, ETraceTypeQuery TraceType, bool bDebug, float DebugDuration)
{
	FVector Direction, HitLocation;
	FVector Origin, Extent;

	if (!InActor) return ESenseResult::Blocked;

	if (!CouldSeeActor(InActor, ViewLocation, DesiredRotation, SightRadius))
	{
		if (bDebug)
		{
			InActor->GetActorBounds(false, Origin, Extent);
			UKismetSystemLibrary::DrawDebugBox(InActor, Origin, Extent * 1.005, FLinearColor::Yellow, 
				UE::Math::TRotator<double>::ZeroRotator, DebugDuration);
		}
		return ESenseResult::OutOfView;
	}
	Direction = UKismetMathLibrary::GetForwardVector(FRotator(0.0, 0.0, 0.0));
	if (CanSeeExtent(Direction, ViewLocation, InActor, TraceType, EDrawDebugTrace::Type::None, HitLocation))
	{
		if (bDebug)
		{
			InActor->GetActorBounds(false, Origin, Extent);
			UKismetSystemLibrary::DrawDebugBox(InActor, Origin, Extent * 1.005, FLinearColor::Green,
				UE::Math::TRotator<double>::ZeroRotator, DebugDuration);
		}
		return ESenseResult::CanSee;
	}
	Direction = UKismetMathLibrary::GetRightVector(FRotator(0.0, 0.0, 0.0));
	if (CanSeeExtent(Direction, ViewLocation, InActor, TraceType, EDrawDebugTrace::Type::None, HitLocation))
	{
		if (bDebug)
		{
			InActor->GetActorBounds(false, Origin, Extent);
			UKismetSystemLibrary::DrawDebugBox(InActor, Origin, Extent * 1.005, FLinearColor::Green,
				UE::Math::TRotator<double>::ZeroRotator, DebugDuration);
		}
		return ESenseResult::CanSee;
	}
	Direction = UKismetMathLibrary::GetUpVector(FRotator(0.0, 0.0, 0.0));
	if (CanSeeExtent(Direction, ViewLocation, InActor, TraceType, EDrawDebugTrace::Type::None, HitLocation))
	{
		if (bDebug)
		{
			InActor->GetActorBounds(false, Origin, Extent);
			UKismetSystemLibrary::DrawDebugBox(InActor, Origin, Extent * 1.005, FLinearColor::Green,
				UE::Math::TRotator<double>::ZeroRotator, DebugDuration);
		}
		return ESenseResult::CanSee;
	}
	if (bDebug)
	{
		InActor->GetActorBounds(false, Origin, Extent);
		UKismetSystemLibrary::DrawDebugBox(InActor, Origin, Extent * 1.005, FLinearColor::Red,
			UE::Math::TRotator<double>::ZeroRotator, DebugDuration);
	}
	return ESenseResult::Blocked;
}
