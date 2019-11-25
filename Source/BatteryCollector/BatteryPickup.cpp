// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"
#include "Components/StaticMeshComponent.h"

// Called when the game starts or when spawned
void ABatteryPickup::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetSimulatePhysics(true);

	//The base power level of the battery
	m_batteryPower = 150.f;
}

void ABatteryPickup::WasCollected_Implementation()
{
	//Use base pickup behaviour
	Super::WasCollected_Implementation();
	//Destroy the battery
	Destroy();
}

//Report the power level of the battery
float ABatteryPickup::GetPower() const
{
	return m_batteryPower;
}