// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FallThroughAtmosphere.generated.h"

/*
	Calulates effects of falling through atmosphere.
	Assumes falling on z axis
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALLING_API UFallThroughAtmosphere : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFallThroughAtmosphere();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Falling")
		float mass = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Falling")
		float gravity = 9.8; //default to earth gravity, but allow this value to change if the user wants

		/*Need to know the drag coefficient (dc) to calculate drag, and attempting to rearrange to calcualte
		  the dc needs to  know drag. Usually the dc is calculated via real world experimentation.
		  So this dc value should be passed in from a known value for the attached shape
		  drag coefficient of a cube as default*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Falling")
		float dragCoefficient = 0.8;

	//default for eaith air density
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Falling")
		float airDensity = 1.2;

	/*
		Frontal area is different for any shape, and is related to the dc value. This will also need to be user provided
		Many useful examples here https://www.engineeringtoolbox.com/drag-coefficient-d_627.html
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Falling")
	float frontalArea;

	UPROPERTY(BlueprintReadWrite, Category = "Falling")
	FVector lastKnownPosition;

	UFUNCTION(BlueprintCallable, Category = "Falling")
	float CalculateAccelleration(const FVector& currentPosition, float deltaTime) const;

private:
	//returns speed in each x, y, y direction 
	FVector CalculateSpeed(const FVector& currentPosition, float deltaTime) const;
	inline float CalculateWeight() const { return mass * gravity; }
	float CalculateDrag(const FVector& velocity) const;

	
};
