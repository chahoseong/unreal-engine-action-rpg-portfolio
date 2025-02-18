# Combat System
## 구성 요소
### GameplayAbility
GameplayAbility를 통해서 캐릭터가 전투에서 수행하는 행동을 실행합니다.
### AnimMontage
Anim Montage를 통해 특정 타이밍에 Anim Notify를 발생시켜 로직을 실행합니다.
### CombatComponent
피격 애니메이션과 Hitbox를 정의하고 공격과 방어를 판정합니다.
### ComboSystemComponent
이전에 했던 공격에 대한 정보를 저장합니다.
### CombatTarget
공격 가능한 대상을 정의합니다.
### CombatWeapon
공격 범위, 소켓 위치등 전투를 진행할 때 필요한 속성과 함수를 정의합니다.
## 공격
![attack process](https://github.com/chahoseong/unreal-engine-action-rpg-portfolio/blob/main/Docs/Combat/Attack.png?raw=true)
## 콤보
![combo process](https://github.com/chahoseong/unreal-engine-action-rpg-portfolio/blob/main/Docs/Combat/Combo.png?raw=true)
## 피격
피격의 경우 GameplayEvent를 통해 GA_HitReact GameplayAbility를 실행합니다.
## 방어
![blocking process](https://github.com/chahoseong/unreal-engine-action-rpg-portfolio/blob/main/Docs/Combat/Block.png?raw=true)
패링(Parrying)의 경우에는 방어를 시작한 지 특정 시간 내에 공격을 받으면 발동합니다.
## 목표물 고정
목표물 고정(Target Lock)은 특정 대상에게 시점을 고정시키는 기능입니다. 그리고 마우스로
고정할 대상을 변경할 수 있습니다.
