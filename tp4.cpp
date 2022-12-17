#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <string>
using namespace std;


struct Noeud{ // Structure de mon noeud
    int val;
    Noeud *gauche = nullptr;
    Noeud *droite = nullptr;
    Noeud *pere = nullptr;
};

Noeud *initArbre();
Noeud *noeudValue(Noeud *noeud, int cle, Noeud *ptr);
Noeud *cle_min(Noeud *noeud, Noeud *ptr);
Noeud *cle_max(Noeud *noeud, Noeud *ptr);
Noeud *predecesseur(Noeud *noeud);
Noeud *successeur(Noeud *noeud);
Noeud *createABRFromArray(int *tab, int taille);
Noeud* createABREquilibre(int *tab,int taille);
void createUser(Noeud **noeud, Noeud *pere);
void affiche(Noeud *parent);
void insertion(Noeud **noeud, int Val_inserer);
void supprimer(Noeud **noeud, Noeud *supp);
void createArrayFromABR(int *tabNoeud, int nbElement, Noeud *noeud);
void triAvecABR(int *tab, int taille);
void tableau(int *tab, int taille);
void AfficheTable(int *tab, int taille);

int INDICE = 0; // variable globale

int main(){
    srand(time(NULL));

    bool START = true;
    int val;
    Noeud *noeudVal;
    int *tab;
    Noeud *Abr; 
    
 
    //Creation de mon arbre
    Noeud *noeud = initArbre();
    createUser(&noeud, nullptr);

    while(START){
        int choix;
        int taille = 0;
        cout<<endl;
        cout<<"1. Afficher l'arbre"<<endl;
        cout<<"2. Insertion"<<endl;
        cout<<"3. Suppression"<<endl;
        cout<<"4. Rechercher"<<endl;
        cout<<"5. Predecesseur"<<endl;
        cout<<"6. Successeur"<<endl;
        cout<<"7. Cle minimale"<<endl;
        cout<<"8. Cle maximale"<<endl;
        cout<<"9. ABR"<<endl;
        cout<<"Appuyer sur n'importe quel autre bouton pour quitter"<<endl;
        cout<<">> ";
        cin >>choix;
        
        switch (choix){
            case 1:
                affiche(noeud); cout<<endl<<endl; // Affichage de l'arbre!
                break;

            case 2:
                cout<<"Entrer la valeur a insere";
                cin>>val;
                insertion(&noeud, val);
                break;
            
            case 3:
                cout<<"Entrer la valeur a supprime: ";
                cin>>val;
                noeudVal = noeudValue(noeud, val, nullptr);
                supprimer(&noeud, noeudVal);              
                break;
            
            case 4:
                cout<<"Entrer la valeur a recherche: ";
                cin>>val;
                noeudVal = noeudValue(noeud, val, nullptr);
                if(noeudVal != nullptr) cout<< "La valeur existe! -> "<<noeudVal->val << endl;
                else cout<<"La valeur n'existe pas"<<endl;
                break;
            
            case 5:
                cout<<"Entrer la valeur a trouve le predecesseur: ";
                cin>>val;
                
                noeudVal=noeudValue(noeud, val, nullptr); 
                noeudVal = predecesseur(noeudVal);
                
                if (noeudVal != nullptr) cout<<"Le pred est : "<< noeudVal->val << endl;
                else cout<<"Il n'y a pas de predecesseur"<<endl;
                break;
            
            case 6:
                cout<<"Entrer la valeur a trouve le successeur: ";
                cin>>val;

                noeudVal =noeudValue(noeud, val, nullptr); 
                noeudVal = successeur(noeudVal);
    
                if (noeudVal != nullptr) cout<<"Le succ est : "<< noeudVal->val << endl;
                else cout<<"Il n'y a pas de successeur"<<endl;
                break;
            
            case 7:
                noeudVal = cle_min(noeud, nullptr);
                cout<<"La cle minimale est: "<<noeudVal->val << endl;
                break;
            
            case 8:
            
                noeudVal = cle_max(noeud, nullptr);
                cout<<"La cle maximale est: "<<noeudVal->val << endl;
                break;
            
            case 9:
                int choix2;
                cout<<"1. Creer ABR a partir d'un tableau"<<endl;
                cout<<"2. Creer d'un tableau a partir d'un ABR"<<endl;
                cout<<"3. Trie un tableau a partir d'un ABR"<<endl;
                cout<<"4. Creer un ABR equilibre"<<endl;
                cout<<"Appuyer sur n'importe quel autre bouton pour quitter"<<endl;
                cout<<">> ";
                cin >>choix2;

                taille = 10;
                tab = new int[taille];
                tableau(tab, taille);
                    
                
                switch (choix2){                   
                    case 1: 
                        cout<<"Mon tableu creer aleatoirement"<<endl;
                        AfficheTable(tab, taille);     

                        Abr = createABRFromArray(tab, taille);
                        cout<<"L'Abr"<<endl;
                        affiche(Abr); cout<<endl<<endl; // Affichage de l'arbre!     
                        break;             
                        

                    case 2:
                        Abr = createABRFromArray(tab, taille);
                        cout<<"Mon Abr! "<<endl;
                        affiche(Abr); cout<<endl; // Affichage de l'arbre! 
                        createArrayFromABR(tab, taille,  Abr);
                        cout<<"Ma table"<<endl; 
                        AfficheTable(tab, taille); 
                        break;
                       
                    
                    case 3:
                        cout<<"Mon tableu creer aleatoirement"<<endl;
                        AfficheTable(tab, taille);

                        triAvecABR(tab,  taille);
                        cout<<"Ma table triee "<<endl;
                        AfficheTable(tab, taille); 
                        break;
                        
                    
                    case 4:
                        Abr = createABREquilibre(tab, taille);
                        cout<<"Arbre equilibre"<<endl;
                        cout<<"Mon Abr! ";
                        affiche(Abr); cout<<endl; // Affichage de l'arbre! 
                        break;
                        
                    
                    default:
                        break;    
                
                }
                delete [] tab;
                Abr = nullptr;
                break;             

            default:
                START = false;
                break;  
        }
        noeudVal = nullptr;  
    }
    
    return 0;
    
}

