# Character Parts System
## Diagram
![diagram]()
## 구성 요소
### CharacterPartsManagerComponent
캐릭터 파츠를 변경하는 요청을 받고, 변경된 파츠를 관리합니다.
### GameplayTags::Character.Parts
변경 가능한 캐릭터 파츠는 GameplayTag로 정의합니다.
### CharacterPartsRow
캐릭터 파츠의 속성을 정의합니다.
## 캐릭터 파츠 교체 방식
캐릭터 파츠는 SkeletalMergingLibrary  로 메쉬를 병합하는 방식을 사용합니다.