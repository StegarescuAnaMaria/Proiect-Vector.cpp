#include <iostream>
#include <cassert>
using namespace std;

template <class T, unsigned n>
class Vector
{
private:
    T* Array;
public:
    Vector(const T);                      ///constructor cu parametri
    Vector (const Vector &ob);     ///constructor de copiere
    Vector () {}                    ///constructor fara parametri
    const T* getArray();
    void setArray(T* matrice);
    const Vector operator=(const Vector &ob);
    const T operator*(Vector ob);
    template <class U, unsigned m>
    friend const Vector<U,m> operator*(const int i, Vector <U, m>const& obj);
    template <class U, unsigned m>
    friend ostream& operator<<(ostream& os, Vector<U,m> const& obj);
    const Vector operator+(Vector ob);
    const Vector operator-(Vector ob);
    const T operator[] (const int unsigned i);
    const unsigned getN();
    ~Vector();
};

template<class T, unsigned n>
Vector<T, n>::~Vector()
{
   delete [] Array;
}

template<class T, unsigned n>
const unsigned Vector<T,n>::getN()
{
    return n;
}

template<class T, unsigned n>
void Vector<T,n>::setArray(T* matrice)
{
    Array=matrice;
}

template<class T, unsigned n>
const T* Vector<T,n>::getArray()
{
    return Array;
}
///operator overloading pe * pentru inmultirea cu scalar la stanga
template <class T, unsigned n>
const Vector<T, n> operator*(const int i, Vector<T, n>const& obj)
{
    Vector<T, n> rezultat;
    unsigned const int dim=n;
    T* Rezultat=new T[dim];

    for(unsigned int j=0; j<dim; j++)
        Rezultat[j]=i*obj.Array[j];

    rezultat.setArray(Rezultat);
    return rezultat;
}
///operator overloading pe << pentru afisarea unui vector
template<class T, unsigned n>
ostream& operator<<(ostream& os, Vector<T, n> const& obj)
{
    os<<"(";
    for(unsigned i=0; i<n; i++)
        if(i==n-1)
            os<<obj.Array[i];
        else
            os<<obj.Array[i]<<",";
    os<<")"<<endl;
    return os;
}
///constructorul cu parametri
template <class T, unsigned n>
Vector <T, n>::Vector(const T val)
{
    Array=new T[n];
    unsigned int i;
    for(i=0; i<n; i++)
        Array[i]=val;
}
///constructorul de copiere
template <class T, unsigned n>
Vector <T, n>::Vector(const Vector &ob)
{
    T*matrice=new T[n];
    unsigned int i;
    for(i=0; i<n; i++)
        matrice[i]=ob.Array[i];
    Array=matrice;
}
///operator overloading pe = pentru atribuirea dintre 2 vectori
template <class T, unsigned n>
const Vector<T, n> Vector<T, n>:: operator=(const Vector &ob)
{
    T*matrice=new T[n];
    unsigned i;
    for(i=0; i<n; i++)
        matrice[i]=ob.Array[i];
    this->Array=matrice;
    return *this;
}
///operator overloading pe * pentru produsul dintre 2 vectori
template <class T, unsigned n>
const T Vector <T, n>::operator*(Vector ob)
{
    T rez=0;
    unsigned int i;
    for(i=0; i<n; i++)
        rez+=this->Array[i]*ob.Array[i];
    return rez;
}
///operator overloading pe adunare, pentru suma dintre componentele a 2 vectori
template <class T, unsigned n>
const Vector <T, n> Vector <T, n>::operator+(Vector ob)
{
    T* rezultat;
    rezultat=new T[n];
    unsigned int i;
    for(i=0; i<n; i++)
        rezultat[i]=this->Array[i]+ob.Array[i];
    ob.setArray(rezultat);
    return ob;
}
///operator overloading pe -, pentru diferenta dintre 2 vectori
template <class T, unsigned n>
const Vector <T, n> Vector <T, n>::operator-(Vector ob)
{
    T* rezultat;
    rezultat=new T[n];
    unsigned int i;
    for(i=0; i<n; i++)
        rezultat[i]=this->Array[i]-ob.Array[i];
    Vector <T, n> Rezultat;
    Rezultat.setArray(rezultat);
    return Rezultat;
}
///operator overloading pe operatorul [] pentru accesarea unui element de pe o anumita pozitie din vector
template <class T, unsigned n>
const T Vector<T, n>::operator[](const unsigned int i)
{
    if(i<0||i>=n)
        throw "Pozitia nu apartine intervalului dintre 0 si dimensiunea vectorului";
    return this->Array[i];
}

int main()
{
    int i;
    const unsigned dim1=5;
    int val1, val2;
    cout<<"Alegeti orice valoare pentru primul vector"<<endl;
    cin>>val1;
    Vector <int, dim1> obiect1(val1);

    for(i=0; i<(int)dim1; i++)                                              ///Se testeaza functionalitatea constructorului in a atribui
        assert(val1==obiect1.getArray()[i]);                                    ///valoarea pe fiecare pozitie din vector

    assert(dim1==obiect1.getN());                                           ///Se testeaza functionalitatea metodei getN()
    cout<<"Primul vector"<<endl;
    cout<<obiect1<<endl;

    cout<<"Alegeti orice valoare pentru al doilea vector"<<endl;
    cin>>val2;
    Vector <int, dim1> obiect2(val2);
    cout<<"Al doilea vector"<<endl;
    cout<<obiect2<<endl;

    int rez=obiect1*obiect2;
    cout<<"Produsul dintre vectori "<<endl<<rez<<endl;

    Vector <int, dim1> obiect3=obiect1+obiect2;
    assert(obiect3.getArray()[0]==obiect1.getArray()[0]+obiect2.getArray()[0]);    ///Se testeaza functionalitatea metodei operator+
    cout<<"Vector suma"<<endl;                                                     ///fiindca constructorul atribuie aceeasi valoare pe fiecare pozitie,
    ///testam doar rezultatul primei valori
    cout<<obiect3<<endl;

    Vector <int, dim1> obiect4=obiect1-obiect2;
    assert(obiect4.getArray()[0]==obiect1.getArray()[0]-obiect2.getArray()[0]);
    cout<<"Vector diferenta dintre primul vector si al doilea vector"<<endl;
    cout<<obiect4<<endl;

    unsigned poz;
    cout<<"Alegeti pozitia valorii din vectorul 1 pe care doriti sa o afisati, de la 0 la dimensiunea vectorului"<<endl;
    cin>>poz;
    try                                                             ///se testeaza cazul in care pozitia indicata nu apartine intervalului dintre 0 si dim1
    {
        assert(obiect1[poz]==obiect1.getArray()[poz]);              ///se testeaza functionalitatea metodei operator[]
        cout<<"Valoarea de pe pozitia indicata"<<endl<<obiect1[poz]<<endl;
    }
    catch(const char*mesaj)
    {
        cerr<<mesaj<<endl;
    }
    int scalar;
    cout<<"Alegeti un numar de tip int pentru inmultirea lui la vectorul obiect1"<<endl;
    cin>>scalar;
    cout<<"Produsul cu scalar "<<endl;
    Vector <int, dim1> obiect5;
    obiect5=scalar*obiect1;
    assert(scalar*obiect1.getArray()[0]==obiect5.getArray()[0]);         ///se testeaza functionalitatea functiei operator*
    cout<<obiect5;                                                       ///pentru inmultirea cu scalar si a metodei getArray()
    return 0;
}
