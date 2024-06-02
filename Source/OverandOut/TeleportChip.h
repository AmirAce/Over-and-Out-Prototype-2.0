// 1011Blueprints.

#pragma once

#include "CoreMinimal.h"
#include "ONO_BaseAbilityChip.h"
#include "TeleportChip.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OVERANDOUT_API UTeleportChip : public UONO_BaseAbilityChip
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTeleportChip();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TeleportChipMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	float MyMaxPowerShotTime = 0.0f;
};
