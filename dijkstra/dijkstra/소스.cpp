/*
- 작성자: 정보통신공학과 22012225 손보경
- Dijkstra 알고리즘으로 경산<->서울 최단경로 찾기

*/

#include <stdio.h>
#include <iostream>
using namespace std;

#define INF 1000000  //테이블 초기화할때 무한으로 설정해주고 시작하기위해 임의로 백만의 큰 값으로 설정
#define n 12 //노드(도시) 수
//#define m //간선의 수

int W[12][12] =  //간선의 가중치를 담은 2차원 배열
{
	{0, 3, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF},
	{7, 0, INF, 1, INF, INF, INF, INF, INF, INF, INF, INF},
	{3, INF, 0, INF, INF, 3, INF, INF, INF, INF, INF, INF},
	{INF, 3, INF, 0, 4, INF, INF, INF, INF, INF, INF, INF},
	{13, INF, INF, 3, 0, 1, INF, INF, 2, INF, INF, INF},
	{INF, INF, 5, INF, 2, 0, INF, INF, 5, INF, INF, INF},
	{INF, INF, INF, 5, INF, INF, 0, 3, 5, 3, INF, INF},
	{INF, INF, INF, INF, 6, INF, 6, 0, INF, INF, 1, 2},
	{INF, INF, INF, INF, 2, 3, 5, 3, 0, INF, INF, 3},
	{INF, INF, INF, INF, INF, INF, 3, 6, INF, 0, 5, INF},
	{INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, 0, 3},
	{INF, INF, INF, INF, INF, INF, INF, INF, 1, INF, 2, 0},
};

int visited[n];  //방문한 노드인지 확인하기위한 배열. 
int touch[n];  
int length[n]; //현노드에서 갈 수 있는 노드들의 가중치들로 갱신 . 이미 방문완료된 노드는 -1의 가중치를 갖게함.




void dijkstra(int start, int end)
{

	for (int i = 0; i < n; i++)
	{
		visited[i] = false;  //아직 방문하지않았으므로 false으로 초기화
		touch[i] = start; //처음 초기화값은 출발지노드번호로.
		length[i] = W[start][i];  //출발지 노드에서 나머지 노드들로 가는 가중치로 초기화
	}
	visited[start] = true;  //출발지를 방문한 노드로 표시
	
	for (int i = 0; i < n; i++)
	{
		int near_node = 100;
		int min = INF + 1;
		//방문하지 않은 노드 중에서 가장 가까운 노드 선택
		for (int j = 0; j < n - 1; j++)  
		{
			//방문하지 않은 노드 중에서, legnth[j]는 양수여야하고, 그 중 min보다 더 작은 length[j]가 있으면
			if ((length[j] >= 0) && (length[j] < min) && (visited[j] == false))
			{
				min = length[j];  //min보다 더 작은 가중치를 가진 length[j]를 min으로 바꿔주고
				near_node = j; //인접한 노드를 j로 바꿔줌.
			}// 계속해서 i번 노드로의 가중치와 min을 비교해가며 가장 비용이 작은 노드를 찾는다.
		}  //위 for-loop이 끝난 후 near_node가 방문하지않은 노드 중 가장 가까운 노드 번호임.
		visited[near_node] = true;  //방문하지 않은 노드 중 가장 가까운 노드를 방문한 노드로 표시

		for (int j = 0; j < n; j++)
		{
			
			if (visited[j] != true)  //방문하지않은 노드 중에서만 수행하도록 함
			{
				if (length[near_node] + W[near_node][j] < length[j])  //원래 가중치보다 현재노드를 거쳐서 가는게 가중치가 더 작은 경우
				{
					length[j] = length[near_node] + W[near_node][j];  //더 작은 가중치를 가지는 노선으로 재정의
					touch[j] = near_node;
				}
			}

		}

	}

	/* 경로 출력 */
	cout << "▶최단경로 : " << start;
	int i = end;  //touch배열을 뒤에서부터
	int N = 0;
	int print[n];
	while (1)
	{
		print[N++] = touch[i];  
		i= touch[i];
		
		if (touch[i] == start)
		{
			break;
		}
	}
	
	for (int i = N-1; i >= 0 ; i--)
	{
		cout << " -> " << print[i];  //print배열 거꾸로 출력
	}
	cout << " -> " << end;

	/* 최단 길이 출력 */
	cout << endl << "▶최종 최단 거리: " << length[end] << endl << endl;


}

void main()
{
	int start, end;
	cout << "<<<<다익스트라 알고리즘>>>> " << endl << endl;
	
	/*
	cout << " 서울(0) 인천(1) 강릉(2) 천안(3) 청주(4) 동해(5) 대전(6) 대구(7) 울진(8) 광주(9) 부산(10) 경산(11) " << endl;
	cout << "탐색할 두 도시의 노드번호를 입력하시오. (e.g. 1 4 ):" << endl;
	cin >> start >> end;
	dijkstra(start, end);
	*/

	cout << "경산 -> 서울" << endl;
	dijkstra(11, 0);

	cout << "서울 -> 경산 " << endl;
	dijkstra(0, 11);
	


}