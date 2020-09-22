// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeSlowSphere.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine.h"
#include "TopDownARPG.h"
#include "TopDownARPGCharacter.h"
#include "Engine/World.h"

// Sets default values
ATimeSlowSphere::ATimeSlowSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	
	//set collision
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	
	//declare overlap events
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATimeSlowSphere::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ATimeSlowSphere::OnOverlapEnd);

	SpeedFactor = 0.70f;
	//Getter for the cached world pointer, will return null if the actor is not actually spawned in a level
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("ATimeSlowSphere::ATimeSlowSphere IsValid(World) == false"));
		return;
	}

	AreaTimerManager = &World->GetTimerManager();
	AreaTimerManager->SetTimer(AreaCooldownTimerHandle, this, &ATimeSlowSphere::OnCooldownTimerExpired, AreaCooldownTimeDilation, true, AreaCooldownTime);
	bIsOffCooldown = false;


}
void ATimeSlowSphere::OnCooldownTimerExpired()
{
	bIsOffCooldown = true;
	
}


// Called when the game starts or when spawned
void ATimeSlowSphere::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
		
		SlowedActors.Add(OtherActor);

		SlowedActorsInitialSpeed.Add(OtherActor->CustomTimeDilation);

		OtherActor->CustomTimeDilation -= SpeedFactor;

	}
}

void ATimeSlowSphere::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));

		OtherActor->CustomTimeDilation += SpeedFactor;
	}
}
// Called every frame
void ATimeSlowSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ATimeSlowSphere::BeginDestroy()
{
	if (AreaTimerManager)
	{
		AreaTimerManager->ClearTimer(AreaCooldownTimerHandle);
		AreaTimerManager = nullptr;
	}

	Super::BeginDestroy();
}

