#include <stdio.h>
#include <stdlib.h>
typedef struct ElementListeChainee ElementListeChainee;

struct ElementListeChainee
{
	void *contenu;
	ElementListeChainee *suivant;
	int tailleElementListeChainee;
};

ElementListeChainee *initialiserListe(int taillePremier)
{
	// par convention, le premier element est vide
	// ca permet de generaliser les autres algorithmes
	ElementListeChainee *sortie;
	sortie = malloc(sizeof(ElementListeChainee));
	sortie -> contenu = NULL;
	sortie -> suivant = NULL;
	sortie -> tailleElementListeChainee = taillePremier;
}

void ajouterElementListeChainee(ElementListeChainee* depart, void *element)
{
//ajout de type fifo (l'element le plus rapide a recuperer est le premier entre
	int tailleElementListeChainees = depart -> tailleElementListeChainee;
	ElementListeChainee *actuel = depart;
	while(actuel -> suivant != NULL)
		actuel = actuel -> suivant;
	actuel -> suivant = malloc(sizeof(ElementListeChainee));
	actuel = actuel -> suivant;
	actuel -> suivant = NULL;
	actuel -> contenu = element;
}

void ajouterElementListeChaineePile(ElementListeChainee* depart, void *element)
{
//ajout de type Pile lifo (l'element le plus rapide a recuperer est le dernier entre
	int tailleElementListeChainees = depart -> tailleElementListeChainee;
	ElementListeChainee* actuel = depart;
	ElementListeChainee* suivant = actuel -> suivant;
	actuel -> suivant = malloc(sizeof(ElementListeChainee));
	actuel = actuel -> suivant;
	actuel -> suivant = suivant;
	actuel -> contenu = element;
}




void* getElementListeChainee(ElementListeChainee * depart,int indice)
{
	int i;
	ElementListeChainee *actuel = depart;
	for(i = 0; i < indice + 1; i++)
	{
		if(actuel -> suivant == NULL)
			return NULL;
		actuel = actuel -> suivant;
	}
	return actuel -> contenu;
}

void supprimerElementListeChainee(ElementListeChainee *liste, int numero)
{
	int i;
	ElementListeChainee* precedent = liste;
	ElementListeChainee *actuel = liste -> suivant;
	for(i = 0; i <  numero; i++)
	{
		if(actuel -> suivant == NULL)
		{
			printf("l'element a supprimer n'est pas dans la liste");
			return ;
		}
		actuel = actuel -> suivant;
		precedent = precedent -> suivant;
	}
	precedent -> suivant = actuel -> suivant;
	free(actuel);



}

void exemple()
{
	//exemple d'utilisation
	ElementListeChainee *liste = initialiserListe(sizeof(int));
	int ajouter = 5;
	ajouterElementListeChainee(liste,&ajouter);
	printf("%i\n", *((int*) getElementListeChainee(liste, 0)));
	supprimerElementListeChainee(liste, 0);
}




