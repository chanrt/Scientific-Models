#include<iostream>

using namespace std;

double getStateEnergy(int state);

double convertToeV(double energy);
double convertToWavelength(double freq);
double convertToNano(double wavelength);
double convertToFrequency(double wavelength);

class Atom
{
    private:
        int Z;

    public:
        void setAtomicNumber(int z)
        {
            Z = z;
        }

        int getAtomicNumber()
        {
            return Z;
        }
};

Atom atom;

class Electron
{
    private:
        int n, p;
        double E, r, v;

    public:
        void setState(int state)
        {
            n = state;
            calcParams();
        }

        void calcParams()
        {
            p = atom.getAtomicNumber();
            E = getStateEnergy(n);
            r = 5.29e-011 * (float(n*n) / float(p));
            v = 2.19e006 * (float(p) / float(n));
        }

        double getEnergy()
        {
            return E;
        }

        double getRadius()
        {
            return r;
        }

        double getVelocity()
        {
            return v;
        }

        int getState()
        {
            return n;
        }
};

Electron e;

class Transition
{
    private:
        int n1, n2;
        double energyDiff;
        double freq, wavelength;

    public:
        Transition()
        {
            n1 = 1;
            n2 = 2;
        }
        Transition(int final)
        {
            n1 = 1;
            n2 = final;
        }
        Transition(int initial, int final)
        {
            n1 = initial;
            n2 = final;

            energyDiff = getStateEnergy(n2) - getStateEnergy(n1);
            freq = energyDiff / (6.626e-034);
            wavelength = convertToWavelength(freq);
        }
        double getEnergyDiff()
        {
            return energyDiff;
        }
        double getFrequency()
        {
            return freq;
        }
        double getWavelength()
        {
            return wavelength;
        }
};

