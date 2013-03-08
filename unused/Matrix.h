#include <iostream>
#include <algorithm>
//#include <unistd.h>
#include <stdio.h>
#include <memory.h>
//#include <dirent.h>
#include <sys/stat.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <string>
#include <deque>
#include <stdlib.h>

using namespace std;

/*******************************************************
all matrix reload option function at here 
*******************************************************/

class matrix
{
	public:
		matrix(){m.clear();};
		~matrix(){};
		deque<deque<double> > m;
		matrix& operator=(matrix &x);
		matrix& operator+(matrix &x);
		matrix& operator-(matrix &x);
		matrix& operator*(matrix &x);
		matrix& operator/(matrix &x);
		matrix& operator+(double x);
		matrix& operator-(double x);
		matrix& operator*(double x);
		matrix& operator/(double x);
		matrix& operator!();
		matrix& operator%(matrix &x);
		void kronecker(matrix &x, matrix &y);
	private:
};

matrix& matrix::operator=(matrix &x)
{
	m=x.m;
	return *this;
}

matrix& matrix::operator+(matrix &x)
{
	matrix *temp;
	temp=new matrix();
	temp->m=m;
	if(m.size()==x.m.size() && m[0].size()==x.m[0].size())
	{
		for(int i=0;i<m.size();i++)
			for(int j=0;j<m[0].size();j++)
				temp->m[i][j]=m[i][j]+x.m[i][j];
		return *temp;
	}
	else
	{
		cout << "+row or col do not match" << endl;
		exit(1);
	}
}

matrix& matrix::operator-(matrix &x)
{
	matrix *temp;
	temp=new matrix();
	temp->m=m;
	if(m.size()==x.m.size() && m[0].size()==x.m[0].size())
	{
		for(int i=0;i<m.size();i++)
			for(int j=0;j<m[0].size();j++)
				temp->m[i][j]=m[i][j]-x.m[i][j];
		return *temp;
	}
	else
	{
		cout << "-row or col do not match" << endl;
		exit(1);
	}
}

matrix& matrix::operator*(matrix &x)
{
	matrix *temp;
	temp=new matrix();
	temp->m=m;
	if(m.size()==x.m.size() && m[0].size()==x.m[0].size())
	{
		for(int i=0;i<m.size();i++)
			for(int j=0;j<m[0].size();j++)
				temp->m[i][j]=m[i][j]*x.m[i][j];
		return *temp;
	}
	else
	{
		cout << "*row or col do not match" << endl;
		exit(1);
	}
}

matrix& matrix::operator/(matrix &x)
{
	matrix *temp;
	temp=new matrix();
	temp->m=m;
	if(m.size()==x.m.size() && m[0].size()==x.m[0].size())
	{
		for(int i=0;i<m.size();i++)
			for(int j=0;j<m[0].size();j++)
			{
				if(x.m[i][j]!=0)
					temp->m[i][j]=m[i][j]/x.m[i][j];
				else
				{
					cout << "n/0 happened" << endl;
					exit(1);
				}
			}
		return *temp;
	}
	else
	{
		cout << "/row or col do not match" << endl;
		exit(1);
	}
}

matrix& matrix::operator+(double x)
{
	matrix *temp;
	temp=new matrix();
	temp->m=m;
	for(int i=0;i<m.size();i++)
		for(int j=0;j<m[0].size();j++)
			temp->m[i][j]=m[i][j]+x;
	return *temp;
}

matrix& matrix::operator-(double x)
{
	matrix *temp;
	temp=new matrix();
	temp->m=m;
	for(int i=0;i<m.size();i++)
		for(int j=0;j<m[0].size();j++)
			temp->m[i][j]=m[i][j]-x;
	return *temp;
}

matrix& matrix::operator*(double x)
{
	matrix *temp;
	temp=new matrix();
	temp->m=m;
	for(int i=0;i<m.size();i++)
		for(int j=0;j<m[0].size();j++)
			temp->m[i][j]=m[i][j]*x;
	return *temp;
}

matrix& matrix::operator/(double x)
{
	matrix *temp;
	temp=new matrix();
	temp->m=m;
	if(x!=0)
	{
		for(int i=0;i<m.size();i++)
			for(int j=0;j<m[0].size();j++)
				temp->m[i][j]=m[i][j]/x;
		return *temp;
	}
	else
	{
		cout << "x=0 happened" << endl;
		exit(1);
	}
}

matrix& matrix::operator !()
{
	deque<double> init;
	matrix *temp;
	temp=new matrix();
	for(int i=0;i<m[0].size();i++)
	{
		init.clear();
		for(int j=0;j<m.size();j++)
		{
			init.push_back(m[j][i]);
		}
		temp->m.push_back(init);
	}
	return *temp;
}

matrix& matrix::operator%(matrix &x)
{
	matrix *temp;
	temp=new matrix();
	temp->m=m;
	if(m[0].size()==x.m.size())
	{
		for(int i=0;i<temp->m.size();i++)
			temp->m[i].clear();
		for(int i=0;i<m.size();i++)
			for(int j=0;j<x.m[0].size();j++)
			{
				temp->m[i].push_back(0);
				for(int k=0;k<m[0].size();k++)
					temp->m[i][j]+=m[i][k]*x.m[k][j];
			}
		return *temp;
	}
	else
	{
		cout << "%*% row or col do not match" << endl;
		exit(1);
	}
}

void matrix::kronecker(matrix &x, matrix &y)
{
	m.clear();
	for(int i=0;i<x.m.size()*y.m.size();i++)
	{
		deque<double> init;
		init.clear();
		m.push_back(init);
		for(int j=0;j<x.m[0].size()*y.m[0].size();j++)
		{
			m[i].push_back(x.m[i/y.m.size()][j/y.m[0].size()]*y.m[i%y.m.size()][j%y.m[0].size()]);
		}
	}
}
