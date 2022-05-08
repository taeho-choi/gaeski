# 개스키 (C++/OpenGL)


### 지원 플랫폼

- PC

### 프로젝트 소개

- 한국공학대학교 게임공학과의 커리큘럼인 ‘컴퓨터 그래픽스’ 과목을 수강하며 제작한 프로젝트입니다.
- C++을 기반으로 OpenGL 라이브러리를 사용하여 개발하였습니다.
- 클라이언트 개발 담당 2인 팀을 구성하여 진행한 첫 협업 프로젝트입니다.

### 시연 영상

[https://youtu.be/EU-EF-leQUg](https://youtu.be/EU-EF-leQUg)

# 기획 내용


떠돌이 강아지 돌돌이가 너무 스키가 타고 싶어 사람들이 모두 자  밤에 몰래 스키를 타는 게임입니다. 스키장에는 나무, 자석, 유령, 달팽이, 코인과 같은 장애물 및 아이템이 있습니다. 최대한 코인을 많이 획득하며 목적지까지 도달하는 것이 목표입니다.

마우스 입력

`게임 시작 버튼 클릭 : 게임 시작`

키보드 입력

`a,d : 캐릭터 좌/우 이동`

`q : 프로그램 종료`

# 맡은 역할


- 곡선 맵 구현 및 객체 배치
- 자석 아이템 효과 구현
- 유령 아이템 효과 구현
- 텍스쳐 적용
- 조명 적용
- 점수 배점 및 출력

# 구현 내용


- Sin 곡선을 이용하여 스키장의 경로를 그리고 코인들을 배치하였습니다.
- 픽셀 쉐이더에서 조명 코드를 적용하여 3차원 공간감을 더했습니다.
- 캐릭터나 로고의 이미지를 직접 제작하고, Polygon들에 텍스쳐를 적용하여 이미지를 렌더링하였습니다.
- 자석 아이템 획득 시 일정 시간 동안 캐릭터에게 가까워진 코인을 자석처럼 끌어당기는 물리 효과를 구현하였습니다. 코인 객체가 지정된 범위 내로 들어왔을 경우 매 프레임마다 캐릭터와 코인의 거리에 따라 감속하며 가까워지게 하였습니다.
- 유령 아이템 획득 시 일정 시간 동안 GL_BLEND를 활성화하고 알파 값을 조정하여 캐릭터를 불투명하게 만들고, 나무와의 충돌체크가 이루어지지 않게 하였습니다.
