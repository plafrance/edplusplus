#include<iostream>
#include <cstring>
#include <fstream>
#include "chaines.h"
#include<cmath>

using namespace std;

//Constantes globales

//Longueur max d'une ligne
const int LIGNE_MAXLONG=200;

//Nombre max de lignes dans le document
const int NB_LIGNES_MAX=1000;

//Longueur max d'une commande
const int CMD_MAXLONG=80;

//Nombre max de paramètres dans une ligne de commande
const int NB_PARAMS_MAX=3;

//Variables globales concernant le document en cours d'édition

//Les lignes du document
char* lignes[NB_LIGNES_MAX];

//Le nombre de lignes que contient le document
int nb_lignes=0;

//La ligne courante (sélectionnée)
int ligne_courante=-1;

//Le nom du fichier lu ou écrit
char nom_fichier[256];

/*
  Affiche une ligne sous la forme
  
  0 : ligne
  
  ou 
  
  0 :*ligne
  
  s'il s'agit de la ligne courante.
  
  
  Paramètre:
      num_ligne: numéro de la ligne à afficher >=0.
*/
void afficher_ligne(int num_ligne){
    cout.width(log10(nb_lignes));
    cout << num_ligne << " :"<< (num_ligne==ligne_courante?"*":" ") << lignes[num_ligne] << endl;
}

/*
   Affiche toutes les lignes
*/
void afficher(){
    for(int i=0; i<nb_lignes; i++){
	afficher_ligne(i);
    }
}

/*
  Lit le contenu d'un fichier et en remplit le tableau de chaînes destinations

  Paramètres:
     destination : tableau de pointeurs de chaînes devant recevoir les lignes lues dans le fichier
     nom_fichier : nom du fichier d'où lire les lignes.

  Retour:
     le nombre de lignes lues ou -1 si le fichier n'a pu être lu.

 */
int lire_fichier(char** destination, char* nom_fichier){
    int nb_lignes=0;
    ifstream fichier=ifstream(nom_fichier);
    if(fichier.is_open()){
	while(!fichier.eof())
	    fichier.getline(destination[nb_lignes++]=new char[LIGNE_MAXLONG],LIGNE_MAXLONG);
	fichier.close();
    }


    return nb_lignes;

}

/*
  Écrit les chaînes de caractères dans un fichier.

  Paramètres:
     nom_fichier : nom du fichier où écrire les lignes.
     lignes : tableau de pointeurs de chaînes à écrire
     nb_lignes : le nombre de lignes à écrire.

  Retour :
     vrai si le fichier a bien été sauvegardé.

*/
bool ecrire_fichier(char* nom_fichier, char **lignes, int nb_lignes){
    ofstream fichier=ofstream(nom_fichier);
    if(fichier.is_open()){
	for(int i=0;i<nb_lignes;i++){
	    fichier << lignes[i] << endl;
	}
	fichier.close();
	return 1;
    }
    return 0;
}

/*
  Détermine si une chaîne de caractère ne contient que des caractères numériques.

  Paramètre :
    chaine : la chaîne de caractères à vérifier

  Retour :
    vrai si et seulement si la chaîne ne contient que des chiffres.
 */
bool est_numerique(char* chaine){
    for(;*chaine;++chaine){
	if(!isdigit(*chaine)){
	    return false;
	}
    }
    return true;
}

