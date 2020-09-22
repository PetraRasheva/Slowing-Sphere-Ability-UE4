// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeSlowSphere.generated.h"

UCLASS()
class TOPDOWNARPG_API ATimeSlowSphere : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		float AreaCooldownTime = 10.f;

	UPROPERTY(EditAnywhere)
		float AreaCooldownTimeDilation = 1.f;

	UPROPERTY(EditAnywhere)
		// crate tarray for slowed actors
		TArray<AActor*> SlowedActors;

	UPROPERTY(EditAnywhere)
		// crate tarray 
		TArray<float> SlowedActorsInitialSpeed;

	UPROPERTY(EditAnywhere)
		float SpeedFactor;
		//FVector SpeedFactor;
	
public:	
	// Sets default values for this actor's properties
	ATimeSlowSphere();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Gameplay)
		class USphereComponent* SphereComponent;

	//----TO DO------
	UPROPERTY(VisibleAnywhere, Category = Visual)
		class UParticleSystemComponent* OnOverlapParticle;

	// declare overlap begin function
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		bool IsOffCooldown() const { return bIsOffCooldown; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy() override;
	
private:
	bool bIsOffCooldown = true;
	FTimerManager* AreaTimerManager = nullptr;
	FTimerHandle AreaCooldownTimerHandle;
	void OnCooldownTimerExpired();

};

