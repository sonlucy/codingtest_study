/*
* 
* 분기한정법으로 TSP 구현하기
* 작성자: 정보통신공학과 22012225 손보경
* 
* 
* 
* V: 모든 정점의 집합
* A: V의 부분집합
* D[vi][A]: A에 속한 각 정점을 한번씩만 거쳐서 vi에서 v1으로 가는 최단경로길이
* 
* <예시>
* D[v2][A={v3,v4}]= min(len[v2,v3,v4,v1], len[v2,v4,v3,v1])
*
* 따라서,
* 최적 일주 여행 경로 길이:
* D[v1][V-{v1}]= min_(2<=j<=n)(W[1][j]+D[vj][V-{v1,vj}])
* 이떄, W[1][j]+D[vj][V-{v1,vj}]: v1에서 vj로의 거리와 vj를 뺏을 때 거리 합
* 
* 일반적으로, i가 1이 아니고, vi가 A에 속하지 않을 때,
* D[vi][A]= min_(vj는 A에 속한다)(W[i][j]+D[vj][A-{vj}]) if A != 공집합
* D[vi][공집합] = W[i][1]
* 
* 
* Bound값 계산하고
* 탐색되어야하는 상태의 ㅈㅂ
* 
* bound값이 여행경로 길이의 하한(최소값)
* bound보다 최소여행경로의 길이가 더 크면 유망.
* 최소여행경로의 초기값은 infnite로 놓는다.
* 따라서 완전한 여행경로를 처음 얻을때까지는 bound < 최소여행경로의길이. 따라서 모든 노드는 유망
* 
* 각 노드의 bound값 구하는 방법: 지나쳐온 노드들의 길이 + 앞으로 가야할 노드들 중에 최소값 ( +가면 안되는 노드 조건 )
*                                                            ->유망하다면 실제 길이는 적어도 이 최소값보다는 큼
* 
*/

#include <iostream>
#include <queue>
using namespace std;
#define INF 1000000 
#define n 5 //노드의 수

int result[n + 1];
//int visited[n] = { 0 };  //방문한 노드인지 확인하기위한 배열. 
int minlength = INF;  //최소 여행경로 비용을 무한으로 초기화
int Mtrx[5][5] =
{
	{0, 14, 4, 10, 20},
	{14, 0, 7, 8, 7},
	{4, 5, 0, 7, 16},
	{11, 7, 9, 0, 2},
	{18, 7, 17, 4, 0}
};

struct NODE  
{
	int path[n+1];
	int level;  //level= 1... (n-1)  
				//만약 level=n-1이라면 노드1을 제외하고 방문하지 않은 단 하나의 노드 -> v1 로 path가 결정됨.
	
	int bound;
};

bool operator<(NODE v, NODE u)
{
	return v.bound < u.bound;
}



int bound(NODE v);
int length(NODE v);
NODE travel();
bool hasIn(int t, int k, NODE v);


bool hasIn(int t, int k, NODE v)
{
	if (t == 0)
	{
		for (int i = 0; i < v.level - 1; i++)
			if (v.path[i] == k)
				return true;
		return false;
	}
	else
	{
		for (int i = 0; i < v.level; i++)
			if (v.path[i] == k)
				return true;
		return false;
	}
}


