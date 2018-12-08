#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;

void bestellvorgang();
std::vector<std::string> eisauswahl();
void wahlSpeichern (string);
int cond (std::vector<pair<string,float>>, string);
void abschluss();

std::pair <std::string,float>eis1 = std::make_pair("Capri",1.10);
std::pair <std::string,float>eis2 = std::make_pair("Nogger",1.60);
std::pair <std::string,float>eis3 = std::make_pair("Cornetto",2.30);
std::vector<std::pair<std::string,float>> eissorten;
std:: vector<string> bestellung;
std::vector<std::string> eisauswahlOut;
float saldo = 5.0;
float betrag = 0;
float wechselgeld = 0;
string wahl;
bool found;


int main()
{
    /*
    Die 3 Eissorten werden, mit ihrem Preis,
    in den Vektor 'eissorten' geladen.
    */
    eissorten.push_back(eis1);
    eissorten.push_back(eis2);
    eissorten.push_back(eis3);
    //Ausgabe der Begrüßung
    cout << "Hallo! Herzlich willkommen in der Eisdiele la consola." << endl;
    cout << "Dies sind unsere Eissortern:" << endl;
    cout << endl << endl;
    /*
    Ausgabe der 3 Eissorten:
    eissorten[i].first gibt den Namen aus
    eissorten[i].second gibt den Preis aus
    */
    for(int i =0; i<=2; i++)
    {
        cout << "- " << eissorten[i].first << " : " << eissorten[i].second << "0 Euro" << endl;
    }
    cout << endl;
    cout << endl;
    //Ausgabe der Informationen zum Vorgang
    cout << "Sie haben ein Budget von 5,00 Euro.\n" << endl;
    cout << endl;
    cout << endl;
    cout << "Als erstes dürfen Ihre beiden Freunde wählen. \nDanach sind Sie dran, falls noch Budget übrig ist. \n" << endl;
    cout << "\nDrücken Sie Enter um fortzufahren." << endl;
    cout << endl << endl << endl;
    cin.get();
    //Beginn des Bestellvorgangs
    bestellvorgang();
    //Abschluss der gesammten Bestellung
    abschluss();
    return 0;
}

/*
Der "Hauptbestellvorgang":
1. Bestellung der Freunde
2. Bestellung des Bestellers
*/
void bestellvorgang()
{
    for (int i = 1; i<=2; i++)
    {
        //Falls das Guthaben kleiner ist, als das günstigste Eis
        if(saldo < 1.1)
        {
            cout << "Sie können leider kein Eis mehr bestellen. Ihr Guthaben ist aufgebraucht." << endl << endl;
        }
        else
        {
            cout << "Freund Nummer " << i << " darf nun bestellen. \n" << endl;
            //Noch bestellbare Eissorten werden ermittelt
            eisauswahlOut = eisauswahl();
            //und ausgegeben
            cout << "Sie können noch folgende Eissorten wählen: " << endl << endl;
            int s = eisauswahlOut.size();
            for (int j=0; j<s; j++)
            {
                cout << "- " << eisauswahlOut[j] << endl;
            }
            cout << endl;
            //Aufforderung die Bestellung ein zu geben.
            cout << "Welches Eis wollen Sie bestellen? \n" << endl;
            cin >> wahl;
            //Falls die Bestellung nicht einer der verfügbaren Eissorten entspricht, erneut auffordern.
            while (std::find(eisauswahlOut.begin(),eisauswahlOut.end(), wahl)==eisauswahlOut.end())
            {
                cout << "Die Auswahl ist nicht möglich." << endl;
                cout << "Bitte geben Sie eine der möglichen Sorten an." << endl;
                cin >> wahl;
            }
            //Bestellung wird in den Vektor 'bestellung' gespeichert und die nötigen Beträge berechnet
            wahlSpeichern(wahl);
            //Ausgabe der Auswahl, mit Preis und das restliche Budget
            int c = cond(eissorten, wahl);
            cout << endl;
            cout << "Ihre Bestellung:" << endl;
            cout << eissorten[c].first << ": " << eissorten[c].second << "0 Euro" << endl;
            cout << endl;
            printf("Ihr vorhandenes Budget: %.2f Euro\n", saldo);
            cout << endl;
            cin.get();
            cout << "\nDrücken Sie Enter um fortzufahren." << endl;
            cin.get();
            cout << endl << endl;
        }
    }
    /*
    Bestellung des Bestellers aufnehmen.
    Ablauf wie bei Freunden.
    */
        if(saldo < 1.1)
        {
            cout << "Sie können leider kein Eis mehr bestellen. Ihr Guthaben ist aufgebraucht." << endl << endl;
            cin.get();
            cout << "\nDrücken Sie Enter um fortzufahren." << endl;
        }
        else
        {
            cout << "Nun dürfen Sie bestellen. \n" << endl;
            eisauswahlOut = eisauswahl();
            cout << "Sie können noch folgende Eissorten wählen: " << endl << endl;
            int s = eisauswahlOut.size();
            for (int j=0; j<s; j++)
            {
                cout << "- " << eisauswahlOut[j] << endl;
            }
            cout << endl;
            cout << "Welches Eis wollen Sie bestellen? \n" << endl;
            cin >> wahl;
            bool part = std::find(eisauswahlOut.begin(),eisauswahlOut.end(), wahl)==eisauswahlOut.end();
            while (part)
            {
                cout << "Die Auswahl ist nicht möglich." << endl;
                cout << "Bitte geben Sie eine der möglichen Sorten an." << endl;
                cin >> wahl;
                part = std::find(eisauswahlOut.begin(),eisauswahlOut.end(), wahl)==eisauswahlOut.end();
            }
            wahlSpeichern(wahl);
            int c = cond(eissorten, wahl);
            cout << endl;
            cout << "Ihre Bestellung:" << endl;
            cout << eissorten[c].first << ": " << eissorten[c].second << "0 Euro" << endl;
            cout << endl << endl;
        }
}