int main()
{
    int init_z, init_n;
    cout<<"---> Bohr's Atomic Model for Hydrogen and Hydrogen-like species <---";
    cout<<endl<<endl<<"Enter atomic number of atom: ";
    cin>>init_z;

    atom.setAtomicNumber(init_z);

    cout<<"Enter initial state of electron (1 = ground state): ";
    cin>>init_n;

    e.setState(init_n);

    while(1)
    {
        out:
        int choice;

        cout<<endl;
        for(int i = 1; i < 40; i++)
        {
            printf("-");
        }

        cout<<endl<<"State: "<<e.getState();
        cout<<endl<<"Energy of electron: "<<e.getEnergy()<<" Joules or "<<convertToeV(e.getEnergy())<<" eV";
        cout<<endl<<"Radius of orbit: "<<e.getRadius()<<" metres";
        cout<<endl<<"Velocity of electron: "<<e.getVelocity()<<" m/s";

        cout<<endl<<endl<<"1: Excite to";
        cout<<endl<<"2: De-excite to";
        cout<<endl<<"3: Excite (incident radiation)";
        cout<<endl<<"4: De-excite (all possibilities)";

        cout<<endl<<endl<<"Your choice: ";
        cin>>choice;

        if(choice == 1)
        {
            int final_state;

            cout<<"Enter final state: ";
            cin>>final_state;

            if(final_state <= e.getState())
            {
                cout<<endl<<"Cannot excite electron to lower state or the same state!";
                goto out;
            }

            Transition trans(e.getState(), final_state);
            cout<<endl<<"Energy absorbed by electron: "<<trans.getEnergyDiff()<<" Joules or "<<convertToeV(trans.getEnergyDiff())<<" eV";
            cout<<endl<<"Frequency of radiation absorbed: "<<trans.getFrequency()<<" Hz";
            cout<<endl<<"Wavelength of radiation absorbed: "<<trans.getWavelength()<<" m or "<<convertToNano(trans.getWavelength())<<" nm";
            cout<<endl;

            e.setState(final_state);
        }
        else if(choice == 2)
        {
            if(e.getState() == 1) 
            {
                cout<<"Not possible to de-excite electron further";
                goto out;
            }
            int final_state;

            cout<<"Enter final state: ";
            cin>>final_state;

            if(final_state >= e.getState())
            {
                cout<<endl<<"Cannot de-excite electron to higher or same state";
                goto out;
            }

            Transition trans(e.getState(), final_state);
            cout<<endl<<"Energy released by electron: "<<-trans.getEnergyDiff()<<" Joules or "<<convertToeV(-trans.getEnergyDiff())<<" eV";
            cout<<endl<<"Frequency of radiation emitted: "<<-trans.getFrequency()<<" Hz";
            cout<<endl<<"Wavelength of radiation emitted: "<<-trans.getWavelength()<<" m or "<<convertToNano(-trans.getWavelength())<<" nm";
            cout<<endl;

            e.setState(final_state);
        }
        else if(choice == 3)
        {
            int input_q;
            double freq;

            cout<<endl<<"Is your input in 1. frequency (10^15 Hz) or 2. wavelength (nm) ?: ";
            cin>>input_q;

            if(input_q == 1)
            {
                cout<<endl<<"Enter frequency of incident radiation as a multiple of 10^15 Hz: ";
                double freq;
                freq = freq * 1e015;
            }
            else if(input_q == 2)
            {
                double wavelength;
                cout<<endl<<"Enter wavelength of incident radiation in nm: ";
                cin>>wavelength;

                freq = convertToFrequency(wavelength * 1e-9);
            }

            double incident_energy = 6.626 * 1e-034 * freq;
            int final, final_state;
            
            if(getStateEnergy(e.getState()) - getStateEnergy(e.getState() + 1) < incident_energy)
            {
                cout<<"Energy of incident radiation is too low for any excitation to happen";
                goto out;
            }

            for(final = e.getState() + 1; incident_energy <= getStateEnergy(final); final++);
            
            cout<<endl<<"The electron can be excited to the following states: ";

            for(int i = e.getState() + 1; i <= final; i++)
            {
                cout<<i<<" ";
            }

            cout<<endl<<"Enter final state: ";
            cin>>final_state;

            if(final_state > final || final_state < 1)
            {
                cout<<endl<<"Not possible to excite electron to that state";
                goto out;
            }

            Transition trans(e.getState(),final_state);
            cout<<endl<<"Energy absorbed by electron: "<<trans.getEnergyDiff()<<" Joules or "<<convertToeV(trans.getEnergyDiff())<<" eV";
            cout<<endl<<"Frequency of radiation absorbed: "<<trans.getFrequency()<<" Hz";
            cout<<endl<<"Wavelength of radiation absorbed: "<<trans.getWavelength()<<" m or "<<convertToNano(trans.getWavelength())<<" nm";
            cout<<endl;

            e.setState(final_state);
        }
        else if(choice == 4)
        {
            int lower = 1;
            int upper = e.getState() - 1;
            int final_state;

            cout<<endl<<"The following states can be attained through de-excitation:";

            for(int i = upper; i >= lower; i--)
            {
                cout<<i<<" ";
            }
            cout<<endl<<"select new state: ";
            cin>>final_state;

            if(final_state > upper || final_state < lower)
            {
                cout<<endl<<"Not possible to de-excite electron to that state";
                goto out;
            }

            Transition trans(e.getState(), final_state);
            cout<<endl<<"Energy released by electron: "<<-trans.getEnergyDiff()<<" Joules or "<<convertToeV(-trans.getEnergyDiff())<<" eV";
            cout<<endl<<"Frequency of radiation emitted: "<<-trans.getFrequency()<<" Hz";
            cout<<endl<<"Wavelength of radiation emitted: "<<-trans.getWavelength()<<" m or "<<convertToNano(-trans.getWavelength())<<" nm";
            cout<<endl;

            e.setState(final_state);
        }
    }
}

double convertToeV(double energy)
{
    return (energy / (1.609e-019));
}

double convertToWavelength(double freq)
{
    return (3e006 / freq);
}

double convertToFrequency(double wavelength)
{
    return (3e006 / wavelength);
}

double convertToNano(double wavelength)
{
    return (wavelength * 1e009);
}

double getStateEnergy(int state)
{
    int p = atom.getAtomicNumber();
    return (- 2.18e-018 * ( float(p*p) / float(state*state) ));
}
