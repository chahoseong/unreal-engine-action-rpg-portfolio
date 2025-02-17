# Unreal Engine Action Rpg Portfolio

## Equipment System
### 구성 요소
#### EquipmentManagerComponent
장비의 장착과 해제 요청을 처리하고, 현재 착용된 장비들을 관리합니다.
#### EquipmentInstance
장비의 속성과 장비가 장착되거나 해제될 때, 적용할 기능을 관리합니다.
#### EquipmentFeature
장비가 장착되거나 해제될 때, 적용되는 기능을 정의합니다.
### 장비 착용 방식

- 액터를 생성해서 소켓에 붙이는 방식
- 메쉬를 불러와서 캐릭터와 합치는 방식 (CharacterPartsManagerComponent)

장비를 착용하는 방식은 **액터를 생성해서 소켓에 붙이는 방식**과 **메쉬를 불러와서 캐릭터와 합치는 방식**이 있습니다. 두 번째 방식의 경우 **CharacterPartsManagerComponent**에서 처리를 합니다.
### 장비 착용 부위 (Slot)
장비를 착용할 수 있는 부위는 **GameplayTag**로 정의합니다.
### 무기(Weapon)
무기는 장비의 일종으로 EquipmentManagerComponent에서 관리합니다. 다만 무기만의 몇 가지 특별한 속성과 기능이 있습니다.
#### 구성 요소
##### WeaponInstance
무기의 속성과 무기가 장착되거나 해제될 때, 적용할 기능을 관리합니다.
##### WeaponFeature
무기가 장착되거나 해제될 때, 적용되는 기능을 정의합니다.
##### WeaponActor (Blueprint)
블루프린트 클래스로, 월드 상에 표현할 메쉬를 정의합니다.
##### Ability Set
무기를 착용하면 캐릭터가 사용할 수 있는 어빌리티들을 정의합니다. 
#### 무기 장착
무기를 장착하면 WeaponInstance에 등록된 InputMappingContext가 적용됩니다. 이를 통해서 무기를 장착했을 때 얻은 Ability를 적절한 입력에 따라 실행할 수 있습니다.
