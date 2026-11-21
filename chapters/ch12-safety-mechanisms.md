# 12장. Software safety mechanism

## 장 계획

| 항목 | 내용 |
|---|---|
| Part | III. 안전한 소프트웨어 만들기 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 미착수 |

### 핵심 질문

고장을 제때 감지하고 반응하는 구체적 수단은 무엇인가?

### 다룰 내용

- watchdog (window 방식, 질의-응답 방식)과 program flow monitoring
- end-to-end 통신 보호: CRC, sequence counter, timeout
- memory protection과 stack 감시
- 입력 타당성 검사: range check, plausibility check, 센서 간 비교
- 중요 데이터의 중복 저장
- error handling 전략과 fault reaction
- safety mechanism 자체의 고장과 그 검사
- 로봇과 드론에서는 (단계 3에서 채운다)

### 예제 산출물

safety mechanism 구현, mechanism마다 덮는 fault 목록

### 근거

ISO 26262-6; IEC 61508-7; AUTOSAR 공개 문서

## 본문

아직 쓰지 않았다.
