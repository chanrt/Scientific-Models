#include<iostream>

using namespace std;

float **makeFloatArray(int m, int n)
{
    float **arr = new float *[m];
    for(int i = 0; i < m; i++)
    {
        arr[i] = new float[n];
    }
    return arr;
}

float calc_determinant(float **f, int n)
{
    float det = 0.0;

    if(n == 1) return f[0][0];
    else if(n == 2) return (f[0][0] * f[1][1] - f[1][0] * f[0][1]);
    else
    {
        for(int i = 0; i < n; i++)
        {
            if(f[0][i] != 0)
            {
                float **major = makeFloatArray(n-1,n-1);

                for(int x = 1; x < n; x++)
                {
                    for(int y = 0; y < n; y++)
                    {
                        if(y < i)
                        {
                            major[x-1][y] = f[x][y];
                        }
                        else if(y > i)
                        {
                            major[x-1][y-1] = f[x][y];
                        }
                    }
                }

                int cofactor;

                if(i % 2 == 0) cofactor = 1;
                else cofactor = -1;

                det = det + (f[0][i] * cofactor * calc_determinant(major,n-1)); 
            }
        }
    } 
    return det;
}

class Matrix
{
    private:
        float **a;
        int m,n;

    public:
        Matrix(int r, int c)
        {
            m = r;
            n = c;

            a = makeFloatArray(m,n);
        }

        Matrix(int sq)
        {
            m = sq;
            n = sq;

            a = makeFloatArray(n,n);
        }

        Matrix(Matrix M, float f)
        {
            m = M.getM();
            n = M.getN();

            a = makeFloatArray(m,n);

            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    a[i][j] = M.getElement(i,j);
                }
            }
        }

        Matrix(Matrix M, Matrix N)
        {
            if(M.getN() == N.getM())
            {
                m = M.getM();
                n = N.getN();

                a = makeFloatArray(m,n);

                for(int i = 0; i < m; i++)
                {
                    for(int j = 0; j < n; j++)
                    {
                        a[i][j] = 0;
                        for(int k = 0; k < n; k++)
                        {
                            a[i][j] = a[i][j] + (M.getElement(i,k) * N.getElement(k,j));
                        }
                    }
                }
            }
        }

        float **getMatrix()
        {
            return a;
        }

        int getM()
        {
            return m;
        }

        int getN()
        {
            return n;
        }

        float getElement(int r, int c)
        {
            return a[r][c];
        }

        void makeIdentity()
        {
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    if(i != j) a[i][j] = 0;
                    else a[i][j] = 1;
                }
            }
        }

        void makeZero()
        {
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    a[i][j] = 0;
                }
            }
        }

        void setMatrix()
        {
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    scanf("%f",&a[i][j]);
                }
            }
        }

        void setMatrix(float **M)
        {
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    a[i][j] = M[i][j];
                }
            }
        }

        void setMatrix(Matrix M)
        {
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    a[i][j] = M.getElement(i,j);
                }
            }
        }

        void setRow(float *r, int row_no)
        {
            for(int i = 0; i < n; i++)
            {
                a[row_no][i] = r[i];
            }
        }

        void setColumn(float *c, int col_no)
        {
            for(int i = 0; i < m; i++)
            {
                a[i][col_no] = c[i];
            }
        }

        void setElement(int r, int c, float i)
        {
            a[r][c] = i;
        }

        bool operator == (Matrix M)
        {
            if(m == M.getM() && n == M.getN())
            {
                for(int i = 0; i < m; i++)
                {
                    for(int j = 0; j < n; j++)
                    {
                        if(float(a[i][j]) != float(M.getElement(i,j))) return false;
                    }
                }
                return true;
            }
            else return false;
        }

        Matrix operator + (Matrix M)
        {
            if(m == M.getM() && n == M.getN())
            {
                Matrix sum(m,n);
                for(int i = 0; i < m; i++)
                {
                    for(int j = 0; j < n; j++)
                    {
                        sum.setElement(i,j,a[i][j] + M.getElement(i,j));
                    }
                }
                return sum;
            }
        }

        Matrix operator - ()
        {
            Matrix add_inv(m,n);
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    add_inv.setElement(i,j,-a[i][j]);
                }
            }
            return add_inv;
        }

        Matrix operator - (Matrix M)
        {
            return (*this + (- M));
        }

        Matrix operator * (float f)
        {
            Matrix mul(m,n);
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    mul.setElement(i,j, a[i][j] * f);
                }
            }
            return mul;
        }

        Matrix operator * (Matrix M)
        {
            if(n == M.getM())
            {
                Matrix prod(m,M.getN());
                int element;

                for(int i = 0; i < m; i++)
                {
                    for(int j = 0; j < M.getN(); j++)
                    {
                        element = 0;
                        for(int k = 0; k < n; k++)
                        {
                            element = element + (a[i][k]*M.getElement(k,j));
                        }
                        prod.setElement(i,j,element);
                    }
                }
                return prod;
            }
        }

        Matrix transpose()
        {
            Matrix trans(n,m);

            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    trans.setElement(i,j,a[j][i]);
                }
            }
            return trans;
        }

        bool isDiagonal()
        {
            for(int i = 0; i < m ; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    if(i == j)
                    {
                        if(a[i][i] == 0) return false;
                    }
                    else
                    {
                        if(a[i][j] != 0) return false;
                    }
                }
            }
            return true;
        }

        bool isUpperTriangular()
        {
            for(int i = 0; i < m ; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    if(i > j)
                    {
                        if(a[i][j] != 0) return false;
                    }
                }
            }
            return true;
        }

        bool isLowerTriangular()
        {
            this->transpose();

            if(this->isUpperTriangular())
            {
                this->transpose();
                return true;
            }
            else 
            {
                this->transpose();
                return false;
            }
        }

        void rowExchange(int r1, int r2)
        {
            float temp;

            for(int i = 0; i < n; i++)
            {
                temp = a[r1][i];
                a[r1][i] = a[r2][i];
                a[r2][i] = temp;
            }
        }

        void columnExchange(int c1, int c2)
        {
            float temp;

            for(int i = 0; i < m; i++)
            {
                temp = a[i][c1];
                a[i][c1] = a[i][c2];
                a[i][c2] = temp;
            }
        }

        void displayMatrix()
        {
            cout<<endl;
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    printf("%6.3f ",a[i][j]);
                }
                cout<<endl;
            }
        }

        float determinant()
        {
            if(isDiagonal() || isUpperTriangular() || isLowerTriangular())
            {
                float det = 1.0;
                for(int i = 0; i < n; i++)
                {
                    det = det * a[i][i];
                }
                return det;
            }

            return calc_determinant(a, n);
        }

        void eliminate();
        Matrix getInverse();
        float *solveSystem(Matrix vector);
};

