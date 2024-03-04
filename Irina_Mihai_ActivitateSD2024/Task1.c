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

	return 0;
}

