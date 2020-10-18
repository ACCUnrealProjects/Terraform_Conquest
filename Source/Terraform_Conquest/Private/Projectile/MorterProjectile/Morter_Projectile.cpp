// Alex Chatt Terraform_Conquest 2020

#include "../../../Public/Projectile/MorterProjectile/Morter_Projectile.h"
#include "Kismet/GameplayStatics.h"

AMorter_Projectile::AMorter_Projectile()
{

}

// Called when the game starts or when spawned
void AMorter_Projectile::BeginPlay()
{
	AProjectile::BeginPlay();
}

void AMorter_Projectile::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AProjectile::HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), TArray<AActor*>(), this, Cast<APawn>(WhoShotMe)->GetController(), true, ECC_Visibility);
}
