# Monitor-Input-lag-tester
- Development tool: C++ / Qt5, Arduino

## 어떠한 작업을 수행하는 시스템인가요?
- 모니터 인풋렉(Input Lag) 측정 시스템

***이해하기 쉽도록 모니터 인풋렉이란 표현을 사용하였지만, 실제 측정되는 인풋렉 딜레이는 전체 PC 시스템의 환경에 영향을 받을 수 있습니다.***

모니터의 인풋렉에 대한 정확한 지식이 없어 구글을 통한 사전 검색을 진행한 결과, "어떠한 기기(보통 마우스와 키보드)의 인풋 시그널이 시리얼 포트로 전달되고 이는 그래픽 카드를 거쳐 변경된 사항이 모니터에 뿌려진다."라고 이해를 하였습니다. 따라서, 이는 모니터 만의 자체 Lag이 아닌 전체 PC 시스템의 Lag인 것을 알 수 있습니다. 그러므로 해당 모니터 인풋렉 테스터를 통해 측정된 지연 시간은 전체적인 PC 시스템이 고정되어 있는 상황에서 모니터만 변경하여 상대적인 지연 시간을 측정하는 것을 목적으로 합니다.
(모니터 자체의 인풋렉이 아님을 강조합니다.)

## 간단소개
한 스트리머(~~눈쟁이님~~)분께서 아두이노를 이용해 모니터의 인풋렉을 측정하고자 하는 프로젝트를 진행중에 있었고, 흥미를 느껴 자그마한 도움이라도 되고자 개인적으로 간단한 프로젝트를 진행해보았습니다. 

프로젝트를 위해 조도센서 및 스위치를 이용한 간단한 회로를 구성하였고, 인풋 시그널에 반응하기 위한 GUI를 개발하였습니다.

개인적인 흥미로 진행한 간단한 프로젝트로, 관련 프로젝트 진행 및 결과를 궁금해하시는 분들께 자그마한 도움이 되었으면 합니다.

## 주요내용
동작의 원리는 다음과 같습니다.
~~~
1. 조도센서가 연결된 아두이노를 GUI의 검은색으로 표시된 위젯에 근접시킨 뒤, 인풋 시그널을 입력(스위치 클릭) -> 타이머 동작
2. 인풋 시그널이 시리얼 포트를 통해 PC로 전달되면 위젯의 색깔을 검정에서 흰색으로 변경함
3. 모니터의 밝기가 바뀔 경우 타이머를 종료하며 현재까지 소요된 시간을 계산
4. 아두이노에 연결된 LCD를 통해 소요 시간을 출력
~~~

사용과 관련한 참고 영상: https://www.youtube.com/watch?v=6UEavnn4ERA

## 테스트 결과
연구실에 비치된 두 대의 모니터(BENQ EW2775ZH, DELL E2209W)를 테스트를 진행하였으며 진행 결과 BENQ EW2775ZH가 연결된 PC 시스템에서는 약 66 ms의 지연시간 그리고 DELL E2209가 연결된 PC 시스템에서는 약 82 ms의 지연시간을 측정하였습니다. (해당 결과는 Pic 폴더에서 직접 확인할 수 있습니다.) 16 ms의 지연시간이 과연 일반사용자에게 얼마나 큰 차이를 줄 수 있는지는 잘 모르겠지만, 반응속도가 중요한 프로게임 분야에서는 상당히 중요한 의미를 가질 수도 있다는 생각이 들었습니다.


