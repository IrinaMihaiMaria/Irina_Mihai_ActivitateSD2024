
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //malloc //free
#include <stdlib.h> //strlen //strcpy


struct Mineral {
	int cod;
	char* nume;
	float* greutate;
	char* culoare;
};

//functii pt citirea de la tastatura

struct Mineral citire() {
	struct Mineral m;
	printf("Introdu codul:");
	scanf("%d", &m.cod);

	m.nume = (char*)malloc(50 * sizeof(char)); //?????
	printf("Introdu numele:");
	scanf("%s", m.nume);

	m.greutate = (float*)malloc(sizeof(float));
	printf("Introdu greutatea:");
	scanf("%f", m.greutate);

	m.culoare = (char*)malloc(50 * sizeof(char));//?????
	printf("Introdu cuoloarea: ");
	scanf("%s", m.culoare);

	return m;
}


//Calcul densitate
float calculDensitate(struct Mineral m, float volum)
{
	return *m.greutate / volum; //????
}

//modificare culoare
void modificareCuloare(struct Mineral* m, char* culoareNoua)
{
	free(m->culoare);
	m->culoare = (char*)malloc((strlen(culoareNoua) + 1) * sizeof(char));
	strcpy(m->culoare, culoareNoua);
}

//afisare
void afisareMineral(struct Mineral m)
{
	printf("Cod: %d\n", m.cod);
	printf("Nume: %s\n", m.nume);
	printf("Greutate: %.2f\n", *m.greutate);//?????
	printf("Culoare: %s\n", m.culoare);
}


//TASK 2

// Functia pentru crearea unui nou vector
struct Mineral* filtreaza(struct Mineral* minerale, int nr, int* nrNou, float greutateMin) {
	*nrNou = 0;
	for (int i = 0; i < nr; i++) {
		if (*minerale[i].greutate >= greutateMin) {
			(*nrNou)++;
		}
	}

	struct Mineral* mineraleFiltrate = (struct Mineral*)malloc((*nrNou) * sizeof(struct Mineral));
	int j = 0;

	for (int i = 0; i < nr; i++)
	{
		if (*minerale[i].greutate >= greutateMin) {
			mineraleFiltrate[j++] = minerale[i];
		}
	}

	return mineraleFiltrate;
}

// Functia pentru mutarea obiectelor 
struct Mineral* muta(struct Mineral** minerale, int* nr, float greutateMax) {
	int nrNou = 0;
	for (int i = 0; i < *nr; i++) {
		if (*(*minerale)[i].greutate <= greutateMax) {
			nrNou++;
		}
	}

	struct Mineral* mineraleMutate = (struct Mineral*)malloc(nrNou * sizeof(struct Mineral));
	struct Mineral* mineraleRamase = (struct Mineral*)malloc((*nr - nrNou) * sizeof(struct Mineral));
	int j = 0, k = 0;
	for (int i = 0; i < *nr; i++) {
		if (*(*minerale)[i].greutate <= greutateMax) {
			mineraleMutate[j++] = (*minerale)[i];
		}
		else {
			mineraleRamase[k++] = (*minerale)[i];
		}
	}
	free(*minerale);
	*minerale = mineraleRamase;
	*nr -= nrNou;

	return mineraleMutate;
}



// Functia pentru concatenarea a doi vectori
struct Mineral* concateneaza(struct Mineral* minerale1, int nr1, struct Mineral* minerale2, int nr2) {
	struct Mineral* mineraleConcatenate = (struct Mineral*)malloc((nr1 + nr2) * sizeof(struct Mineral));
	memcpy(mineraleConcatenate, minerale1, nr1 * sizeof(struct Mineral));
	memcpy(mineraleConcatenate + nr1, minerale2, nr2 * sizeof(struct Mineral));
	return mineraleConcatenate;
}



// Functia pentru afisarea unui vector cu obiecte
void afisareVector(struct Mineral* minerale, int nr) {
	for (int i = 0; i < nr; i++) {
		afisareMineral(minerale[i]);
	}
}



int main()
{
	struct Mineral m = citire(); //creez un mineral

	afisareMineral(m); //afisare

	//calcul densitate
	float densitate = calculDensitate(m, 1.0);
	printf("Densitate: %.2f\n", densitate);

	//modificare culoare
	modificareCuloare(&m, "rosu");
	afisareMineral(m);

	//eliberarea memoriei alocata dinamic
	free(m.nume);
	free(m.greutate);
	free(m.culoare);


	//TASK 2
	int nr = 5;
	struct Mineral* minerale = (struct Mineral*)malloc(nr * sizeof(struct Mineral));
	for (int i = 0; i < nr; i++) {
		minerale[i] = citire();
	}

	// Crearea unui nou vector cu obiecte care indeplinesc o anumita conditie
	int nrFiltrate;
	struct Mineral* mineraleFiltrate = filtreaza(minerale, nr, &nrFiltrate, 10.0);
	printf("Minerale cu greutatea mai mare sau egala cu 10.0:\n");
	afisareVector(mineraleFiltrate, nrFiltrate);

	// Mutarea obiectelor 
	struct Mineral* mineraleMutate = muta(&minerale, &nr, 5.0);
	printf("Minerale mutate cu greutatea mai mica sau egala cu 5.0:\n");
	afisareVector(mineraleMutate, nrFiltrate);

	// Concatenarea a doi vectori
	struct Mineral* mineraleConcatenate = concateneaza(minerale, nr, mineraleFiltrate, nrFiltrate);
	printf("Minerale concatenate:\n");
	afisareVector(mineraleConcatenate, nr + nrFiltrate);

	// Eliberarea memoriei alocate dinamic
	for (int i = 0; i < nr; i++) {
		free(minerale[i].nume);
		free(minerale[i].greutate);
		free(minerale[i].culoare);
	}
	free(minerale);
	free(mineraleFiltrate);
	free(mineraleMutate);
	free(mineraleConcatenate);

	return 0;
}


