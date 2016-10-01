#include <iostream>
#include <cmath>

typedef unsigned int uint;

using namespace std;

struct Coord
{
	uint x;
	uint y;
	Coord (uint x, uint y)
	{
		this->x=x; this->y=y;
	}
};

class Matrix
{
private:
	uint rows;
	double **data;
public:
	Matrix()
	{
		cin >> rows;
		data=new double* [rows];
		for (uint i=0; i<rows; i++)
		{
			data[i]=new double [rows];
			for (uint j=0; j<rows; j++)
			{
				cin >> data[i][j];
			}
		}
	}
	
	void out()
	{
		for (uint i=0; i<rows; i++)
		{
			for (uint j=0; j<rows; j++)
			{
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
	}
	
	void free()
	{
		for (uint i=0; i<rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}
	
	void rotate(uint i, uint j, float alpha) //Умножение на матрицу поворота
	{
		double *rowi=new double [rows],*rowj=new double [rows];
		for (uint x=0; x<rows; x++)
		{
			rowi[x]=data[i][x];
			rowj[x]=data[j][x];
		}
		for (uint k=0; k<rows; k++)
		{
			data[i][k]=rowi[k]*cos(alpha)-rowj[k]*sin(alpha);
			data[j][k]=rowi[k]*sin(alpha)+rowj[k]*cos(alpha);
		}
		for (uint k=0; k<rows; k++)
		{
			data[k][i]=rowi[k]*cos(alpha)-rowj[k]*sin(alpha);
			data[k][j]=rowi[k]*sin(alpha)+rowj[k]*cos(alpha);
		}
		delete[] rowi;
		delete[] rowj;
	}
	
	bool isSymm()
	{
		for (uint i=0; i<rows; i++)
		{
			for (uint j=0; j<i; j++)
			{
				if (data[i][j]!=data[j][i]) return false;
			}
		}
		return true;
	}
	
	Coord max()
	{
		double max=0;
		uint maxi=0,maxj=0;
		for (uint i=0; i<rows; i++)
		{
			for (uint j=0; j<i; j++)
			{
				if (i==j) continue;
				if (abs(data[i][j])>max)
				{
					maxi=i; maxj=j; max=abs(data[i][j]);
				}
			}
		}
		return Coord(maxi,maxj);
	}
	
	double diff()
	{
		double res=0;
		for (uint i=0; i<rows; i++)
		{
			for (uint j=0; j<i; j++)
			{
				if (i==j) continue;
				res+=data[i][j]*data[i][j];
			}
		}
		return res;
	}
	
	double getalpha(uint i, uint j)
	{
		return atan(2*data[i][j]/(data[j][j]-data[i][i]));
	}
};

int main ()
{
	Matrix a;
	double eps=1;
	Coord c(0,0);
	
	if (!a.isSymm())
	{
		cout << "Несимметричная матрица";
		return -1;
	}
	while (a.diff()>=eps)
	{
		c=a.max();
		a.rotate(c.x,c.y,a.getalpha(c.x,c.y));
	}
	a.out();
	return 0;
}
