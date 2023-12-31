//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int m, n;
int xvoid[10], yvoid[10]; // maximum of void cells is 10


char *p = NULL; //there are two sets for the matrix, p is for graph, the struct
struct set		//set is for calculating
{
	int par[2]; //parent cell
	int dis;	//distance
	bool vis;	//the cell has gone 
}*pset;


int main()
{
	printf("m = ");
	scanf_s("%d", &m);
	printf("n = ");
	scanf_s("%d", &n);

	int i, j;
	for (i = 0; i < 10; i++)
	{
		printf("Xvoid%d = ", i);
		scanf_s("%d", xvoid + i);
		if (xvoid[i] < 0) //<0 means input finished
			break;
	}

	for (i = 0; i < 10; i++)
	{
		printf("Yvoid%d = ", i);
		scanf_s("%d", yvoid + i);
		if (yvoid[i] < 0) //<0 means input finished
			break;
	}

	/*** initialize p ***/
	p = (char *)malloc(m * n * sizeof(char));
	if (p == NULL)
	{
		printf("p malloc error\n");
		return 0;
	}
	memset(p, ' ', m * n * sizeof(char));

	for (i = 0; i < 10; i++)
	{
		if ((xvoid[i] >= 0) && (yvoid[i] >= 0))
			p[m * yvoid[i] + xvoid[i]] = 'X';  //void cells are 'X'
		else
			break;
	}

	/*** initialize pset ***/
	pset = (set *)malloc(m * n * sizeof(set));
	if (pset == NULL)
	{
		printf("pset malloc error\n");
		return 0;
	}
	for (i = 0; i < m * n; i++)
	{
		pset[i].dis = 99999;
		pset[i].vis = 0;
	}


	int x = 0, y = 0;//start from the first cell
	pset[0].dis = 0; //initialize the first cell
	pset[0].vis = 1;
	while (1)
	{
		int a, b, c, d;
		a = (x > 0) ? (x - 1) : 0; //update the node connected to (x,y)
		b = (y > 0) ? (y - 1) : 0;
		c = (m - 1 == x) ? (m - 1) : (x + 1);
		d = (n - 1 == y) ? (n - 1) : (y + 1);
		for (j = b; j <= d; j++)
			for (i = a; i <= c; i++)
			{
				if (p[m * j + i] == 'X') //the cell is void
					continue;
				if (pset[m * j + i].vis == 1) //the cell has gone
					continue;
				if ((j == y) && (i == x))//parent cell
					continue;
				if (pset[m * j + i].dis > 1 + pset[m * y + x].dis)
				{
					pset[m * j + i].dis = 1 + pset[m * y + x].dis;//updating
					pset[m * j + i].par[0] = x;
					pset[m * j + i].par[1] = y;
				}
				if ((j == n - 1) && (i == m - 1))//if we have reached (m-1,n-1),no need to keep calculating
					goto end;
			}
		pset[m * y + x].vis = 1;//cell (x,y) has gone

		x = 0;//find next cell whose distance is smallest for next loop.
		y = 0;
		int temp = 99999;
		for (j = 0; j < n; j++)
			for (i = 0; i < m; i++)
			{
				if (p[m * j + i] == 'X')
					continue;
				if (pset[m * j + i].vis == 1)
					continue;
				if (pset[m * j + i].dis < temp)
				{
					x = i;
					y = j;
					temp = pset[m * y + x].dis;
				}
			}
	}

end:
	/*** write to p ***/
	p[m * n - 1] = 'O';///cells on the path are 'O';
	i = pset[m * n - 1].par[0];
	j = pset[m * n - 1].par[1];
	while (1)
	{
		int k = m * j + i;
		p[k] = 'O';
		i = pset[k].par[0];
		j = pset[k].par[1];
		if (0 == k)
			break;
	}
	p[0] = 'O';

	/*** show graph ***/
	printf("\n  ");
	for (i = 0; i < m; i++)
		printf("%d", i);
	printf("\n\n");
	for (i = 0; i < n; i++)
	{
		printf("%d ", i);
		for (int j = 0; j < m; j++)
			printf("%c", p[m * i + j]);
		printf("\n");
	}
	return 0;
}
