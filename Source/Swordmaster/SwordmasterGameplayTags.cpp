#include "SwordmasterGameplayTags.h"

namespace SwordmasterGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Gameplay_NativeInputBlocked, "Gameplay.NativeInputBlocked");
	UE_DEFINE_GAMEPLAY_TAG(Gameplay_AbilityInputBlocked, "Gameplay.AbilityInputBlocked");
	UE_DEFINE_GAMEPLAY_TAG(Gameplay_InteractionAbilityBlocked, "Gameplay.InteractionAbilityBlocked");

	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Attacking, "Character.Status.Attacking");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Attacking_Light, "Character.Status.Attacking.Light");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Attacking_Heavy, "Character.Status.Attacking.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Defending, "Character.Status.Defending");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Parryable, "Character.Status.Parryable");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Rolling, "Character.Status.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_TargetLocked, "Character.Status.TargetLocked");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Stunning, "Character.Status.Stunning");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Invincible, "Character.Status.Invincible");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Dead, "Character.Status.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Interacting, "Character.Status.Interacting");

	UE_DEFINE_GAMEPLAY_TAG(Combat_Status_Hit, "Combat.Status.Hit");

	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack_Light, "Character.Ability.Attack.Light");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack_Heavy, "Character.Ability.Attack.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack_Blocked, "Character.Ability.AttackBlocked");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_HitReact, "Character.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Knockdown, "Character.Ability.Knockout");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Roll, "Character.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Defend, "Character.Ability.Defend");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Parry, "Character.Ability.Parry");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_TargetLock, "Character.Ability.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Interact, "Character.Ability.Interact");

	UE_DEFINE_GAMEPLAY_TAG(Character_Part, "Character.Part");

	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot, "Equipment.Slot");
	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_Head, "Equipment.Slot.Head");
	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_Chest, "Equipment.Slot.Chest");
	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_Hands, "Equipment.Slot.Hands");
	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_Legs, "Equipment.Slot.Legs");
	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_Feet, "Equipment.Slot.Feet");
	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_MainHand, "Equipment.Slot.MainHand");
	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_OffHand, "Equipment.Slot.OffHand");
	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_Back, "Equipment.Slot.Back");

	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Strength, "Attribute.Primary.Strength");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Intellect, "Attribute.Primary.Intellect");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Agility, "Attribute.Primary.Agility");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Will, "Attribute.Primary.Will");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_MaxHealth, "Attribute.Secondary.MaxHealth");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_MaxStamina, "Attribute.Secondary.MaxStamina");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_Health, "Attribute.Vital.Health");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_Stamina, "Attribute.Vital.Stamina");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Combat_WeaponDamage, "Attribute.Combat.WeaponDamage");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Combat_Armor, "Attribute.Combat.Armor");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Combat_Knockdown, "Attribute.Combat.Knockdown");

	UE_DEFINE_GAMEPLAY_TAG(Input, "Input");
	UE_DEFINE_GAMEPLAY_TAG(Input_Move, "Input.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Look, "Input.Look");
	UE_DEFINE_GAMEPLAY_TAG(Input_LightAttack, "Input.LightAttack");
	UE_DEFINE_GAMEPLAY_TAG(Input_HeavyAttack, "Input.HeavyAttack");
	UE_DEFINE_GAMEPLAY_TAG(Input_Roll, "Input.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Input_Defend, "Input.Defend");
	UE_DEFINE_GAMEPLAY_TAG(Input_TargetLock, "Input.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Input_SwitchTarget, "Input.SwitchTarget");
	UE_DEFINE_GAMEPLAY_TAG(Input_Inventory, "Input.Inventory");
	UE_DEFINE_GAMEPLAY_TAG(Input_Interact, "Input.Interact");

	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_WeaponDamageEnabled, "GameplayEvent.WeaponDamageEnabled");
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_WeaponDamageDisabled, "GameplayEvent.WeaponDamageDisabled");
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_AttackComboEnabled, "GameplayEvent.AttackComboEnabled");
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_AttackComboDisabled, "GameplayEvent.AttackComboDisabled");
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_AttackHit, "GameplayEvent.AttackHit");
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_AttackBlocked, "GameplayEvent.AttackBlocked");
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_ParryAttack, "GameplayEvent.ParryAttack");
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_HitReact, "GameplayEvent.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_Knockout, "GameplayEvent.Knockout");

	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_SwitchTarget_Left, "GameplayEvent.SwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_SwitchTarget_Right, "GameplayEvent.SwitchTarget.Right");

	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_EquipItem, "GameplayEvent.EquipItem");
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_CommitAbility, "GameplayEvent.CommitAbility");
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_CommitAbility_Cost, "GameplayEvent.CommitAbility.Cost");
}
