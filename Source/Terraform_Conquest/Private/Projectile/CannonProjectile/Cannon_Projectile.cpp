// Alex Chatt Terraform_Conquest 2020

#include "../../../Public/Projectile/CannonProjectile/Cannon_Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACannon_Projectile::ACannon_Projectile()
{

}

// Called when the game starts or when spawned
void ACannon_Projectile::BeginPlay()
{
	AProjectile::BeginPlay();
}

void ACannon_Projectile::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AProjectile::HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
	UGameplayStatics::ApplyDamage(OtherActor, Damage, Cast<APawn>(WhoShotMe)->GetController(), WhoShotMe, UDamageType::StaticClass());
}
