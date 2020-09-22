// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaTimeSlowAbility.h"
#include "TopDownARPG.h"
#include "Engine/World.h"
#include "Triggers/TimeSlowSphere.h"


void UAreaTimeSlowAbility::Activate(AActor* Source)
{
	Super::Activate(Source);

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("UAreaTimeSlowAbility::Activate IsValid(World) == false"));
		//UE_LOG(LogTopDownARPG, Error, TEXT(" UAreaTimeSlowAbility::Activate IsValid(World) == false"));
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Source;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = Source->GetActorLocation() + Source->GetActorForwardVector() * 200.0f;

	AActor* TimeSlowSphere = World->SpawnActor<AActor>(TimeSlowSphereClass, SpawnLocation, Source->GetActorRotation(), SpawnParameters);
	if (IsValid(TimeSlowSphere) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("UAreaTimeSlowAbility::Activate IsValid(TimeSlowSphere) == false"));
		return;
	}
	
	OnActivateBlueprint(Source);
}
