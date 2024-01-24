### ✏️작성자: 손보경 (shson2280@gmail.com)
### ✒️최종코드 수정일: 2022-05-08
## 🤡 다익스트라 알고리즘으로 경산<->서울 최단경로 찾기<br><br>
<br><br>


  
![image](https://github.com/sonlucy/codingtest_study/assets/86239847/8d89e33d-02f5-40d4-8bcf-2d53bc43b371)
- 📌실행결과<br><br>

![image](https://github.com/sonlucy/codingtest_study/assets/86239847/31011421-1d08-4887-8aa5-a9b5053d5954)
- 위와 같이 노드를 설정하였고 이에 따른 가중치 그래프 2차원 배열 W가 오른쪽과 같음<br><br>

![image](https://github.com/sonlucy/codingtest_study/assets/86239847/0ec5baab-db4c-4fd2-9e85-ad471573a56f)
- 경로 출력을 위해서 touch 배열의 end번째 요소 -> 그 요소번째의 요소 -> ... 식으로 하여 print배열에 차례로 담았음. 이 print배열을 거꾸로 출력하여 경로를 출력하였음
그리고 최종 최단거리는 length[end]에 담긴 녀석(강의자료 예시로 보면 5)이라 이를 출력하였음
