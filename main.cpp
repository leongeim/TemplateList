#include "klassen.h"
int main()
{
    Warenkorb2<Lebensmittel> korb;

    Datum date = Datum(1,1,1900);
    Stueckware temp = Stueckware("Hallo", date, 1, 10);
    Stueckware temp2 = Stueckware("Test", date, 2, 20);
    Stueckware temp3 = Stueckware("123", date, 3, 30);
    Stueckware temp4 = Stueckware("2135", date, 4, 40);
    KiloWare temp5  = KiloWare("Kilo1", date, 1, 10);
    KiloWare temp6  = KiloWare("Kilo2", date, 2, 20);
    KiloWare temp7  = KiloWare("Kilo3", date, 3, 30);
    KiloWare temp8  = KiloWare("Kilo4", date, 4, 40);
    korb.einfuegen(temp);
    korb.einfuegen(temp2);
    korb.einfuegen(temp3);
    korb.einfuegen(temp4);
    korb.einfuegen(temp5);
    korb.einfuegen(temp6);
    korb.einfuegen(temp7);
    korb.einfuegen(temp8);

    korb.zeige();


}
