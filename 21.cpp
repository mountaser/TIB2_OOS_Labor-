#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

// Eigene Exceptionklasse "MyException"
// abgeleitet von Exception
class MyException : public exception {
    // HIER
    string _filename;
    int _line;
    string _description;
public:
    // Konstruktor
    MyException(const string& filename, int line, const string& description)
        : _filename(filename), _line(line), _description(description) {}

    // Überschreiben der what()-Methode
    const char* what() const noexcept override {
        return ("Fehler '" + _description + "' aufgetreten in Datei " + _filename + ", Zeile: " + to_string(_line)).c_str();
    }
};

// Eigene Exceptionklasse "ElefantMeetsMouse"
// abgeleitet von MyException
class ElefantMeetsMouse : public MyException {
    // HIER
    string _filename;
    int _line;
    string _description;
public:
    // Konstruktor
    ElefantMeetsMouse(const string& filename, int line,const string& description)
        : MyException(filename, line, description) {}
};

// Klasse der Tiere
class Animal
{
    // Name des Tiers
    string _name;

public:
    // Konstruktor
    Animal()
    {
        cout << "Bitte Namen des Tieres eingeben: ";
        cin >> _name;
    };
    // virtuelle print-Funktion
    virtual void print(bool nl) const
    {
        cout << _name;
        if (nl)
        {
            cout << endl;
        }
    }
    virtual Animal *clone() const = 0;
};

// Klasse "Elefant"
// abgeleitet von Animal
class Elefant : public Animal {
    // HIER
    Animal* clone() const override {
        return new Elefant(*this);
    }
};

// Klasse "Tiger"
// abgeleitet von Animal
class Tiger : public Animal {
    // HIER
    Animal* clone() const override {
        return new Tiger(*this);
    }
};

// Klasse "Mouse"
// abgeleitet von Animal
class Mouse : public Animal {
    // HIER
    Animal* clone() const override {
        return new Mouse(*this);
    }
};

class Zoo
{
    // Name des Zoos
    string _name;
    // Die Tiere werden in einem Vektor gespeichert
    vector<Animal *> animals;

public:
    // Konstruktor
    Zoo()
    {
        // Name zuweisen
        cout << "Bitte Name des Zoos eingeben: ";
        cin >> _name;
        // Wenn der String kuerzer als 4 Zeichen ist,
        // dann MyException werfen
        // Nutzen Sie die Praeprozessormakros __LINE__ und __FILE__

        // HIER
        if (_name.length() < 4) {
            throw MyException(__FILE__, __LINE__, "Zooname zu kurz");
        }
        
        // Ansonsten, den 5. Buchstaben des Namens gross machen
        _name.at(4) = toupper(_name.at(4));
    }

    // Ein Tier dem Zoo hinzufuegen
    void add_animal(const Animal &animal)
    {
        // Wenn ein Elefant nach einer Maus eingefuegt wird, oder anders herum
        // dann Ausnahme werfen
        // Nutzen Sie die Praeprozessormakros __LINE__ und __FILE__
        
        // HIER
     if (!animals.empty()) {
        if (dynamic_cast<const Elefant*>(animals.back()) && dynamic_cast<const Mouse*>(&animal)) {
            throw ElefantMeetsMouse(__FILE__, __LINE__,"Elefant trifft auf Maus");
        }
        else if (dynamic_cast<const Mouse*>(animals.back()) && dynamic_cast<const Elefant*>(&animal)) {
            throw ElefantMeetsMouse(__FILE__, __LINE__,"Elefant trifft auf Maus");
        }
    }
        

        // sonst Tier hinzufuegen

        // HIER
        animals.push_back(animal.clone());

    }
    // Alle Zootiere ausgeben
    void print() const
    {
        // HIER
        for (const Animal* animal : animals) {
            animal->print(true);
        }
        
    }
};

int main(int argc, char *argv[])
{
    char choice;
    string name;
    try {
        Zoo zoo;
        do
        {
            cout << endl
                 << "Bitte Tierart auswaehlen:" << endl;
            cout << "1 = Elefant" << endl;
            cout << "2 = Tiger" << endl;
            cout << "3 = Maus" << endl;
            cout << "e = Ende mit Eingabe" << endl;
            cout << "Eingabe: ";
            cin >> choice;
            switch (choice)
            {
            case '1':
            {
                Elefant elefant = Elefant();
                zoo.add_animal(elefant);
                break;
            }
            case '2':
            {
                Tiger tiger = Tiger();
                zoo.add_animal(tiger);
                break;
            }
            case '3':
            {
                Mouse mouse = Mouse();
                zoo.add_animal(mouse);
                break;
            }
            case 'e':
                break;
            default:
                // Einen String als Ausnahme werfen
                // HIER
                throw string("Fehlerhafte Eingabe!");
            }

            cout << endl;
            zoo.print();
        } while (choice != 'e');
    }
    // Ausnahmen auffangen
    // Speziellste Ausnahme auffangen und ausgeben
    catch (ElefantMeetsMouse &e)
    {
    cout << e.what() << endl;
    }
    // MyException auffangen und ausgeben
    // HIER
    catch (MyException& e) {
        cout << e.what() << endl;
    }
    

    // Alle anderen Standardausnahmen auffangen und ausgeben
    // HIER
    catch (exception& e) {
        cout << "Standardausnahme: " << e.what() << endl;
    }
    

    // Alle Strings auffangen und ausgeben
    // HIER
    catch (string& s) {
        cout << s << endl;
    }
    

    // Alle anderen Ausnahmen auffangen
    // HIER
    catch (...) {
        cout << "Unbekannte Ausnahme aufgetreten" << endl;
    }
    
    return 0;
}