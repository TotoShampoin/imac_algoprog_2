#include <iostream>

using namespace std;

struct Noeud{
    int donnee;
    Noeud* suivant;
};

struct Liste{
    Noeud* premier;
    // your code
    int taille;
};

struct DynaTableau{
    int* donnees;
    // your code
    int taille, capacite;
};


void initialise(Liste* liste)
{
    liste->premier = nullptr;
    liste->taille = 0;
}

bool est_vide(const Liste* liste)
{
    return liste->premier == nullptr;
}

void ajoute(Liste* liste, int valeur)
{
    if(liste->premier == nullptr) {
        liste->premier = new Noeud {valeur, nullptr};
        return;
    }
    Noeud* tmp = liste->premier;
    while(tmp->suivant) {
        tmp = tmp->suivant;
    }
    tmp->suivant = new Noeud {valeur, nullptr};
}

void affiche(const Liste* liste)
{
    Noeud* tmp = liste->premier;
    while(tmp) {
        cout << tmp->donnee << " ";
        tmp = tmp->suivant;
    }
    cout << endl;
}

int recupere(const Liste* liste, int n)
{
    Noeud* tmp = liste->premier;
    for(int i = 0; i < n; i++) {
        if(tmp == nullptr) return 0;
        tmp = tmp->suivant;
    }
    if(tmp == nullptr) return 0;
    return tmp->donnee;
}

int cherche(const Liste* liste, int valeur)
{
    Noeud* tmp = liste->premier;
    int i = 0;
    while(tmp && tmp->donnee != valeur) {
        tmp = tmp->suivant;
        i++;
    }
    if(tmp != nullptr) return i;
    return -1;
}

void stocke(Liste* liste, int n, int valeur)
{
    Noeud* tmp = liste->premier;
    for(int i = 0; i < n; i++) {
        if(tmp == nullptr) return;
        tmp = tmp->suivant;
    }
    if(tmp == nullptr) return;
    tmp->donnee = valeur;
}

void ajoute(DynaTableau* tableau, int valeur)
{
    if(tableau->taille == tableau->capacite) {
        tableau->capacite *= 2;
        int* donnees = new int[tableau->capacite];
        for(int i = 0; i < tableau->taille; i++) {
            donnees[i] = tableau->donnees[i];
        }
        delete[] tableau->donnees;
        tableau->donnees = donnees;
    }
    tableau->donnees[tableau->taille++] = valeur;
}


void initialise(DynaTableau* tableau, int capacite)
{
    tableau->donnees = new int[capacite];
    tableau->taille = 0;
    tableau->capacite = capacite;
}

bool est_vide(const DynaTableau* liste)
{
    return liste->taille == 0;
}

void affiche(const DynaTableau* tableau)
{
    for(int i = 0; i < tableau->taille; i++)
        cout << tableau->donnees[i] << " ";
    cout << endl;
}

int recupere(const DynaTableau* tableau, int n)
{
    if(n < 0 && n >= tableau->taille) return -1;
    return tableau->donnees[n];
}

int cherche(const DynaTableau* tableau, int valeur)
{
    for(int i = 0; i < tableau->taille; i++) {
        if(tableau->donnees[i] == valeur) return i;
    }
    return -1;
}

void stocke(DynaTableau* tableau, int n, int valeur)
{
    if(n < 0 && n >= tableau->taille) return;
    tableau->donnees[n] = valeur;
}

//void pousse_file(DynaTableau* liste, int valeur)
void pousse_file(Liste* liste, int valeur)
{
    Noeud* tmp = liste->premier;
    Noeud* nv = new Noeud {valeur, tmp};
    liste->premier = nv;
}

int retire_file_noeud(Noeud** noeud) {
    if((*noeud)->suivant != nullptr) {
        return retire_file_noeud(&(*noeud)->suivant);
    }
    int res = (*noeud)->donnee;
    delete *noeud;
    *noeud = nullptr;
    return res;
}

//int retire_file(Liste* liste)
int retire_file(Liste* liste)
{
    if(liste->premier == nullptr) return 0;
    return retire_file_noeud(&liste->premier);
}

//void pousse_pile(DynaTableau* liste, int valeur)
void pousse_pile(Liste* liste, int valeur)
{
    Noeud* tmp = liste->premier;
    Noeud* nv = new Noeud {valeur, tmp};
    liste->premier = nv;
}

//int retire_pile(DynaTableau* liste)
int retire_pile(Liste* liste)
{
    Noeud* tmp = liste->premier;
    Noeud* suivant = tmp->suivant;
    int res = tmp->donnee;
    delete tmp;
    liste->premier = suivant;
    return res;
}


int main()
{
    Liste liste;
    initialise(&liste);
    DynaTableau tableau;
    initialise(&tableau, 5);

    if (!est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (!est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    for (int i=1; i<=7; i++) {
        ajoute(&liste, i*7);
        ajoute(&tableau, i*5);
    }

    if (est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    std::cout << "Elements initiaux:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    std::cout << "5e valeur de la liste " << recupere(&liste, 4) << std::endl;
    std::cout << "5e valeur du tableau " << recupere(&tableau, 4) << std::endl;

    std::cout << "21 se trouve dans la liste à " << cherche(&liste, 21) << std::endl;
    std::cout << "15 se trouve dans la liste à " << cherche(&tableau, 15) << std::endl;

    stocke(&liste, 4, 7);
    stocke(&tableau, 4, 7);

    std::cout << "Elements après stockage de 7:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    Liste pile; // DynaTableau pile;
    Liste file; // DynaTableau file;

    initialise(&pile);
    initialise(&file);

    for (int i=1; i<=7; i++) {
        pousse_file(&file, i);
        pousse_pile(&pile, i);
    }

    int compteur = 10;
    while(!est_vide(&file) && compteur > 0)
    {
        std::cout << retire_file(&file) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    compteur = 10;
    while(!est_vide(&pile) && compteur > 0)
    {
        std::cout << retire_pile(&pile) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    return 0;
}
