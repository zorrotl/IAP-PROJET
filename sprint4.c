#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define lgMot 30
#define maxSkieurs 50
#define maxcar 80
#define maxdoor 20
#pragma warning(disable : 4996)
char mot[lgMot];
typedef struct {  tableau Mesure avec le temps, la porte et le dossard
	double temps;
	unsigned int porte;
	unsigned int dossard;
}Mesure;

typedef struct { tableau Course avec pour chaque Mesure (taille pour augmenter le nombre de mesure enregistrée)  
	Mesure data1[maxSkieurs * maxdoor];
	unsigned int taille;
	unsigned int nbPortes;
	unsigned int nbDisqualif;
}Course;

typedef struct {
	char nom[lgMot + 1];
	char pays[lgMot + 1];
	unsigned int dossard;
} Skieur;

typedef struct {
	Skieur data[maxSkieurs];
	unsigned int nbInscrits;
} Inscrits;


void definition_course(Course* crs);  (a)
void enregistrement_temps(Course* crs);  (b)
void affichage_temps(const Course* crs);  (c)
void inscription_skieur(Inscrits*ins);
void affichage_skieurs(const Inscrits* ins);
void disqualification(Course* crs);
void afficher_classement(const Course* crs,const Inscrits* ins);
void sortie2();

int main() {
	Course crs;
	Inscrits ins;
	ins.nbInscrits = 0;
	crs.taille = 1;
	crs.nbDisqualif = 0;
	char mot[maxcar];  mot de commande à lire
	printf("entrer 'inscrire_skieurs' pour proceder a l'inscription\n");
	printf("entrer 'afficher_skieurs' pour afficher les skieurs inscrits\n");
	printf("entrer 'enregistrer_temps' pour proceder a l'enregistrement du temps\n");
	printf("entrer 'disqualification' si le skieur est disqualifie\n");
	printf("entrer 'afficher_temps' pour afficher le temps\n");
	do {
		 Lecture de la commande (mot)
		scanf("%s", mot);
		if (strcmp(mot, "definir_course") == 0) {
			definition_course(&crs);
		}
		if (strcmp(mot, "enregistrer_temps") == 0) {
			enregistrement_temps(&crs);
		}
		if (strcmp(mot, "afficher_temps") == 0) {
			affichage_temps(&crs);
		}
		if (strcmp(mot, "inscrire_skieur") == 0) {
			inscription_skieur(&ins);
		}
		if (strcmp(mot, "afficher_skieurs") == 0) {
			affichage_skieurs(&ins);
		}
		if (strcmp(mot, "disqualification") == 0) {
			disqualification(&crs);
		}
		if (strcmp(mot, "afficher_classement") == 0) {
			afficher_classement(&crs,&ins);
		}
		if (strcmp(mot, "exit") == 0) {
			sortie2();
		}
	} while (1);
	system("pause");
	return 0;
}

void inscription_skieur(Inscrits* ins) { fonction permettant d'inscire un Skieur à la course

	printf("entrer le nom du skieur : ");
	scanf("%s", mot); donner son Nom
	strcpy(ins->data[ins->nbInscrits].nom, mot);

	printf("entrer le pays du skieur : ");
	scanf("%s", mot); donner le pays
	strcpy(ins->data[ins->nbInscrits].pays, mot);

	ins->data[ins->nbInscrits].dossard = 101 + ins->nbInscrits; dossard attribué dans l'ordre d'inscription
	printf("inscription dossard %d\n", ins->data[ins->nbInscrits].dossard);

	ins->nbInscrits++; ajoute 1 au nombre d'inscrits
}


void affichage_skieurs(const Inscrits* ins) { fonction permettant l'affichage des skieurs inscrits à la course
	unsigned int i;
	for ( i = 0 ; i < ins->nbInscrits; i++)
	{
		printf("%s %s %d\n", ins->data[i].nom, ins->data[i].pays, ins->data[i].dossard);
	}
}

void definition_course(Course * crs) { fonction définissant le nombre de portes à passé
	printf("entrer le numero de la course ");
	scanf("%s", mot); donner le nombre de portes à passer 
	crs->nbPortes = atoi(mot); conversion de "mot"(char) en int
}
void enregistrement_temps(Course* crs) { fonction permettant l'enregistrement du temps à une porte donnée et un dossard donné
	printf("entrer le temps : ");
	scanf("%s", &mot);  donner le temps
	crs->data1[crs->taille].temps = atof(mot);

	printf("numero de porte : ");
	scanf("%s", &mot); donner le numéro de porte
	crs->data1[crs->taille].porte = atoi(mot);

	printf("entrer le numero de dossard : ");
	scanf("%s", &mot); donner le numéro de dossard
	crs->data1[crs->taille].dossard = atoi(mot);

	crs->taille++; ajoute 1 à "taille" qui défini le nombre de mesure entré
}