/* Mes fonctions*/
Noeud *initArbre(){ //Initialisation de mon arbre
    Noeud *Arbre = new Noeud();
    return Arbre;

}
void createUser(Noeud **noeud, Noeud *pere){
    if(noeud != nullptr){ 
        (*noeud)->pere = pere; // raccorde le pere du noeud
       
       //Demande l'existance des fils gauches et droites
        string fg, fd;   
        cout<<"Val? ";
        cin>>(*noeud)->val;

        cout<<"fg? (oui/non) ";
        cin>>fg;
        cout<<"fd? (oui/non)";
        cin>>fd;

        if(fg == "oui"){ // Si oui pour le fils gauche, appel la fonction sur le fils gauche
            (*noeud)->gauche = new Noeud;
            createUser(&(*noeud)->gauche, *noeud);
        }

        if(fd == "oui"){ // Si oui pour le fils droite, appel la fonction sur le fils droite
            (*noeud)->droite = new Noeud;
            createUser(&(*noeud)->droite, *noeud);
        }        
    }
}

void affiche(Noeud *parent){ // Affichage des valeurs d'un arbre binaire de maniere infixe

    Noeud *ptr = parent;
    if (ptr != nullptr){
        affiche(ptr->gauche);
        cout<< ptr->val<<" ";     
        affiche(ptr->droite);
    }  
}

Noeud *noeudValue(Noeud *noeud, int cle, Noeud *ptr){// FOnction qui recherche l'existance d'une valeur
    if(noeud!= nullptr){
        if(noeud->val == cle) return noeud; // Si il retrouve la valeur, il le renvoi
        else{ // Sinon, il parcours son fils gauche et droite
            ptr = noeudValue(noeud->gauche, cle,ptr);
            ptr = noeudValue(noeud->droite, cle,ptr);
        }     
    }
    return ptr; // Retour la valeur de ptr
}

Noeud *cle_min(Noeud *noeud, Noeud *ptr){// Recherche la valeur minimale dans mon arbre
    if(noeud!= nullptr){ 
        if(noeud->gauche == nullptr) return noeud;
        ptr = cle_min(noeud->gauche, ptr);// Parcours sur mon sous-arbre gauche
    }
    return ptr;      
}

Noeud *cle_max(Noeud *noeud, Noeud *ptr){// Recherche la valeur maximale dans mon arbre
   if(noeud!= nullptr){
        if(noeud->droite == nullptr) return noeud;
        ptr = cle_max(noeud->droite, ptr); // Parcours sur mon sous-arbre droite
    }
    return ptr;      
}

Noeud *predecesseur(Noeud *noeud){ // Recherche le predecesseur du noeud
    if(noeud!= nullptr){
        // recherche le max de son sous arbre gauche
        if(noeud->gauche != nullptr) return cle_max(noeud->gauche, nullptr);

        /*soit s’il n’a pas de sous-arbre gauche, le premier ancêtre dont le
            sous-arbre droit contient le noeud */
        Noeud *pere = noeud->pere;
        while(pere != nullptr){
            if(pere->droite == noeud) return pere;
            noeud = pere;
            pere = pere->pere;
        }
        return pere;
    }
    return nullptr;
}

Noeud *successeur(Noeud *noeud){ // Recherche le successeur du noeud
    if(noeud!= nullptr){
        //recherche le min de son sous arbre droite
        if(noeud->droite != nullptr) return cle_min(noeud->droite, nullptr);

        /*soit s’il n’a pas de sous-arbre droit, le premier ancêtre dont le
            sous-arbre gauche contient le noeud*/
        Noeud *pere = noeud->pere;
        while(pere != nullptr){
            if(pere->gauche == noeud) return pere;
            noeud = pere;
            pere = pere->pere;
        }
        return pere;
    }
    return nullptr;
}

