/*
- �ۼ���: ������Ű��а� 22012225 �պ���
- Dijkstra �˰������� ���<->���� �ִܰ�� ã��

*/

#include <stdio.h>
#include <iostream>
using namespace std;

#define INF 1000000  //���̺� �ʱ�ȭ�Ҷ� �������� �������ְ� �����ϱ����� ���Ƿ� �鸸�� ū ������ ����
#define n 12 //���(����) ��
//#define m //������ ��

int W[12][12] =  //������ ����ġ�� ���� 2���� �迭
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

int visited[n];  //�湮�� ������� Ȯ���ϱ����� �迭. 
int touch[n];  
int length[n]; //����忡�� �� �� �ִ� ������ ����ġ��� ���� . �̹� �湮�Ϸ�� ���� -1�� ����ġ�� ������.




void dijkstra(int start, int end)
{

	for (int i = 0; i < n; i++)
	{
		visited[i] = false;  //���� �湮�����ʾ����Ƿ� false���� �ʱ�ȭ
		touch[i] = start; //ó�� �ʱ�ȭ���� ���������ȣ��.
		length[i] = W[start][i];  //����� ��忡�� ������ ����� ���� ����ġ�� �ʱ�ȭ
	}
	visited[start] = true;  //������� �湮�� ���� ǥ��
	
	for (int i = 0; i < n; i++)
	{
		int near_node = 100;
		int min = INF + 1;
		//�湮���� ���� ��� �߿��� ���� ����� ��� ����
		for (int j = 0; j < n - 1; j++)  
		{
			//�湮���� ���� ��� �߿���, legnth[j]�� ��������ϰ�, �� �� min���� �� ���� length[j]�� ������
			if ((length[j] >= 0) && (length[j] < min) && (visited[j] == false))
			{
				min = length[j];  //min���� �� ���� ����ġ�� ���� length[j]�� min���� �ٲ��ְ�
				near_node = j; //������ ��带 j�� �ٲ���.
			}// ����ؼ� i�� ������ ����ġ�� min�� ���ذ��� ���� ����� ���� ��带 ã�´�.
		}  //�� for-loop�� ���� �� near_node�� �湮�������� ��� �� ���� ����� ��� ��ȣ��.
		visited[near_node] = true;  //�湮���� ���� ��� �� ���� ����� ��带 �湮�� ���� ǥ��

		for (int j = 0; j < n; j++)
		{
			
			if (visited[j] != true)  //�湮�������� ��� �߿����� �����ϵ��� ��
			{
				if (length[near_node] + W[near_node][j] < length[j])  //���� ����ġ���� �����带 ���ļ� ���°� ����ġ�� �� ���� ���
				{
					length[j] = length[near_node] + W[near_node][j];  //�� ���� ����ġ�� ������ �뼱���� ������
					touch[j] = near_node;
				}
			}

		}

	}

	/* ��� ��� */
	cout << "���ִܰ�� : " << start;
	int i = end;  //touch�迭�� �ڿ�������
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
		cout << " -> " << print[i];  //print�迭 �Ųٷ� ���
	}
	cout << " -> " << end;

	/* �ִ� ���� ��� */
	cout << endl << "������ �ִ� �Ÿ�: " << length[end] << endl << endl;


}

void main()
{
	int start, end;
	cout << "<<<<���ͽ�Ʈ�� �˰���>>>> " << endl << endl;
	
	/*
	cout << " ����(0) ��õ(1) ����(2) õ��(3) û��(4) ����(5) ����(6) �뱸(7) ����(8) ����(9) �λ�(10) ���(11) " << endl;
	cout << "Ž���� �� ������ ����ȣ�� �Է��Ͻÿ�. (e.g. 1 4 ):" << endl;
	cin >> start >> end;
	dijkstra(start, end);
	*/

	cout << "��� -> ����" << endl;
	dijkstra(11, 0);

	cout << "���� -> ��� " << endl;
	dijkstra(0, 11);
	


}