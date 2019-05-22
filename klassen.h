/* Aufgabe 1 - Musterlösung */
/* klassen.h                */

#include <iostream>
#include <string>

#ifndef KLASSEN_H
#define KLASSEN_H

using namespace std;

/************************************************/
/* Klasse Datum                                 */
/************************************************/

class Datum
{
private:
    int tag,monat,jahr;

public:
    Datum()
    {
        this->tag = 0;
        this->monat = 0;
        this->jahr = 0;
    }

    Datum(int t, int m, int j);
    void setDatum(int t, int m, int j);

    friend ostream& operator<<(ostream &os, Datum &d);

    virtual ~Datum(){}
};

inline Datum::Datum(int t, int m, int j):tag(t),monat(m),jahr(j)
{
}

/************************************************/
/* Klasse Lebensmittel                          */
/************************************************/

class Lebensmittel
{
private:

protected:
    string Bezeichnung;
    Datum Mhd;

public:

    Lebensmittel();
    Lebensmittel(string &b, Datum &d);
    virtual ~Lebensmittel();
    virtual double preis() = 0;
    virtual void zeige();

    void setBezeichnung(string &b);
    void setMhd(Datum &d);

    string getBezeichnung(void);
    Datum getMhd(void);

};

/************************************************/
/* Klasse KiloWare                              */
/************************************************/

class KiloWare : public Lebensmittel
{
private:

protected:
    double Menge;
    double PreisPerKilo;

public:
    KiloWare();
    KiloWare(string b, Datum &d, double m, double ppk);
    ~KiloWare();
    double preis();
    void zeige();

    void setMenge(double m);
    void setPreisPerKilo(double ppk);

    double getMenge(void);
    double getPreisPerKilo(void);

};

/************************************************/
/* Klasse StueckWare                            */
/************************************************/

class Stueckware : public Lebensmittel
{
private:

protected:
    int Menge;
    double PreisPerStueck;

public:
    Stueckware();
    Stueckware(string b, Datum &d, int m, double pps);
    ~Stueckware();
    double preis();
    void zeige();

    void setMenge(int m);
    void setPreisPerStueck(double pps);

    int getMenge(void);
    double getPreisPerStueck(void);
};

/************************************************/
/* Klasse Warenkorb                             */
/************************************************/

class Warenkorb
{
private:
    static int Aenderung;
    int anzahl;
    int max;
    Lebensmittel **korb;

protected:

public:
    Warenkorb();
    ~Warenkorb();

    bool einfuegen(Lebensmittel *l);
    bool entfernen(string bezeichnung);

    double preis();
    void zeige();

    int getAnzahl();
    int getMax();
    bool isEmpty();

};

template <typename T1, typename T2>
class Warenkorb2;

//Verkettete Listen-Objekt
template <typename _ValueType>
struct Node
{
    friend class Warenkorb2<_ValueType, _ValueType>;
    typedef _ValueType value_t;

    Node(value_t const& value = value_t(), Node<_ValueType>* ptr_next = NULL)
        : m_value(value), m_next(ptr_next)
    {}

private:
    value_t m_value;
    Node<_ValueType>* m_next;
};

//Verwaltung der Objekte
template <typename T1, typename T2>
class Warenkorb2
{
    Node<T>* m_data;
    Node<T>* startPoint;
    std::size_t m_size;

public:
    Warenkorb2()
        : m_size(0), m_data(NULL)
    {}
    ~Warenkorb2();

    bool empty() const { return m_size == 0; }
    void einfuegen(T const& value);
    bool entfernen(T const& value);
    void zeige();
};

template <typename T1, typename T2>
Warenkorb2<T>::~Warenkorb2()
{
    while (m_data != NULL)
    {
        Node<T>* ptr_tmp(m_data->m_next);
        delete m_data;
        m_data = ptr_tmp;
    }
}

template <typename T1, typename T2>
void Warenkorb2<T>::einfuegen(T const& value)
{
    //Erster Wert wird eingefügt
    if (empty())
    {
        m_data = new Node<T>(value);
        startPoint = m_data;
        m_size++;
        return;
    }

    //Nächstes Objekt füllen
    m_data->m_next = new Node<T>(value);
    //Auf nächstes Objekt in Liste wechseln
    m_data = m_data->m_next;
    m_size++;
}

template <typename T1, typename T2>
bool Warenkorb2<T>::entfernen(T const& value)
{
    if(value == startPoint)
    {
        Node<T> *tmp = startPoint;
        startPoint = startPoint->m_next;
        delete[] tmp;
        m_size--;
    }
    else
    {
        Node<T> *tmp = startPoint;
        for (int i =0; i < m_size - 1;i++)
        {
            if(tmp->m_next == value)
            {
               Node<T> *toDelete = tmp->m_next;
               tmp->m_next = toDelete->m_next;
               delete[] toDelete;
               m_size--;
            }
        }
    }
    return true;
}

template <typename T1, typename T2>
void Warenkorb2<T>::zeige()
{
   Node<T> *tmp = startPoint;
   for (int i = 0;i < m_size; i++)
   {
        cout << tmp << endl;
        tmp = tmp->m_next;
   }
}
#endif // KLASSEN_H
