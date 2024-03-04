#include <stdio.h>
#include <malloc.h>

struct Masina {
	char* marca;
	float capacitateCilidrica;
	int an;
};

//functie care afiseaza

void afisareMasina(const struct Masina* m)
{
	if (m->marca != NULL)
	{
		printf("Marca: %s\n", m->marca);
	}

	printf("Capacitate cilindrica: %5.2f\n", m->capacitateCilidrica);
	printf("An: %i\n\n", m->an);

}

//funtcie care initializeaza o masina

struct Masina initializareMasina(const char* marca, int an, float cc)
{
	struct Masina m;
	m.an = an;
	m.capacitateCilidrica = cc;

	if (marca != NULL)
	{
		m.marca = malloc(strlen(marca) + 1);
		strcpy(m.marca, marca);
	}
	else
	{
		m.marca = (char*)malloc(strlen("N/A") + 1);
		strcpy(m.marca, "N/A");
	}

	return m;
}

void dezalocareMasina(struct Masina* masina)
{
	free(masina->marca);

	masina->marca = NULL;
}

int main()
{
	struct Masina masina1;
	//Dacia

	//initializarea tuturor campurilor
	masina1.marca = (char*)malloc(sizeof(char) * (strlen("Dacia") + 1)); //alocarea de spatiu

	strcpy(masina1.marca, "Dacia");

	masina1.capacitateCilidrica = 1.9;

	masina1.an = 2023;

	afisareMasina(&masina1);

	////eliberam memoria
	//
	//free(masina1.marca);

	////initializam cu NULL
	//masina1.marca = NULL;

	//alternativa
	dezalocareMasina(&masina1);

	struct Masina masina2 = initializareMasina("Ford", 2022, 2.49);
	afisareMasina(&masina2);
	/*free(masina2.marca);
	masina2.marca = NULL;*/
	//alternativa
	dezalocareMasina(&masina2);

	afisareMasina(&masina2);//nu imi afiseazqa marca si apate TTTTT
	//modificam:
	/*void dezalocareMasina(struct Masina masina)
	{
	free(masina.marca);

	masina.marca = NULL;
	}*/
	//daca schimb asta imi scoate marca cu totul

	return 0;
}