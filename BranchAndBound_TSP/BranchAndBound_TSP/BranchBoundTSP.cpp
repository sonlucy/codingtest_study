/*
* 
* �б����������� TSP �����ϱ�
* �ۼ���: ������Ű��а� 22012225 �պ���
* 
* 
* 
* V: ��� ������ ����
* A: V�� �κ�����
* D[vi][A]: A�� ���� �� ������ �ѹ����� ���ļ� vi���� v1���� ���� �ִܰ�α���
* 
* <����>
* D[v2][A={v3,v4}]= min(len[v2,v3,v4,v1], len[v2,v4,v3,v1])
*
* ����,
* ���� ���� ���� ��� ����:
* D[v1][V-{v1}]= min_(2<=j<=n)(W[1][j]+D[vj][V-{v1,vj}])
* �̋�, W[1][j]+D[vj][V-{v1,vj}]: v1���� vj���� �Ÿ��� vj�� ���� �� �Ÿ� ��
* 
* �Ϲ�������, i�� 1�� �ƴϰ�, vi�� A�� ������ ���� ��,
* D[vi][A]= min_(vj�� A�� ���Ѵ�)(W[i][j]+D[vj][A-{vj}]) if A != ������
* D[vi][������] = W[i][1]
* 
* 
* Bound�� ����ϰ�
* Ž���Ǿ���ϴ� ������ ����
* 
* bound���� ������ ������ ����(�ּҰ�)
* bound���� �ּҿ������� ���̰� �� ũ�� ����.
* �ּҿ������� �ʱⰪ�� infnite�� ���´�.
* ���� ������ �����θ� ó�� ������������ bound < �ּҿ������Ǳ���. ���� ��� ���� ����
* 
* �� ����� bound�� ���ϴ� ���: �����Ŀ� ������ ���� + ������ ������ ���� �߿� �ּҰ� ( +���� �ȵǴ� ��� ���� )
*                                                            ->�����ϴٸ� ���� ���̴� ��� �� �ּҰ����ٴ� ŭ
* 
*/

#include <iostream>
#include <queue>
using namespace std;
#define INF 1000000 
#define n 5 //����� ��

int result[n + 1];
//int visited[n] = { 0 };  //�湮�� ������� Ȯ���ϱ����� �迭. 
int minlength = INF;  //�ּ� ������ ����� �������� �ʱ�ȭ
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
				//���� level=n-1�̶�� ���1�� �����ϰ� �湮���� ���� �� �ϳ��� ��� -> v1 �� path�� ������.
	
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
	int result[n + 1];  //�������� ��带 ���� �迭
	result[0] = 0; //result[n] = 0;  //��߳��� �������� ù��° ���(0�� ���)�� ����
	//result[0],[1],[2],[3]���� ä������ ���̻� ����� �ʿ����. 
	//[4]�� �������带 �����ϰ�湮���� ���� ���� [5]�� ��������ϱ�.
	*/
	int whNum = 0;
	//int notvisit;
	PQ.push(v);
	while (!PQ.empty())  //PQ�� ��������ʴµ��� ����
	{
		whNum++;
		v = PQ.top();
		PQ.pop();

		if (v.bound < minlength)  //�� ������ ������ ��� v�� �����ϹǷ� �ڽĳ��� ������ �� ����
		{
			///minlength = v.bound;
			u.level = v.level + 1;  //�ڽĳ��� �� �θ��� ���� +1
			for (int i = 1; i < n; i++)
			{
				if (hasIn(1,i, v)) continue;
				for (int k = 0; k < v.level/*sizeof(v.path) / sizeof(int)*/; k++)
					u.path[k] = v.path[k];
				u.path[u.level - 1] = i; ////////�湮�������� ���� �θ��� �������� i��� �߰�
					
				if (u.level == n - 1)  //level= 1...n-1
				{
					//�湮���� ���� ���� �ϳ��� ��� �߰��ϱ�����
					//���Ŀ� ������ ���� ���� ���� ��带 ã�´�.
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
					else  //�� ���� ���� �߸��Ȱǵ�,,
						lasttravel = 0;
					u.path[n-1] = lasttravel;
					/*for (int k = 1; k < n; k++)
					{
						if (!hasIn(1, k, u))    //�湮���� ���� �� �ϳ��� ��带 �߰�
							u.path[n - 1] = k;  
					}*/
					u.path[n] = 0;  //ù��°��尡 �������

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
					if (u.bound < minlength) //�����Ұ��
					{
						////////////////������ ��� u�� �����̿���Ƽ ť�� �־��ش�.
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
	bound = length(v);  //�̹� �湮�� ��� ����
	//int nottravel = 0;
	//���� �湮�������� ���鿡 ���� �ּҰ� ���� bound�� ���ϱ�����
	for (int i = v.level-1; i < n; i++)
	{
		if (hasIn(0,i, v)) continue;  
		min = INF;
		for (int j = 0; j < n; j++)
		{
			//1.�밢���̰ų�, 2.�̹� �湮�� ����̰ų�, 3.v.path���� ���������� �湮�ѳ�忡�� ���� ���� �� ù��° ����� ���� ����
			if ((i == j)|| (hasIn(1, j, v)) || (j == 0 && i == v.path[v.level - 1]) ) continue; 
			if (min > Mtrx[i][j]) min = Mtrx[i][j];  //������ ���� ���ٰ� �� ���� ���� �ִٸ� min���� �� ���������� ����
		}
		bound += min;  //���� ���� ���� bound�� ������
	}

	return bound;  //����
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
		visited[i] = false;  //���� �湮���� �ʾ����Ƿ� ��� ���鿡 ���� false��
		//memset(visited, false, n)���� ���־��.
	}
	visited[0] = true; //ù��° ��带 ������� �Ͽ� �� ��带 �湮�� ���� ����*/

	/*int minimum_bound = INF;
	// level 1 
	minimum_bound = bound(0); //ù��°��� -> ������ ���� ���°��� ���� ���� ����ġ��
	//��, v1->v3
	//next_index=3
	*/
	NODE u;  

	u = travel();
	minlength = length(u);
	cout << "���� �Ÿ� : " << minlength;
	cout << "\n���� ���:";
	for (int i = 0; i < u.level + 1; i++)
		//cout << result[i] +1 << "->";
		cout << u.path[i] + 1 << "->";
	//cout << result[u.level + 1]+1;
	cout << u.path[u.level + 1] + 1;

	
}