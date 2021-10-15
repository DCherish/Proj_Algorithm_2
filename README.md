---

<div align="center">

 💜 *Algorithm Project 1*

</div>

---

# 🧐 프로젝트 목표
- **문자열 탐색 알고리즘** 중 2가지의 알고리즘을를 구현하여 서로 간의 성능을 분석  
  - `KMP Algorithm` `Boyer-Moore Algorithm`  

# 👨‍💻 사용 기술 Stack
- [x] Visual Studio  

# 💛 프로젝트 결과 (간략)
<img src="/image/d1.png" width="700px" height="400px" alt="BlockDiagram"></img><br/><br/>
<img src="/image/d2.png" width="450px" height="390px" alt="BlockDiagram"></img><br/>
> **KMP Algorithm**과 **Boyer-Moore Algorithm**을 서로 비교 및 분석한 결과 (데이터 개수 및 실행시간)  

👉 **Boyer-Moore Algorithm < KMP Algorithm**  
👉 각각의 **실행 시간**은 **발생 횟수**와 **패턴의 길이**에 따라 결정  
👉 일반적으로, **Boyer-Moore Algorithm**이 **KMP Algorithm**에 비해 성능이 좋다는 것을 확인  

---

<img src="/image/d3.png" width="700px" height="200px" alt="BlockDiagram"></img><br/><br/>
<img src="/image/d4.png" width="420px" height="380px" alt="BlockDiagram"></img><br/>
> **Worst Case**에서 비교 및 분석한 결과 (데이터 개수 및 실행시간)  


👉 **Boyer-Moore Algorithm > KMP Algorithm**  
👉 메모장에 텍스트가 D로 꽉 차있는 경우에서 패턴을 ZDDDDD로 입력하여 **찾지 못하는 최악의 경우**를 실행  
👉 그 결과, **KMP Algorithm**이 **Boyer-Moore Algorithm**에 비해 성능이 좋다는 것을 확인
