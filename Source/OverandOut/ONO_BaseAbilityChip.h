// 1011Blueprints.

#pragma once

#include "CoreMinimal.h"
#include "DiffResults.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ONO_BaseAbilityChip.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class OVERANDOUT_API UONO_BaseAbilityChip : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UONO_BaseAbilityChip();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetRoot(USceneComponent* newroot);
	float MAxPowerShotTime1() const;
	void SetMAxPowerShotTime(float MAxPowerShotTime);
	USceneComponent* GetRoot();
	


	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot = nullptr;

private:
	
	// UPROPERTY(VisibleAnywhere, Category = "PowerShot")
	float MAxPowerShotTime = 0.0f;

	
};