void insertion(Noeud **noeud, int Val_inserer){ //Insertion d'une valeur
    Noeud *ptr = *noeud;
    Noeud *pere = nullptr;

    while(ptr != nullptr){ // Parcours l'arbre 
        pere = ptr;
        // Si la valeur est inferieure que le noeud, donc je parcous dur le sous arbre gauche
        if(Val_inserer < ptr->val) ptr = ptr->gauche; 
        else ptr = ptr->droite; // Si la valeur est superieure que le noeud, donc je parcous dur le sous arbre droite
    }

    //creation de mon noeud
    Noeud *valInserer = new Noeud; 
    valInserer->val = Val_inserer;
    valInserer->pere = pere;

    if(pere == nullptr){
        *noeud = valInserer;
        return;
    }

    //Ajout de mon noeud
    if(Val_inserer < pere->val) pere->gauche = valInserer;
    else pere->droite = valInserer;    
}


void supprimer(Noeud **noeud, Noeud *supp){ // Suppression d'un noeud
    if (*noeud == nullptr) {
        cout<<"L'arbre est vide! "<<endl;
        return;
    }

    if (supp == nullptr){
        cout<<"Le noeud n'existe pas!"<<endl;
        return;
    }

    //0 fils : le supprimer tout simplement ;
    if(supp->gauche == nullptr && supp->droite == nullptr){
        if (supp->pere == nullptr) {
            *noeud = nullptr;
            return;
        }
        if(supp == supp->pere->gauche) supp->pere->gauche = nullptr;
        else supp->pere->droite = nullptr;
        delete supp;
        return;     
    }

    //1 fils : on rattache ce fils au père du noeud à supprimer ;
    if(supp->gauche == nullptr || supp->droite == nullptr){
        Noeud *aRattacher;

        // Recherche si le fils gauche existe
        if(supp->gauche != nullptr) aRattacher = supp->gauche; // recupere le fils du noeud a supprimer
        
        // Recherche si le fils droit existe
        else aRattacher = supp->droite; // recupere le fils du noeud a supprimer
        
        aRattacher->pere = supp->pere;// raccorde le noeud au pere du noeud a supprimer

        // Si le noeud appartient au sous-arbre gauche
        
        if(supp->pere == nullptr){
            (*noeud) = aRattacher;
            return;
        } 
        if(supp == supp->pere->gauche) supp->pere->gauche = aRattacher; // Raccorde le pere du noeud a supprimer a aRattacher
        else supp->pere->droite = aRattacher; // Raccorde le pere du noeud a supprimer a aRattacher
        
        delete supp;
        return; 
    }

    /*2 fils :
        1 on recherche son successeur (= qui a au plus un fils),
        2 on copie la valeur du successeur dans le noeud a supprimer 
        3 on supprime le successeur.
    */

    Noeud *succ = successeur(supp); // recherche de son successeur
    if (succ == nullptr){
        cout<<"Le noeud n'a pas de successeur! "<<endl;
        return;
    } 
    supp->val = succ->val; //on copie la valeur du successeur dans le noeud a supprimer
    supprimer(noeud, succ); // on supprime le successeur
}


Noeud *createABRFromArray(int *tab, int taille){
    Noeud *racine = new Noeud;
    racine->val = tab[0];

    // cout<<" taill "<<sizeof(*tab)<<" taill";
    for(int i=1; i<taille; i++) insertion(&racine,  tab[i]);
    
    return racine;
}

void createArrayFromABR(int *tabNoeud, int nbElement, Noeud *noeud){
    if(INDICE < nbElement){
        if (noeud != nullptr){
            createArrayFromABR(tabNoeud,  nbElement, noeud->gauche);
            tabNoeud[INDICE ++] = noeud->val;
            createArrayFromABR(tabNoeud ,  nbElement, noeud->droite);
        }
       
    }
}

void triAvecABR(int *tab, int taille){
    Noeud *noeud = createABRFromArray(tab, taille);
    createArrayFromABR(tab, taille, noeud);
}

Noeud* createABREquilibre(int *tab,int taille){
    triAvecABR(tab,taille);
    
    int indiceMilieu = taille/2;

    Noeud *racine = new Noeud;
    racine->val = tab[indiceMilieu];

    for(int i = 0; i<taille; i++){
        if(i != indiceMilieu) insertion(&racine,  tab[i]);
        
    }
    return racine;


}

void tableau(int *tab, int taille){
    for(int i=0; i<taille; i++) tab[i] = rand()%100;
}

void AfficheTable(int *tab, int taille){
    for(int i=0; i<taille; i++) cout<< tab[i]<<" ";
    cout<<endl; 
}
// bool estPlein(Noeud *parent){ // Verifie si l'arbre est plein
    
//   if (parent!=NULL) {
//     if (parent->gauche !=NULL || parent->droite !=NULL)
//       return estPlein(parent->gauche) && estPlein(parent->droite);
//     else return true;
//   }
//   return false;
// }