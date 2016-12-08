#include <iostream>
#include <cmath>

const double precision = 0.001;

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

	Matrix(uint size)
	{
		rows = size;
		data=new double* [size];
		for (uint i=0; i<size; i++)
		{
			data[i]=new double [size];
			for (uint j=0; j<size; j++)
			{
				if (i == j) data[i][j]=10; else data[i][j]=0;
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
		double cs=cos(alpha),sn=sin(alpha);
		for (uint x=0; x<rows; x++)
		{
			rowi[x]=data[i][x];
			rowj[x]=data[j][x];
		}
		for (uint k=0; k<rows; k++)
		{
			data[i][k]=rowi[k]*cs+rowj[k]*sn;
		}
		for (uint k=0; k<rows; k++)
		{
			data[j][k]=-rowi[k]*sn+rowj[k]*cs;
		}

		for (uint x=0; x<rows; x++)
		{
			rowi[x]=data[x][i];
			rowj[x]=data[x][j];
		}
		for (uint k=0; k<rows; k++)
		{
			data[k][i]=rowi[k]*cs+rowj[k]*sn;
		}
		for (uint k=0; k<rows; k++)
		{
			data[k][j]=-rowi[k]*sn+rowj[k]*cs;
		}

	}

	void rt(uint i, uint j, float alpha) //Умножение на матрицу поворота
	{
		double *rowi=new double [rows],*rowj=new double [rows];
		double cs=cos(alpha),sn=sin(alpha);
		for (uint x=0; x<rows; x++)
		{
			rowi[x]=data[i][x];
			rowj[x]=data[j][x];
		}
		for (uint k=0; k<rows; k++)
		{
			data[i][k]=rowi[k]*cs+rowj[k]*sn;
		}
		for (uint k=0; k<rows; k++)
		{
			data[j][k]=-rowi[k]*sn+rowj[k]*cs;
		}

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
			for (uint j=i+1; j<rows; j++)
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
		return sqrt(res);
	}

	double getalpha(uint i, uint j)
	{
		if (data[j][j]-data[i][i] < precision) return 3.14159265/4;
		return atan(2*data[i][j]/(data[j][j]-data[i][i]))/2;
	}

	friend void getEigens(Matrix &A, Matrix &B);

	uint getRows() {return rows;}
};

void getEigens(Matrix &A, Matrix &B)
{
	cout << "Собственные значения и соответствующие векторы:\n";
	for (int i = 0; i < A.rows; i++)
	{
		cout << "λ" << i << "=" << A.data[i][i] << endl;
		cout << "x" << i << "=" << "[" << B.data[i][0];
		for (int j = 1; j < B.rows; j++)
		{
			cout << "," << B.data[i][j];
		}
		cout << "]\n";
	}

}

int main ()
{
	Matrix a;
	Matrix one(a.getRows());
	double tmp;
	double eps=0.000001;
	Coord c(0,0);

	if (!a.isSymm())
	{
		cout << "Несимметричная матрица";
		return -1;
	}
	while (a.diff()>=eps)
	{
		c=a.max();
		tmp=a.getalpha(c.x,c.y);
		a.rotate(c.x,c.y,tmp);
		one.rt(c.x,c.y,tmp);
	}
	getEigens(a,one);
	return 0;
}