NODE travel()
{
	NODE v, u;
	v.level = u.level = 1;
	v.path[0] = u.path[0]=  0;
	v.bound = bound(v);
	
	//priority_queue<int*> PQ;  ////////////////////
	priority_queue<NODE> PQ;  ////////////////////

	/*
	int result[n + 1];  //최적해의 노드를 담을 배열
	result[0] = 0; //result[n] = 0;  //출발노드와 도착노드는 첫번째 노드(0번 노드)로 설정
	//result[0],[1],[2],[3]까지 채워지면 더이상 뻗어나갈 필요없음. 
	//[4]는 출발지노드를 제외하고방문하지 않은 노드고 [5]는 출발지노드니까.
	*/
	int whNum = 0;
	//int notvisit;
	PQ.push(v);
	while (!PQ.empty())  //PQ가 비어있지않는동안 수행
	{
		whNum++;
		v = PQ.top();
		PQ.pop();

		if (v.bound < minlength)  //이 조건을 만족할 경우 v는 유망하므로 자식노드로 진입할 수 있음
		{
			///minlength = v.bound;
			u.level = v.level + 1;  //자식노드는 그 부모의 레벨 +1
			for (int i = 1; i < n; i++)
			{
				if (hasIn(1,i, v)) continue;
				for (int k = 0; k < v.level/*sizeof(v.path) / sizeof(int)*/; k++)
					u.path[k] = v.path[k];
				u.path[u.level - 1] = i; ////////방문하지않은 노드면 부모노드 복사한후 i노드 추가
					
				if (u.level == n - 1)  //level= 1...n-1
				{
					//방문하지 않은 남은 하나의 노드 추가하기위해
					//거쳐온 노드들의 합을 통해 빠진 노드를 찾는다.
					int sum = 0;
					int lasttravel;
					for (int x = 0; x < n-1; x++)
					{
						sum += u.path[x];  //0,1,2,3,4,0    
					}
					if (sum == 6)
						lasttravel = 4;
					else if (sum == 7)
						lasttravel = 3;
					else if (sum == 8)
						lasttravel = 2;
					else if (sum == 9)
						lasttravel = 1;
					else  //이 경우는 뭔가 잘못된건데,,
						lasttravel = 0;
					u.path[n-1] = lasttravel;
					/*for (int k = 1; k < n; k++)
					{
						if (!hasIn(1, k, u))    //방문하지 않은 단 하나의 노드를 추가
							u.path[n - 1] = k;  
					}*/
					u.path[n] = 0;  //첫번째노드가 도착노드

					if (length(u) < minlength)
					{
						minlength = length(u);
						for (int i = 0; i < n + 1; i++)
							result[i] = u.path[i];   ////////

					}
				}
				else
				{
					u.bound = bound(u);
					if (u.bound < minlength) //유망할경우
					{
						////////////////유망한 노드 u를 프라이오리티 큐에 넣어준다.
						PQ.push(u);
						
					}
				}

			}//end first for-loop


		}


	}//end while

	for (int i = 0; i < u.level + 2; i++)
		u.path[i] = result[i];

	return u;  ////

}

int bound(NODE v) 
{

	int min; 
	int bound;
	bound = length(v);  //이미 방문한 노드 길이
	//int nottravel = 0;
	//아직 방문하지않은 노드들에 대해 최소값 더해 bound값 구하기위해
	for (int i = v.level-1; i < n; i++)
	{
		if (hasIn(0,i, v)) continue;  
		min = INF;
		for (int j = 0; j < n; j++)
		{
			//1.대각선이거나, 2.이미 방문한 노드이거나, 3.v.path에서 마지막으로 방문한노드에서 가는 노드들 중 첫번째 노드의 경우는 제외
			if ((i == j)|| (hasIn(1, j, v)) || (j == 0 && i == v.path[v.level - 1]) ) continue; 
			if (min > Mtrx[i][j]) min = Mtrx[i][j];  //각각의 열을 돌다가 더 작은 값이 있다면 min값을 더 작은값으로 설정
		}
		bound += min;  //가장 작은 값을 bound에 더해줌
	}

	return bound;  //하한
}

int length(NODE v)
{
	int l = 0;
	
	if (v.level == n - 1)
	{
		for (int i = 0; i < n-1 ; i++)
		{

			l += Mtrx[v.path[i]][v.path[i + 1]];
		}
		l += Mtrx[v.path[n - 1]][0];
	}
	else
	{
		for (int i = 0; i < (v.level - 1); i++)
		{

			l += Mtrx[v.path[i]][v.path[i + 1]];
		}
	}

	
	return l;
}



void main()
{



	/*for (int i = 0; i < n; i++)
	{
		visited[i] = false;  //아직 방문하지 않았으므로 모든 노드들에 대해 false로
		//memset(visited, false, n)으로 해주어도됨.
	}
	visited[0] = true; //첫번째 노드를 출발지로 하여 이 노드를 방문한 노드로 선언*/

	/*int minimum_bound = INF;
	// level 1 
	minimum_bound = bound(0); //첫번째노드 -> 나머지 노드로 가는것중 가장 작은 가중치값
	//즉, v1->v3
	//next_index=3
	*/
	NODE u;  

	u = travel();
	minlength = length(u);
	cout << "최종 거리 : " << minlength;
	cout << "\n최종 경로:";
	for (int i = 0; i < u.level + 1; i++)
		//cout << result[i] +1 << "->";
		cout << u.path[i] + 1 << "->";
	//cout << result[u.level + 1]+1;
	cout << u.path[u.level + 1] + 1;

	
}