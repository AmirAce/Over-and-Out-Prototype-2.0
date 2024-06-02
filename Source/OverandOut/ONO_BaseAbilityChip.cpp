// 1011Blueprints.


#include "ONO_BaseAbilityChip.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values for this component's properties
UONO_BaseAbilityChip::UONO_BaseAbilityChip()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Defualt Root"));
	// ...	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 3000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
}


// Called when the game starts
void UONO_BaseAbilityChip::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UONO_BaseAbilityChip::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UONO_BaseAbilityChip::SetRoot(USceneComponent* newroot)
{
	this->DefaultRoot = newroot;
}


float UONO_BaseAbilityChip::MAxPowerShotTime1() const
{
	return MAxPowerShotTime;
}

void UONO_BaseAbilityChip::SetMAxPowerShotTime(float AMAxPowerShotTime)
{
	AMAxPowerShotTime = MAxPowerShotTime;
}



