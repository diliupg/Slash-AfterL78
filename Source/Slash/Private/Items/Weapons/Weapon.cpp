// EMorphus Software 2022


#include "Items/Weapons/Weapon.h"
#include "Characters/SlashCharacter.h"

void AWeapon::Equip( USceneComponent* InParent, FName SocketName )
{
	FAttachmentTransformRules TransformRules( EAttachmentRule::SnapToTarget, true );
	ItemMesh->AttachToComponent(InParent, TransformRules, SocketName);

	ItemState = EItemState::EIS_Equipped;
}

void AWeapon::OnSphereOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	Super::OnSphereOverlap( OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult );


}

void AWeapon::OnSphereEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	Super::OnSphereEndOverlap( OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex );
}
