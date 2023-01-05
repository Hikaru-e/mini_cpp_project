#include <iostream>
#include <string>
#include <string.h>
#include <conio.h>

using namespace std;

// Toutes les structures utilisées sont des listes aimées
// l'utilité de cette structure réside lors de la création de règles, elle aide à créer une liste de conditions et également une liste de résultats

struct liste
{ 
    string el;
    liste *next;
};

struct fait
{
    string el;
    char test;
    fait *next;
};

struct regle
{
    liste *condition;
    liste *resultat;
    char testr;
    regle *suivant;
};

// ######################################################

// Prototypes des fonctions utilisees

fait *Creation_Base_Fait(fait *F);
liste *creation(int n);
regle *Creation_Base_Regle(regle *Rr);
void Ajoute_Regle(regle *&R);
void Ajoute_Fait(fait *&F, string el, char x);
void Supprimer_Fait( fait *&F );
void Supprimer_Regle( regle *&R );
void Afficher_Base_Faits(fait *F);
void Afficher_Base_Regles(regle *R);
void Afficher_Base_Regles_Sans_Resultats(regle *R);
int nombre_liste(liste *li);
int egual(liste *regcon, liste *L2);
void Afficher_Resultat(fait *M);
int Moteur_Inference(liste *L, fait *&F, regle *&R);

// ######################################################

// Cette fonction est utilisée dans un premier temps pour créer une base de faits, elle donne la possibilité d'ajouter plusieurs faits jusqu'à ce que 
// l'utilisateur appuie au clavier sur le chiffre 0, elle prend en argument un pointeur vers une structure 'fait'

fait *Creation_Base_Fait(fait *F)
{
    int k;

    F = new fait;
    cout << "\nDonner une base de faits : ";
    fflush(stdin);
    getline(cin,F->el);
    F->test = '#';
    F->next = NULL;

    fait *p = F;

    cout << "\nContinuer ... 0/1 : ";
    cin >> k;
    while (k != 0)
    {
        fait *q = new fait;
        cout << "\nDonner une base fait : ";
        fflush(stdin);
        getline(cin,q->el);
        q->test = '#';
        q->next = NULL;
        p->next = q;
        p = q;

        cout << "\nContinuer ... 0/1 : ";
        cin >> k;
    }
    return F;
}

// ##############################################################

// Cette fonction permet ici de créer une liste de listes chainees basée sur un entier, cette fonction est utilisée dans la fonction de base de règles ci-dessous

liste *creation(int n)
{
    liste *tete = new liste();
    cout << "\n[" << 1 << "]. ";
    fflush(stdin);
    getline(cin,tete->el);
    tete->next = NULL;
    liste *q = tete;

    for (int i = 2; i <= n; i++)
    {
        cout << "\n[" << i << "]. ";
        liste *p = new liste();
        fflush(stdin);
        getline(cin,p->el);
        p->next = NULL;
        q->next = p;
        q = p;
    }
    return tete;
}

//------------------------------------------------

// Cette fonction est utilisée dans un premier temps pour créer une base de règles, elle donne la possibilité d'ajouter plusieurs règles jusqu'à ce que l'utilisateur 
// appuie au clavier sur le chiffre 0, elle prend en argument un pointeur vers une structure 'regle'

regle *Creation_Base_Regle(regle *Rr)
{
    int n1, n2;
    int k;
    Rr = new regle;

    cout << "\nDonner le nombre de conditions : ";
    cin >> n1;
    Rr->condition = creation(n1);

    cout << "\nDonner le nombre de resultats : ";
    cin >> n2;
    Rr->resultat = creation(n2);

    Rr->testr = '*';
    Rr->suivant = NULL;

    cout << "\nContinuer ... 0/1 : ";
    cin >> k;
    regle *p = Rr;
    while (k != 0)
    {
        regle *q = new regle;

        cout << "\nDonner le nombre de conditions : ";
        cin >> n1;
        q->condition = creation(n1);

        cout << "\nDonner le nombre de resultats : ";
        cin >> n2;
        q->resultat = creation(n2);

        q->testr = '*';
        q->suivant = NULL;
        p->suivant = q;
        p = q;

        cout << "\nContinuer ... 0/1 : ";
        cin >> k;
    }
    return Rr;
}

