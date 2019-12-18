#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <ctime>
#include <cstdlib>

using namespace std;


int main() {
	
	char lettre;
	int nbCoups = 5;
	ifstream dico("dico.txt");
	
	do {
		srand(time(0));//initialisation des nombres aléatoires
		lettre = ' ';//on efface la valeur de la lettre
		
		//1 : Saisie d'un mot au hasard du dictionnaire
		string motMystere, motMelange, motUtilisateur;
		int numeroMot, positionLettre;
		
		if (dico) {
			
			string ligne; //pour stocker les lignes lues
			int nbMots(0);
			while(getline(dico, ligne)) {
				nbMots++;
			}
			dico.close();//bug si on ne ferme pas le fichier
			
			//choix d'un mot aléatoire
			numeroMot = rand() % nbMots;
			
			dico.open("dico.txt");//réouverture
			//positionnement sur la ligne correspondante
			for (int compteur = numeroMot; compteur > 0; compteur--) {
				getline(dico, ligne);
			}
			dico.ignore();
			dico >> motMystere;
			
		} else {
			cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
		}
		
		
		//2 : Mélange des lettres du mot
		
		string copie = motMystere;
		
		while (copie != "") {
			positionLettre = rand() % copie.size();
			motMelange += copie[positionLettre];
			copie.erase(positionLettre,1);
		}
		
		//3 : On demande à l'utilisateur quel est le mot mystère
		
		do {
			
			cout << endl << "Quel est ce mot? " <<  motMelange << endl;
			cout << "Essais restants : " << nbCoups << endl;
			cin >> motUtilisateur;
			//mise en majuscules
			for (int i = 0; i < motUtilisateur.size(); i++) {
				motUtilisateur[i] = ::toupper(motUtilisateur[i]);
			}
			
			if (motUtilisateur != motMystere) {
				cout << "Ce n'est pas le mot ! " << endl;
				nbCoups--;
			} else {
				cout << "BRAVO! " << endl;
			}
			
		} while (motUtilisateur != motMystere && nbCoups != 0);
		
		if (nbCoups == 0) {
			cout << "Le mot était : " << motMystere << endl;
		}
		
		//4 : Invite de continuation
		while (lettre != 'o' && lettre != 'n') {
			
			cout << endl << "Voulez vous rejouer? (o/n) ";
			cin >> lettre;
			switch (lettre) {
				case 'n':
					cout << "Fin de partie!" << endl;
					break;
				case 'o':
					nbCoups = 5;
					break;
				default:
					cout << "Saisie incorrecte; entrer 'O' pour continuer ou 'N' pour quitter" << endl;
					break;
			}
			
		}
		
	
	} while (lettre != 'n');
	
	
	
	return 0;
}
