// Fill out your copyright notice in the Description page of Project Settings.


#include "FallThroughAtmosphere.h"

// Sets default values for this component's properties
UFallThroughAtmosphere::UFallThroughAtmosphere()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFallThroughAtmosphere::BeginPlay()
{
	Super::BeginPlay();

	lastKnownPosition = GetComponentTransform().GetLocation();
}


// Called every frame
void UFallThroughAtmosphere::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UFallThroughAtmosphere::CalculateAccelleration(const FVector& currentPosition, float deltaTime) const
{
	float weight = CalculateWeight();
	FVector positionMeters = currentPosition / 100.f;
	FVector speed = CalculateSpeed(positionMeters, deltaTime);
	float drag = CalculateDrag(speed);
	return ((weight - drag) / mass) * 100.f;
}

FVector UFallThroughAtmosphere::CalculateSpeed(const FVector& currentPosition, float deltaTime) const
{
	FVector returnVal;
	FVector lastKnownPositionMetres = lastKnownPosition / 100.f;
	returnVal.X = abs((currentPosition.X - lastKnownPositionMetres.X)) / deltaTime;
	returnVal.Y = abs((currentPosition.Y - lastKnownPositionMetres.Y)) / deltaTime;
	returnVal.Z = abs((currentPosition.Z - lastKnownPositionMetres.Z)) / deltaTime;
	return returnVal;
}

float UFallThroughAtmosphere::CalculateDrag(const FVector& velocity) const
{ 
	float frontalAreaMsqr = frontalArea / 10000;
	return dragCoefficient * frontalAreaMsqr * 0.5 * airDensity * (velocity.Z * velocity.Z);
}