// ##############################################################

//cette fonction doit être utilisée après la création de la base de règles et rien d'autre, mais elle peut être utilisée dans un premier temps même 
//si la base de règles n'est pas créée, pourquoi penser ? parce que l'utilisation de la fonction de création de la base de règles remplacera les données précédentes, 
//et c'est quelque chose que nous ne voulons pas

void Ajoute_Regle(regle *&R)
{
    int n1, n2;
    regle *nouveau = new regle;

    cout << "\nDonner le nombre de condition : ";
    cin >> n1;
    nouveau->condition = creation(n1);

    cout << "\nDonner le nombre de resultat : ";
    cin >> n2;
    nouveau->resultat = creation(n2);

    nouveau->testr = '*';

    nouveau->suivant = NULL;

    regle *p = R;

    while (p->suivant != NULL)
        p = p->suivant;

    p->suivant = nouveau;
}

// ######################################################

// Cette fonction est similaire à celle ci-dessus, sauf qu'elle traite de la base des faits
void Ajoute_Fait(fait *&F, string el, char x)
{
    fait *nouveau = new fait;
    nouveau->el = el;
    nouveau->test = x;
    nouveau->next = NULL;

    fait *p = F;
    while (p->next != NULL)
        p = p->next;

    p->next = nouveau;
}

// ######################################################

