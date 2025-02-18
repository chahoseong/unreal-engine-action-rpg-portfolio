# Equipment System
## Diagram
![diagram]()
## 구성 요소
### EquipmentManagerComponent
장비의 장착과 해제 요청을 처리하고, 현재 착용된 장비들을 관리합니다.
### EquipmentInstance
장비의 속성을 정의하고 장비가 장착되거나 해제될 때 적용할 기능들을 관리합니다.
### EquipmentFeature
장비가 장착되거나 해제될 때 적용할 기능을 정의합니다.
## 장비 착용 방식
- 액터를 생성해서 소켓에 붙이는 방식
- 매쉬를 불러와서 캐릭터와 합치는 방식
장비를 착용하는 방식은 **액터를 생성해서 소켓에 붙이는 방식**과 
**메쉬를 불러와서 캐릭터와 합치는 방식**이 있습니다.
## 장비 착용 부위 (Slot)
장비를 착용할 수 있는 부위는 GameplayTag로 정의합니다. 이 프로젝트의 모든 GameplayTag는
SwordmasterGameplayTags에 정의되어 있습니다.
## Weapon
무기(Weapon)는 장비의 일종으로 EquipmentManagerComponent에서 관리합니다. 다만 무기만의
몇 가지 특별한 속성과 기능이 있습니다.
### 구성 요소
#### WeaponInstance
무기의 속성을 정의하고 무기가 장착되거나 해제될 때 적용할 기능들을 관리합니다.
#### WeaponFeature
무기가 장착되거나 해제될 때 적용할 기능을 정의합니다.
#### WeaponActor (Blueprint)
블루프린트 클래스로 월드 상에 표현할 메쉬를 정의합니다.
#### Ability Set
무기를 착용하면 캐릭터가 사용할 수 있는 능력(Ability)들을 정의합니다.
### Input
무기를 장착하면 무기에 맞는 InputMappingContext를 추가합니다(WeaponInstance에 등록되어 있음).
이를 통해서 무기를 장착했을 때 얻은 능력들을 적절한 입력에 따라 실행할 수 있습니다.