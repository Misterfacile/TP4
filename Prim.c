#include <stdio.h>
#include <stdlib.h>

#include "Prim.h"


#define INFINI 1000.0


t_arete *prim(float **adjacencePoids, int ordre){
	t_arete arbre = NULL;
	int indiceA = 0;
	int *marques;
	int s,x,y,ymin;
	float min;
	arete *a=NULL;
	arbre = new_t_arete(ordre-1);
	marques = (int*) malloc(ordre * sizeof(int));
	for(x=0;x<ordre;x++){
		marques[x] = 0;
	}
	s = rand()%ordre;
	marques[s] = 1;
	printf("Valeur de s : %d\n",s);
	while(indiceA <ordre-1){
		min = INFINI;
		for(x=0; x<ordre; x++){
			if(marques[x]){
				for(y=0 ; y<ordre ; y ++){
					if(adjacencePoids[x][y] > 0  && !marques[y] && adjacencePoids[x][y]<min){
						min = adjacencePoids[x][y];
						ymin = y;
					}
				}
				a = new_arete(x+1,ymin+1,min);
				arbre[indiceA].arete= a;
				marques[ymin] = 1;

			}


		}

		indiceA++;
	}
	float poid = 0;
	for(int i=0; i<ordre-1 ; i++){
		poid = poid + arbre[i].arete->value;
	}
	printf(" Poid minimal de l'arbre : %f \n",poid);
	return arbre;
}

t_arete new_t_arete(int nbarete){
	t_arete t = NULL;
	t = malloc(nbarete*sizeof(*t));
	return t;
}




arete *new_arete(int s1, int s2, float value){
	arete *a = NULL;
	a = malloc(sizeof(*a));
	a->sommet1 = s1;
	a->sommet2 = s2;
	a ->value = value;
	return a;
}

void allouerTableau2(float** t, int n) {
	*t = (float*) malloc(n * sizeof(float));
	if(*t == NULL){
		printf("Pb Allocation mémoire !! \n");
		exit(EXIT_FAILURE);
	}
}



void afficherMatrice(float *t, int n){
	int i = 0;
	for(i = 0; i<n; i++ ){
		printf("%f\t ", t[i]);
	}
}
void afficherMatrice2D(float **t, int l){
	int i;
	for(i = 0; i<l ; i++){
		afficherMatrice(t[i], l);
		printf("\n");
	}
}

void adjacencePoid(float *t,int noeud2,float valeur){
	t[noeud2-1] = valeur;
}

void adjacence2DPoid(float **t,int noeud1, int noeud2, float valeur){
	adjacencePoid(t[noeud1-1],noeud2,valeur);
	adjacencePoid(t[noeud2-1],noeud1,valeur);
}

void afficheVoisin(float *t, int n){
	int i = 0;
	for(i = 0; i<n; i++ ){
		if(t[i]!= 0){
			printf("(%d) ", i+1);
		}
	}
	printf("\n");
}
void chargeGraphe(float **t, int ordre){
	for(int i =0; i<ordre; i++){
		printf("(%d) : ",i+1);
		afficheVoisin(t[i],ordre);
	}
}


void chargeExercice(){
	printf("Tapez le nombre de noeud dans le graphe : ");
			int ordre;
			scanf("%d",&ordre);
			float **adjacence = NULL ;
			// Alloue les lignes de la matrice
			adjacence = (float**) malloc(ordre * sizeof(float*));

			// Alloue les colonnes de la matrice
			for(int i=0;i < ordre; i++){
				allouerTableau2(&(adjacence[i]), ordre);
			}

			int choix;
			int noeud1;
			int noeud2;
			do{
				printf("---Menu---\n");
				printf("1- Ajouter un voisin \n");
				printf("0- Initialisation de la matrice \n");
				printf("Votre choix : ");
				scanf("%d",&choix);
				if(choix == 1){

					do{
						printf("Quel noeud a un voisin ? : ");
					    scanf("%d",&noeud1);
					    if(noeud1 > ordre || noeud1<= 0){
					    	printf("Le noeud n'existe pas \n");
					    }
					}while(noeud1>ordre || noeud1 <=0);
					do{
						printf("Avec quel noeud ? : ");
						fflush(stdout);
					    scanf("%d",&noeud2);
					    if(noeud2>ordre || noeud2 <=0){
					    printf("Le noeud n'existe pas \n");
					    }else if(noeud1 == noeud2){
					    	printf("Un noeud ne peut être voisin de lui-même \n");
					    }
					}while(noeud2>ordre || noeud2 <=0 || noeud1 == noeud2 );
					float valeur = INFINI;
					do{
						printf("Saisissez la valeur de l'arête entre le sommet (%d) et (%d) entre 1 à 1000: ",noeud1,noeud2);
						scanf("%f",&valeur);
						if(!(valeur < 1000 && valeur > 1)){
							printf("Valeur Incorrecte \n");
						}
					}while(valeur >1000 || valeur < 1);

					adjacence2DPoid(adjacence,noeud1,noeud2,valeur);

				}else if(choix != 0){
					printf("\nChoix incorrecte \n");
				}
			}while(choix !=0);
			printf("---------- Affichage Matrice adjacence poid ---------- \n");
			afficherMatrice2D(adjacence,ordre);
			printf("---------- Affichage Graphe format (Sommet) : (voisin1)  (voisin2) ---------- \n");
			chargeGraphe(adjacence,ordre);
			t_arete t = prim(adjacence,ordre);
			printf("FIN");
}

