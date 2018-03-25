#include "listeChainee.c"

typedef struct Noeud Noeud;
typedef struct Arc Arc;
typedef struct Graphe Graphe;

struct Noeud {
	int distance;
	Noeud* antecedent;
	int infini;
	int fixe;
	ElementListeChainee *listeArcs;
	int numero;
};

struct Arc
{
	Noeud* arrivee;
	int cout;//mettre ce cout a 1 dans le cas ou le graphe n'est pas pondere

};

struct Graphe
{
	ElementListeChainee* sommets;
	int nombreSommets;
};

Graphe* creerGraphe(int nombreSommets)
{
	Graphe* nouveauGraphe = malloc(sizeof(Graphe));
	nouveauGraphe -> sommets = initialiserListe(sizeof(Noeud));
	nouveauGraphe -> nombreSommets = nombreSommets;
	int i;
	for(i = 0; i < nombreSommets; i++)
	{
		Noeud* nouveau = malloc(sizeof(Noeud));
		nouveau -> antecedent = NULL;
		nouveau -> infini = 1;
		nouveau -> listeArcs = initialiserListe(sizeof(Arc));
		nouveau -> fixe = 0;
		nouveau -> numero = i;
		ajouterElementListeChainee(nouveauGraphe -> sommets, nouveau);
	}
	return nouveauGraphe;
}

void ajouterArc(Graphe* graphe, int depart, int arrivee, int cout)
{//si le graphe n'est pas pondere, cout = 1
	Noeud* sommetDepart = getElementListeChainee(graphe -> sommets, depart);
	Noeud* sommetArrivee = getElementListeChainee(graphe -> sommets, arrivee);
	Arc* nouvelArc = malloc(sizeof(Arc));
	nouvelArc -> arrivee = sommetArrivee;
	nouvelArc -> cout = cout;
	ajouterElementListeChainee(sommetDepart -> listeArcs, nouvelArc);

} 

void ajouterArrete(Graphe* graphe, int depart, int arrivee, int cout)
{	
	ajouterArc(graphe, depart, arrivee, cout);
	ajouterArc(graphe, arrivee, depart, cout);

}

Noeud* chercherMinNonFixeDansGraphe(Graphe* graphe)
{
	ElementListeChainee* actuel = graphe -> sommets -> suivant;
	int min = 0;
	int infini = 1;
	Noeud* noeudMini = NULL;//actuel -> contenu;
	while(actuel != NULL)
	{
		Noeud* noeudActuel = actuel -> contenu;
		if(!noeudActuel -> fixe && !noeudActuel -> infini && (infini||min > noeudActuel -> distance))
		{
			noeudMini = noeudActuel;
			infini = 0;
			min = noeudActuel -> distance;
		}
	actuel = actuel -> suivant;	
	}
	return noeudMini;

}

void djikstra(Graphe* graphe, int depart)
{
	Noeud* sommetDepart = getElementListeChainee(graphe -> sommets, depart);
	sommetDepart -> distance = 0;
	sommetDepart -> infini = 0;
	int nombreSommets =  graphe -> nombreSommets;
	int i;
	for(i = 0; i < nombreSommets - 1; i++)
	{
		//on cherche le sommet a fixer (ie le plus proche du depart)
		Noeud* sommetAFixer = chercherMinNonFixeDansGraphe(graphe);
		//on fixe le sommet
		sommetAFixer -> fixe = 1;
		// on met a jour ses fils
		ElementListeChainee* elementArc = sommetAFixer -> listeArcs -> suivant;
		printf("%i\n",sommetAFixer -> numero);

		while(elementArc != NULL)
		{
			Arc* arc = elementArc -> contenu;
			if(arc -> arrivee -> infini)
			{// le chemin qui passe par ce sommet est meilleur que le precedent
				arc -> arrivee -> distance = sommetAFixer -> distance + arc -> cout;
				arc -> arrivee -> antecedent = sommetAFixer;
				arc -> arrivee -> infini = 0;
			}
			if(sommetAFixer -> distance + arc -> cout < arc -> arrivee -> distance)
			{// le chemin qui passe par ce sommet est meilleur que le precedent
				arc -> arrivee -> distance = sommetAFixer -> distance + arc -> cout;
				arc -> arrivee -> antecedent = sommetAFixer;
			
			}
			elementArc = elementArc -> suivant;
		}
	}
}

void main()
{
	Graphe* graphe = creerGraphe(5);
	ajouterArrete(graphe, 0,1,7);

	ajouterArrete(graphe, 0,2,9);
	ajouterArrete(graphe, 1,2,10);
	ajouterArrete(graphe, 2,3,11);
	ajouterArrete(graphe, 3, 4, 6);
	djikstra(graphe,0);
	Noeud* sommet = getElementListeChainee(graphe -> sommets, 4); 
	printf("%i\n", sommet -> distance);
}