void Matrix::eliminate()
{
    float multiplier;
    for(int i = 0; i < m; i++)
    {
        for(int j = i + 1; j < m; j++)
        {
            if(a[i][i] == 0)
            {
                for(int k = i + 1; k <= m; k++)
                {
                    if(k == m)
                    {
                        cout<<"Elimination breaks down";
                        goto elimination_out;
                    }
                    else if(a[k][i] != 0)
                    {
                        displayMatrix();
                        rowExchange(k,i);
                        cout<<"Row exchange: "<<k<<" and "<<i;
                        break;
                    }
                }
            }

            displayMatrix();
            multiplier = a[j][i] / a[i][i];
            cout<<"Multiplier: "<<multiplier;
            for(int k = 0; k < n; k++)
            {
                a[j][k] = a[j][k] - (a[i][k] * multiplier);
            }
        }
    }
    elimination_out:
    cout<<"Process terminated";
}

Matrix Matrix::getInverse()
{
    if(determinant() != 0)
    {
        float multiplier;
        Matrix dup(*this, 1);
        Matrix inv(n);
        inv.makeIdentity();

        for(int i = 0; i < n; i++)
        {
            if(dup.getElement(i,i) == 0)
            {
                for(int j = i+1; j <= n; j++)
                {
                    if(j == n)
                    {
                        cout<<"Matrix is not invertible";
                        goto inverse_out;
                    }
                    if(dup.getElement(j,i) != 0 && i != j)
                    {
                        dup.rowExchange(i,j);
                        inv.rowExchange(i,j);
                        break;
                    }
                }
            }

            for(int j = 0; j < n; j++)
            {
                if(i != j)
                {
                    multiplier = dup.getElement(j,i) / dup.getElement(i,i);
                    for(int k = 0; k < n; k++)
                    {
                        dup.setElement(j,k,dup.getElement(j,k) - (dup.getElement(i,k) * multiplier));
                        inv.setElement(j,k,inv.getElement(j,k) - (inv.getElement(i,k) * multiplier));
                    }
                }
            }
        }

        for(int l = 0; l < n; l++)
        {
            float divider = dup.getElement(l,l);
            for(int o = 0; o < n; o++)
            {
                inv.setElement(l,o,inv.getElement(l,o) / divider);
            }
        }
        return inv;
    }
    inverse_out:
    cout<<"Process terminated";
}

float * Matrix::solveSystem(Matrix vector)
{
    if(determinant() != 0)
    {
        float multiplier;
        for(int i = 0; i < (n-1); i++)
        {
            if(a[i][i] == 0)
            {
                for(int j = (i+1); j <= n; j++)
                {
                    if(j == n)
                    {
                        cout<<"System unsolvable";
                        goto system_out;
                    }
                    if(a[j][i] != 0)
                    {
                        rowExchange(i,j);
                        vector.rowExchange(i,j);
                        break;
                    }
                }
            }

            //printf("Multiplier: %.3f",multiplier);
            for(int j = (i+1); j < n; j++)
            {
                multiplier = a[j][i] / a[i][i];
                for(int k = 0; k < n; k++)
                {
                    a[j][k] = a[j][k] - (multiplier * a[i][k]);
                }
                vector.setElement(j,0, vector.getElement(j,0) - (multiplier * vector.getElement(i,0)));
            }
            displayMatrix();
            vector.displayMatrix();
        }

        float *solution = new float[n];
        solution[n - 1] = vector.getElement(n - 1,0) / a[n-1][n-1];

        float lc;
        for(int i = 2; n - i >= 0; i++)
        {
            lc = vector.getElement(n-i,0);

            for(int j = (n-i+1); j < n; j++)
            {
                lc = lc - (a[n-i][j] * solution[j]);
            }
            solution[n-i] = lc / a[n-i][n-i];
        }
        return solution;
    }
    system_out:
    cout<<"Process terminated";
} 

int main()
{
    Matrix m1(3);
    m1.setMatrix();

    Matrix m2(3,1);
    m2.setMatrix();

    m1.solveSystem(m2);
}