int main(int args, char* argv[]){
    //Ligne de commande entrée par l'utilisateur
    char commande[CMD_MAXLONG];

    //La commande à exécuter
    char* cmd;

    //Tableau des paramètres entrés par l'utilisateur (incluant la commande)
    char* params[NB_PARAMS_MAX];

    //Nombre de paramètres entrés par l'utilisateur.
    int nb_params;

    commande[0]=0;

    //Récupère le contenu du fichier si spécifié en paramètres au programme
    memset(nom_fichier, 0, 256);
    if(args>1){
	strcpy(nom_fichier,argv[1]);
	nb_lignes=lire_fichier(lignes, nom_fichier);
    }
    else{                                                                                                                                                                        
        cout << "Entrez un nom de fichier à éditer." << endl;
        cout << "Syntaxe : editeur nomfichier" << endl;                                                                                                                          
        return -1;                                                                                                                                                               
    }

    //Initialise l'espace pour la commande.
    for(int i=0;i<NB_PARAMS_MAX;++i){
	params[i]=new char[CMD_MAXLONG];
    }

    //C'est ici que l'éditeur lit les commandes et les exécute.
    //Boucle jusqu'à ce que l'utilisateur entre la commande Q.
    do{
	//Affiche l'invite de commande
	cout << ">";
	cin.getline(commande, CMD_MAXLONG);
	
	//Récupère la commande, ou répète la dernière commande en entrant «!!»
	if(strcmp(commande,"!!")){
	    nb_params=separer_mots(params, commande);
	    cmd=params[0];
	}

	//Afficher
	if(!strcasecmp(cmd, "a")){
	    //À FAIRE
	}

	//Insérer une ligne
	else if(!strcasecmp(cmd, "i")){
	    int ligne;
	    if(nb_params>1){
		//insère avant la ligne donnée en paramètre
		ligne=atoi(params[1]);
	    }
	    else{
		//insère avant la ligne courante ou après la dernière s'il
		//n'y a pas de ligne courante
		ligne=(ligne_courante==-1?nb_lignes:ligne_courante);
	    }
	    cout << ":";
	    char entree[LIGNE_MAXLONG];
	    cin.getline(entree, LIGNE_MAXLONG);
	    //À FAIRE insérer la ligne au bon endroit.
	}

	//Changer la casse pour des MAJUSCULES
	else if(!strcasecmp(cmd, "maj")){
	    int ligne=-1;
	    if(nb_params>1){
		ligne=atoi(params[1]);
	    }
	    else{
		ligne=ligne_courante;
	    }

	    if(ligne_courante>-1){
		changer_casse(lignes[ligne_courante], lignes[ligne_courante], CASSE::MAJ);
	    }
	    else{
		cout<<"Aucune ligne sélectionnée\n";
	    }

	}
	
	//Changer la casse pour des minuscules
	else if(!strcasecmp(cmd, "min")){
	    int ligne=-1;
	    if(nb_params>1){
		ligne=atoi(params[1]);
	    }
	    else{
		ligne=ligne_courante;
	    }

	    if(ligne_courante>-1){
		changer_casse(lignes[ligne_courante], lignes[ligne_courante], CASSE::MIN);
	    }
	    else{
		cout<<"Aucune ligne sélectionnée\n";
	    }

	}
	
	//Changer la casse pour des Capitales
	else if(!strcasecmp(cmd, "cap")){
	    int ligne=-1;
	    if(nb_params>1){
		ligne=atoi(params[1]);
	    }
	    else{
		ligne=ligne_courante;
	    }

	    if(ligne_courante>-1){
		changer_casse(lignes[ligne_courante], lignes[ligne_courante], CASSE::CAP);
	    }
	    else{
		cout<<"Aucune ligne sélectionnée\n";
	    }

	}

	//Cherche une chaîne
	else if(!strcasecmp(cmd, "c")){
	    //chaîne recherchée
	    char cible[LIGNE_MAXLONG];

	    if(nb_params<2){
		cout << ":";
		cin.getline(cible,LIGNE_MAXLONG);
	    }
	    else{
		strcpy(cible, params[1]);
	    }

	    //À FAIRE : rechercher la prochaine occurence de cible, en faire
	    //la ligne courante et l'afficher
	}

	//Cherche et remplace une chaîne par une autre
	else if(!strcasecmp(cmd, "r")){
	    char cible[LIGNE_MAXLONG];
	    char remplacement[LIGNE_MAXLONG];	    

	    if(nb_params<2){
		cout << "chercher: ";
		cin.getline(cible,LIGNE_MAXLONG);
	    }
	    else{
		strcpy(cible, params[1]);
	    }
	    
	    if(nb_params<3){
		cout << "remplacer par: ";
		cin.getline(remplacement,LIGNE_MAXLONG);
	    }
	    else{
		strcpy(remplacement, params[2]);
	    }

	    //À FAIRE : rechercher la prochaine occurence de cible, la remplacer
	    //par remplacement puis en faire la ligne courante et l'afficher.
	}

	//Supprime une ligne
	else if(!strcasecmp(cmd, "s")){
	    //Le numéro de la ligne à supprimer.
	    int ligne=-1;
	    //Un numéro est donné en paramètre
	    if(nb_params>1){
		if(est_numerique(params[1])){
		    ligne=atoi(params[1]);
		}
	    }
	    //on supprime la ligne courante
	    else if(ligne_courante>=0){
		ligne=ligne_courante;
	    }
x
	    //on supprime la ligne
	    if(ligne>0){
		//À FAIRE : supprimer la ligne.
	    }
	    //pas de paramètre donné et pas de ligne courante, on demande
	    else{
		cout<<"Aucune ligne sélectionnée\n";
	    }
	}

	//Sélectionne une ligne courante
	else if(!strcasecmp(cmd, "n")){
	    if(nb_params<2){
		ligne_courante=-1;
	    }
	    else{
		ligne_courante=atoi(params[1]);
	    }
	}

	//Sauvegarde le fichier.
	else if(!strcasecmp(cmd, "e")){
	    //Utilise le nom de fichier donné en paramètre.
	    ecrire_fichier(nom_fichier, lignes, nb_lignes);
	}

	//Quitte le programme
	else if(!strcasecmp(cmd, "q")){
	    cout << "Au revoir\n";
	}

	//Commande inconnue
	else{
	    cout << "La commande " << cmd << " n'est pas reconnue.\n";
	}
    }while(strcasecmp(cmd,"q"));

}
