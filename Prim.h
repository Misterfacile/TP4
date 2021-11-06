/*
 * Prim.h
 *
 *  Created on: 29 oct. 2021
 *      Author: misterfacile
 */

#ifndef PRIM_H_
#define PRIM_H_

typedef struct arete{
	int sommet1;
	int sommet2;
	float value;
}arete;

typedef struct t_arete{
	 arete *arete;
}*t_arete;


t_arete new_t_arete(int nbarete);
void insererArete(t_arete *t, arete a, int indiceA);
arete *new_arete(int s1, int s2, float value);
void allouerTableau2(float **t, int n);
void afficherMatrice(float *t, int n);
void afficherMatrice2D(float **t, int l);
void adjacencePoid(float *t,int noeud2,float valeur);
void adjacence2DPoid(float **t,int noeud1, int noeud2, float valeur);
void afficheVoisin(float *t, int n);
void chargeGraphe(float **t, int ordre);
void chargeExercice();
t_arete *prim(float **adjacencePoids, int ordre);
#endif /* PRIM_H_ */
