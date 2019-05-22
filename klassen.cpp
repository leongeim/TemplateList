/* Aufgabe 1 - Musterlösung */
/* klassen.cpp              */

#include "klassen.h"

/************************************************/
/* Klasse Datum                                 */
/************************************************/

string monat[] = {"", "Januar", "Februar", "Maerz", "April",
                  "Mai", "Juni", "Juli", "August", "September", "Oktober",
                  "November", "Dezember"};

void Datum::setDatum(int t, int m, int j)
{
    this->tag = t;
    this->monat = m;
    this->jahr = j;
}

ostream& operator<<(ostream &os, Datum &d)
{
    if(d.tag == 0 || d.monat == 0 || d.jahr == 0)
    {
        os << "Datum nicht inisitalisiert" << endl;
    }
    else
    {
       os << d.tag << ". " << monat[d.monat] << " " << d.jahr << endl;
    }

    return os;
}

/************************************************/
/* Klasse Lebensmittel                          */
/************************************************/

Lebensmittel::Lebensmittel()
{
    this->Bezeichnung = "noch nicht initialisiert";
}

Lebensmittel::Lebensmittel(string &b, Datum &d)
{
    this->Bezeichnung = b;
    this->Mhd = d;
}

Lebensmittel::~Lebensmittel()
{

}

void Lebensmittel::zeige()
{
    cout << "Artikel: " << this->Bezeichnung << endl;
    cout << "Mind. haltbar bis : " << this->Mhd;
}

void Lebensmittel::setBezeichnung(string &b)
{
    this->Bezeichnung = b;
}

void Lebensmittel::setMhd(Datum &d)
{
    this->Mhd = d;
}

string Lebensmittel::getBezeichnung(void)
{
    return this->Bezeichnung;
}

Datum Lebensmittel::getMhd(void)
{
    return this->Mhd;
}

/************************************************/
/* Klasse KiloWare                              */
/************************************************/

KiloWare::KiloWare()
{
    this->Menge = 0.0;
    this->PreisPerKilo = 0.0;
}

KiloWare::KiloWare(string b, Datum &d, double m, double ppk)
    :Lebensmittel(b,d)
{
    this->Menge = m;
    this->PreisPerKilo = ppk;
}

KiloWare::~KiloWare()
{

}

double KiloWare::preis()
{
    return this->Menge * this->PreisPerKilo;
}

void KiloWare::zeige()
{
    cout << endl;
    Lebensmittel::zeige();
    cout << "Menge: " << this->Menge << " kg" << endl;
    cout << "Preis pro Kilo: " << this->PreisPerKilo << " Euro" << endl;
}

void KiloWare::setMenge(double m)
{
    this->Menge = m;
}

void KiloWare::setPreisPerKilo(double ppk)
{
    this->PreisPerKilo = ppk;
}

double KiloWare::getMenge(void)
{
   return this->Menge;
}

double KiloWare::getPreisPerKilo(void)
{
   return this->PreisPerKilo;
}

/************************************************/
/* Klasse StueckWare                            */
/************************************************/

Stueckware::Stueckware()
{
    this->Menge = 0;
    this->PreisPerStueck = 0.0;
}

Stueckware::Stueckware(string b, Datum &d, int m, double pps)
    :Lebensmittel(b,d)
{
    this->Menge = m;
    this->PreisPerStueck = pps;
}

Stueckware::~Stueckware()
{

}

double Stueckware::preis()
{
    return ((double)this->Menge * this->PreisPerStueck);
}

void Stueckware::zeige()
{
    cout << endl;
    Lebensmittel::zeige();
    cout << "Menge: " << this->Menge << " Stueck" << endl;
    cout << "Preis pro Stueck: " << this->PreisPerStueck << " Euro" << endl;
}

void Stueckware::setMenge(int m)
{
    this->Menge = m;
}

void Stueckware::setPreisPerStueck(double pps)
{
    this->PreisPerStueck = pps;
}

int Stueckware::getMenge(void)
{
    return this->Menge;
}

double Stueckware::getPreisPerStueck(void)
{
    return this->PreisPerStueck;
}

/************************************************/
/* Klasse Warenkorb                             */
/************************************************/

 int Warenkorb::Aenderung = 2;

 Warenkorb::Warenkorb()
 {
     int i;

     this->anzahl = 0;
     this->max = Warenkorb::Aenderung;
     this->korb = new Lebensmittel*[this->max];

     for(i=0;i<this->max;i++)
     {
         this->korb[i] = 0;
     }
 }

 Warenkorb::~Warenkorb()
 {
     delete[] this->korb;
 }

 bool Warenkorb::einfuegen(Lebensmittel *l)
 {
     if(this->anzahl < this->max)
     {
         this->korb[this->anzahl] = l;
         this->anzahl++;

         return true;
     }
     else
     {
         Lebensmittel** tmp;
         int i;

         tmp = this->korb;
         this->max += Warenkorb::Aenderung;
         this->korb = new Lebensmittel*[this->max];

         for(i=0;i<this->anzahl;i++)
         {
             this->korb[i] = tmp[i];
         }

         delete[] tmp;

         this->korb[this->anzahl] = l;
         this->anzahl++;

         return true;
     }

 }

 bool Warenkorb::entfernen(string bezeichnung)
 {
    bool res = false;

    if(this->anzahl == 0)
    {
        return res;
    }
    else
    {
        int i,j;

        for(i=0;i<this->anzahl;i++)
        {
            if(this->korb[i]->getBezeichnung() == bezeichnung)
            {
                for(j=i;j<this->anzahl-1;j++)
                {
                    this->korb[j] = this->korb[j+1];
                }

                this->anzahl--;
                i--;
                res = true;
            }
        }

        return res;
    }
 }

 double Warenkorb::preis()
 {
     int i;
     double preis = 0.0;

     if(this->anzahl == 0)
     {
         return preis;
     }
     else
     {
        for(i=0;i<this->anzahl;i++)
        {
            preis += this->korb[i]->preis();
        }

        return preis;
     }
 }

 void Warenkorb::zeige()
 {
     int i;

     if(this->anzahl == 0)
     {
         cout << "Warenkorb ist leer." << endl;
     }
     else
     {
        for(i=0;i<this->anzahl;i++)
        {
            this->korb[i]->zeige();
        }
     }
 }

 int Warenkorb::getAnzahl()
 {
     return this->anzahl;
 }

 int Warenkorb::getMax()
 {
     return this->max;
 }

 bool Warenkorb::isEmpty()
 {
    if(this->anzahl==0)
    {
        return true;
    }
    else
    {
        return false;
    }
 }
