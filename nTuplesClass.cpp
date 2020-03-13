#include<iostream>
#include<math.h>

using namespace std;

class Ntuple
{
    private:

        float *a;
        int dim;

    public:

        Ntuple()
        {
            a = new float[3];
            dim = 3;
        }

        Ntuple(int n)
        {
            a = new float[3];
            dim = n;
        }

        void setZero()
        {
            for(int i = 0; i < dim; i++) a[i] = 0;
        }

        void setConstant(float f)
        {
            for(int i = 0; i < dim; i++) a[i] = f;
        }

        void setComponents(float *f, int n)
        {
            if(n == dim)
            {
                for(int i = 0; i < dim; i++) a[i] = f[i];
            }
        }

        void setNthComponent(int n, float f)
        {
            if(n <= dim)
            {
                a[n-1] = f;
            }
        }

        int getDim()
        {
            return dim;
        }

        float *getComponents()
        {
            return a;
        }

        float getNthComponent(int n)
        {
            if(n <= dim)
            {
                return a[n-1];
            }
        }

        float getMagnitude()
        {
            float sum = 0.0;
            for(int i = 0; i < dim; i++) sum = sum + (a[i] * a[i]);
            return sqrt(sum);
        }

        Ntuple operator + (Ntuple t)
        {
            if(dim == t.getDim())
            {
                Ntuple sum(dim);
                for(int i = 0; i < dim; i++) sum.a[i] = a[i] + t.a[i];

                return sum;
            }
        }

        Ntuple operator - ()
        {
            Ntuple inv(dim);
            for(int i = 0; i < dim; i++) inv.a[i] = - a[i];
            return inv;
        }

        Ntuple operator - (Ntuple t)
        {
            if(dim == t.getDim())
            {
                return (*this + (- t));
            }
        }

        Ntuple operator * (float m)
        {
            Ntuple mul(dim);

            for(int i = 0; i < dim; i++) mul.a[i] = m * a[i];
            return mul;
        }

        Ntuple operator * (Ntuple t)
        {
            if(dim == t.getDim())
            {
                Ntuple dot(dim);

                for(int i = 0; i < dim; i++) dot.a[i] = a[i] * t.a[i];
                return dot;
            }
        }

        void displayTuple()
        {
            if(dim == 1)
            {
                printf("\n( %f )",a[0]);
            }
            else
            {
                printf("\n( %f ",a[0]);
                for(int i = 1; i < dim; i++)
                {
                    printf(", %f ",a[i]);
                }
                printf(")");
            }
        }
};

int main()
{
    /* code */
}

