// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
public:
	//Override the WasCollected function - Use impleentation because it's a blueprint native event
	void WasCollected_Implementation() override;

	//Public way to access the battery power level
	float GetPower() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Set the amount of power the battery gives to the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float m_batteryPower;
	
};
