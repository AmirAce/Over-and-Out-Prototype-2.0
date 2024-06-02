// 1011Blueprints.


#include "TeleportChip.h"


// Sets default values for this component's properties
UTeleportChip::UTeleportChip()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	Super::SetMAxPowerShotTime(MyMaxPowerShotTime);
}


// Called when the game starts
void UTeleportChip::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UTeleportChip::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



//
// UStaticMeshComponent* GetMeshComponent()
// {
// 	// Cast the DefaultRoot to UStaticMeshComponent
// 	// UONO_BaseAbilityChip::SetRoot(UTeleportChip::Mesh);
//
// 	if (MeshComponent)
// 	{
// 		// The cast was successful, return the MeshComponent
// 		return MeshComponent;
// 	}
// 	else
// 	{
// 		// Handle the case where the cast failed (e.g., DefaultRoot is not a UStaticMeshComponent)
// 		return nullptr;
// 	}
// }