void disqualification(Course* crs) {
	printf("entrer le numero de porte disqualifie : ");
	scanf("%s", mot); donner la porte de disqualification
	crs->data1[crs->taille].porte = atoi(mot);
	printf("entrer le numero de dossard disqualifie : ");
	scanf("%s", mot); donner le numéro de dossard du disqualifié
	crs->data1[crs->taille].dossard = atoi(mot);
	double dsq = -1; valeur de disqualification
	crs->data1[crs->taille].temps = dsq;

	crs->taille++; ajoute 1 à "taille" qui défini le nombre de mesure entré
	crs->nbDisqualif++;
}

void affichage_temps(const Course* crs) { fonction affichant le temps d'un numéro de dossard choisi et indique si disqualifié
	unsigned int dossard,i;
	printf("entrer le dossard choisi : ");
	scanf("%s", mot);
	dossard = atoi(mot); donner le numéro de dossard dont le temps sera affiché
	for (i = 0; i < crs->taille; i++) { boucle ne prenant que les temps du dossard choisi
		if (crs->data1[i].dossard == dossard && crs->data1[i].temps >= 0) { condition affichant la porte, le dossard et le temps
			printf("%u %u %.2lf \n", crs->data1[i].porte, crs->data1[i].dossard, crs->data1[i].temps);
		}
		else if (crs->data1[i].dossard == dossard && crs->data1[i].temps <= 0) { si valeur -1 le dossard est disqualifié
			printf("%u %u disqualification \n", crs->data1[i].porte, crs->data1[i].dossard);
		}
	}
}

void afficher_classement(const Course* crs, const Inscrits* ins) { fonction affichant le classement des skieurs à une porte donnée
	unsigned int pt, i, j, o = 0, d, tDos[maxSkieurs];tableau auxiliaire 1 permettant le trie des dossards
	double tTps[maxSkieurs], t; tableau auxiliaire 2 permettant le trie des temps
	
	scanf("%s", mot); porte choisie
	pt = atoi(mot);
	for (i = 0; i <= ins->nbInscrits - crs->nbDisqualif ; i++) { 
		while (crs->data1[o].porte != pt && o < crs->taille) boucle ne prenant que les données sur la porte demandée
		{
			o++;
		}
			if (crs->data1[o].temps < 0) { contrainte pour différencier les disqualifiés (temps par défaut est -1 pour les disqualifiés)
				tTps[i] = 65555555; temps fixé (trop grand) afin de l'eliminé lors de l'affichage des temps
				tDos[i] = crs->data1[o].dossard; le tableau auxiliaire prend le dossard donnée
			}
			else
			{
				tTps[i] = crs->data1[o].temps - ((crs->data1[o].dossard - 101) * 60);  temps réel effectué lors de la course en fonction du numéro de dossard
				tDos[i] = crs->data1[o].dossard; le tableau auxiliaire prend le dossard donnée
			}
			o++;
	}
	for (i = 1; i < ins->nbInscrits - crs->nbDisqualif; i++) {
		t = tTps[i];
		d = tDos[i];
		j = i;
		while (j > 0 && tTps[j - 1] > t) boucle de tri
		{/*si le temps à l'indice inférieur est plus grand alors le temps le plus petit prend 
			l'indice le plus petit possible tout en faisant suivre le numéro de dossard effectuant ce temps*/
			tTps[j] = tTps[j - 1];
			tDos[j] = tDos[j - 1];
			j--;
		}
		tTps[j] = t; fixe la valeur de temps au bon indice
		tDos[j] = d; fixe le dossard au bon indice 
	}
	for (i = 0; i <= ins->nbInscrits - crs->nbDisqualif; i++) {
		if (tTps[i] < 65555 && tTps[i] >= 0 && tDos[i] < ins->nbInscrits + 101 && tDos[i] >= 101) {
			différentes contraintes d'affichage : temps< 65555 ET temps >= 0 ET Dossard <= nbInscrits + 101 ET dossard >= 101
			printf("%d %d %s %s %.2lf\n", pt, tDos[i], ins->data[tDos[i] - 101].nom, ins->data[tDos[i] - 101].pays, tTps[i]); affiche la porte, le dossard, le Nom, le Pays et le temps
		}
	}
	}


void sortie2() {
	exit(0);
}