/*
Ermittelt die noch bestellbaren Eissorten
und übergibt sie in einem Vektor.
*/
std::vector<std::string> eisauswahl()
{
    std:: vector<string> moeglEissorten;
    //Nur noch Capri möglich
    if(1.1 <= saldo && saldo < 1.6)
    {
        moeglEissorten.push_back("Capri");
    }
    else
    {
        //Capri und Nogger möglich
        if(1.6 <= saldo && saldo < 2.3)
        {
            moeglEissorten.push_back("Capri");
            moeglEissorten.push_back("Nogger");
        }
        else
        {
            //Alle Eissorten möglich
            moeglEissorten.push_back("Capri");
            moeglEissorten.push_back("Nogger");
            moeglEissorten.push_back("Cornetto");
        }
    }
    //Rückgabe der bestellbaren Eissorten
    return moeglEissorten;
}

/*

*/
void wahlSpeichern (string a)
{
    int c = cond(eissorten, a);
    betrag = betrag + eissorten[c].second;
    saldo = saldo - eissorten[c].second;
    bestellung.push_back(a);

}

int cond (std::vector<pair<string,float>> b, string x)
{
    int out;
    int s = b.size();
    for(int i=0; i<=s;i++)
    {
        if(b[i].first == x)
        {
            out = i;
        }
        else
        {
            continue;
        }
    }
    return out;
}

void abschluss ()
{
    int eurobetrag = (int)betrag;
    float centbetrag = 100*(betrag - (float)eurobetrag);
    int eurowechsel = (int)saldo;
    float centwechsel = 100*(saldo- (float)eurowechsel);
    cout << endl << endl << endl;
    cout << "Der Bestellvorgang ist nun beendet. \n" << endl;
    cout << "Ihre Bestellung: \n" << endl;
    int s = bestellung.size();
    for (int i = 0; i<s;i++)
    {
        cout << bestellung[i] << endl;
    }
    cout << endl << endl;
    cout << "Ihr Rechnungsbetrag: \n" << endl;
    cout << eurobetrag << " Euro und " << centbetrag << " Cent." << endl;
    cout << endl << endl;
    cout << "Ihr Wechselgeld: \n" << endl;
    cout << eurowechsel << " Euro und " << centwechsel << " Cent." << endl;
}