void Supprimer_Fait( fait *&F )
{
    // Supprimer un fait
    cout << "Entrer la valeur du fait pour la supprimer: ";
    string name;
    getline(cin,name);

    // Trouver le fait dans la liste chainee
    fait *prev = nullptr;
    fait *curr = F;
    while (curr != nullptr)
    {
        if (curr->el == name)
        {
            // Supprimer le fait de la liste chainee
            if (prev == nullptr)
            {
                F = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

}

// ######################################################

void Supprimer_Regle( regle *&R )
{
    // Supprimer une regke
    cout << "Entrer l'index du Regle pour la supprimer: ";
    int index_r;
    cin >> index_r;
    index_r++;
    // Trouver la regle dans la liste chainee
    regle *prev = nullptr;
    regle *curr = R;
    for (int i = 0; i < index_r && curr != nullptr; i++)
    {
        prev = curr;
        curr = curr->suivant;
    }

    // Supprimer la regle de la liste chainee
    if (curr != nullptr)
    {
        if (prev == nullptr)
        {
            R = curr->suivant;
        }
        else
        {
            prev->suivant = curr->suivant;
        }
        delete curr;
    }

}
// ######################################################

void Afficher_Base_Faits(fait *F)
{
    fait *ff = F;
    int itr=1;
    cout << "\n========================================================\n";
    cout << "\nLes faits : \n\n";
    while (ff != NULL)
    {
        cout << "\t["<< itr << "]. "<< ff->el << "\n";
        ff = ff->next;
        itr++;
    }
}    

// ######################################################

void Afficher_Base_Regles(regle *R)
{
    regle *rr = R;
    int itr=1;
    int itr_r=1;
    int itr_c=1;
    
    cout << "\nLes regles : \n";
    while (rr != NULL)
    {
        cout << "\n========================================================\n";
        cout << "\n\t\tRegle " << itr << " : \n";
        liste *f = rr->condition;
        liste *p = rr->resultat;

        cout << "Conditions : \n";
        while (f != NULL)
        {
            cout << "\t["<< itr_c << "]. "<< f->el << "\n";
            f = f->next;
            itr_c++;
        }
        
        
        cout << "\nResultats : \n";
        while (p != NULL)
        {
            cout << "\t["<< itr_r << "]. "<< p->el << "\n";
            p = p->next;
            itr_r++;
        }
        rr = rr->suivant;
        itr++;
        itr_r=1;
        itr_c=1;
    }
}
// ######################################################

void Afficher_Base_Regles_Sans_Resultats(regle *R)
{
    regle *rr = R;
    int itr=1;
    int itr_c=1;
    
    cout << "\nLes regles : \n";
    while (rr != NULL)
    {
        cout << "\n========================================================\n";
        cout << "\n\t\tRegle " << itr << " : \n";
        liste *f = rr->condition;


        cout << "Conditions : \n";
        while (f != NULL)
        {
            cout << "\t["<< itr_c << "]. "<< f->el << "\n";
            f = f->next;
            itr_c++;
        }

        rr = rr->suivant;
        itr++;

        itr_c=1;
    }
}
// ######################################################

int nombre_liste(liste *li)
{ // nombre d'élément d'une liste
    int cpt = 0;
    for (liste *p = li; p != NULL; p = p->next)
        cpt++;

    return cpt;
}

// ######################################################

int egual(liste *regcon, liste *L2)
{ // test égalité de deux listes
    int cpt = 0;

    for (liste *p2 = L2; p2 != NULL; p2 = p2->next)
        for (liste *reg = regcon; reg != NULL; reg = reg->next)
            if (p2->el.compare(reg->el)==0)
                cpt++;

    if ((nombre_liste(L2) == cpt))
        return 1;
    else
        return 0;
}

// ######################################################

void Afficher_Resultat(fait *M)
{ // affichage des résultat éxécution de moteur inference
    fait *p = M;

    while (p != NULL)
    {
        if (p->test == '*')
        {
            cout << "\n========================================================\n";
            cout << "\nResultat est : " << p->el;
            cout << "\n\n========================================================\n";
        }

        p = p->next;
    }
}
// ######################################################

int Moteur_Inference(liste *L, fait *&F, regle *&R)
{
    Afficher_Base_Regles_Sans_Resultats(R);
    regle *r = R;
    int n1;
    cout << "\n========================================================\n";
    cout << "\nEntrer le nombre de conditions : ";
    fflush(stdin);
    cin >> n1;
    L = creation(n1);

    while (r != NULL)
    {
        if (r->testr == '*')
            if ((nombre_liste(L)) == (nombre_liste(r->condition)))
                if (egual(r->condition, L) == 1)
                {
                    r->testr = '#';
                    for (liste *p = r->resultat; p != NULL; p = p->next)
                        Ajoute_Fait(F, p->el, '*');

                    return 0;
                }
        r = r->suivant;
    }

    Afficher_Resultat(F);
    return 0;
}

// ######################################################

void afficherMenu(void) // affichage de menu
{
    system("cls");
    system("color 1F");
cout<< "\n\n\t  __       __  ___  ___        ___     ___      __   ___  __  ___ "
<< "\n\t /__` \\ / /__`  |  |__   |\\/| |__     |__  \\_/ |__) |__  |__)  |"  
<< "\n\t .__/  |  .__/  |  |___  |  | |___    |___ / \\ |    |___ |  \\  |  \n\n";


    cout << "\t\t       ---------------------------------------  \n";
    cout << "\t\t       |                                     |  \n";
    cout << "\t\t       | 1- Saisir les faits .               |  \n";
    cout << "\t\t       | 2- Saisir les regles .              |  \n";
    cout << "\t\t       |                                     |  \n";
    cout << "\t\t       | 3- Ajouter une regle.               |  \n";
    cout << "\t\t       | 4- Ajouter un fait.                 |  \n";
    cout << "\t\t       |                                     |  \n";
    cout << "\t\t       | 5- Supprimer un fait                |  \n";
    cout << "\t\t       | 6- Supprimer une regle              |  \n";
    cout << "\t\t       |                                     |  \n";
    cout << "\t\t       | 7- Affichager base de faits.        |  \n";
    cout << "\t\t       | 8- Affichager base de regle.        |  \n";
    cout << "\t\t       |                                     |  \n";
    cout << "\t\t       | 9- Moteur d inference.              |  \n";
    cout << "\t\t       |                                     |  \n";
    cout << "\t\t       | 0- Quiter.                          |  \n";
    cout << "\t\t       |                                     |  \n";
    cout << "\t\t       ---------------------------------------  \n ";
}

int main()
{

    regle *RRR = NULL;
    regle *R = NULL; 
    fait *FFF = NULL;
    fait *F = NULL;
    liste *LL = NULL;
    string K;
    int nn;
    char choix;

    do
    {

        afficherMenu();
        choix = getch();
        switch (choix)
        {
        case '1':
            system("cls");
            system("COLOR 7");
            cout << "\n-----------------------------------------------------\n";
            cout << "\n\tCHARGEMENT BASE DE FAIT\n ";
            FFF = Creation_Base_Fait(F);
            fflush(stdin);
            cout <<"\n\n\t\aPRESS ANY KEY TO CONTINUE ...";
            getch();
            break;

        case '2':
            system("cls");
            system("COLOR 7");
            cout << "\n-----------------------------------------------------\n";
            cout << "\n\tCHARGEMENT BASE DE REGLE\n ";
            RRR = Creation_Base_Regle(R);
            cout <<"\n\n\t\aPRESS ANY KEY TO CONTINUE ...";
            getch();
            break;

        case '3':
            system("cls");
            system("COLOR 7");
            cout << "\n-----------------------------------------------------\n";
            cout << "\n\tAJOUTE UNE REGLE\n ";
            Ajoute_Regle(RRR);
            cout <<"\n\n\t\aPRESS ANY KEY TO CONTINUE ...";
            getch();
            break;

        case '4':
            system("cls");
            system("COLOR 7");
            cout << "\n-----------------------------------------------------\n";
            cout << "\n\tAJOUTE UN FAIT\n ";
            cout << "\nDonner une base de fait : ";
            fflush(stdin);
            getline(cin,K);
            Ajoute_Fait(FFF, K, '#');
            cout <<"\n\n\t\aPRESS ANY KEY TO CONTINUE ...";
            getch();
            break;

        case '5':
            system("cls");
            system("COLOR 7");
            cout << "\n-----------------------------------------------------\n";
            cout << "\n\tSUPPRIMER UN FAIT\n ";
            Supprimer_Fait(FFF);
            cout <<"\n\n\t\aPRESS ANY KEY TO CONTINUE ...";
            getch();
            break;


        case '6':
            system("cls");
            system("COLOR 7");
            cout << "\n-----------------------------------------------------\n";
            cout << "\n\tSUPPRIMER UNE REGLE\n ";
            Supprimer_Regle(RRR);
            cout <<"\n\n\t\aPRESS ANY KEY TO CONTINUE ...";
            getch();
            break;

        case '7':
            system("cls");
            system("COLOR 7");
            cout << "\n-----------------------------------------------------\n";
            cout << "\n\tAFFICHAGE BASE DE FAITS\n ";
            cout << "\nLa base de faits est : \n";
            Afficher_Base_Faits(FFF);
            cout <<"\n\n\t\aPRESS ANY KEY TO CONTINUE ...";
            getch();
            break;

        case '8':
            system("cls");
            system("COLOR 7");
            cout << "\n-----------------------------------------------------\n";
            cout << "\n\tAFFICHAGE BASE DE REGLES\n ";
            cout << "\nLa base de regles est : \n";
            Afficher_Base_Regles(RRR);
            cout <<"\n\n\t\aPRESS ANY KEY TO CONTINUE ...";
            getch();
            break;

        case '9':
            system("cls");
            system("COLOR 7");
            cout << "\n-----------------------------------------------------\n";
            cout << "\n\tMOTEUR D'INFERENCE \n ";
            fflush(stdin);
            Moteur_Inference(LL, FFF, RRR);
            Afficher_Resultat(FFF);
            cout <<"\n\n\t\aPRESS ANY KEY TO CONTINUE ...";
            getch();
            break;

        }
    } while (choix != '0');

    cout << "\n\t         ----- LE PROGRAMME TERMINE -----";

    cin >> nn;
    return 0;
}