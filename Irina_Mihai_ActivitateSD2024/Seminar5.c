#include <stdio.h>
#include <malloc.h>
//liste simplu inlantuite

//eticheta / alias
typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;


struct Biblioteca {
	char* nume;
	int nrCarti;
	int nrCititori;

};

struct Nod
{
	Biblioteca info;
	Nod* next;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori)
{
	Biblioteca b;

	//alocam spatiu
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.nrCarti = nrCarti;
	b.nrCititori = nrCititori;

	return b;
}

//facem inserarea in lista de la inceput
Nod* inserareInceput(Nod* cap, Biblioteca b)
{
	//alocam spatiu
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	//setam informatia
	//deep copy - nu ne ajuta aici ca cumva in main cand initializam facemm 2 zone de memorie pt ex Mihai Eminescu
	//modific din main : 	cap = inserareInceput(cap, initializare("Ioan Slavici", 200, 30)); in : Biblioteca b1 =initializare("Mihai Eminescu", 150, 20);
//	cap = inserareInceput(cap, b1);
	nou->info = initializare(b.nume, b.nrCarti, b.nrCititori);

	//pointeaza 
	nou->next = cap;

	//noul cap al listei 
	return nou;
}


//functie de afisare
void afisareLista(Nod* cap)
{
	while (cap != NULL)
	{
		printf("Biblioteca %s are %d carti si %d cititori.\n", cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);
		//parcurgere, procesare
		cap = cap->next;
	}
}

//
char* getBibliotecaNrCartiPerCititor(Nod* cap)
{
	float max = 0;

	char* nume_aux = NULL;

	//parcurgem
	while (cap)
	{
		if (cap->info.nrCarti / cap->info.nrCititori > max)
		{
			max = cap->info.nrCarti / cap->info.nrCititori;
			nume_aux = cap->info.nume;
		}
		cap = cap->next;
	}

	//facem deep copy
	char* nume = (char*)malloc(sizeof(char) * (strlen(nume_aux)+1));
	strcpy(nume, nume_aux);

	return nume;
}

//stergem tot ce avem alocat in main 
void stergeLista(Nod** cap)//transmintem pointer prin pointer
{
	while ((*cap) != NULL)
	{
		free((*cap)->info.nume);
		Nod* copie = *cap;

		*cap = (*cap)->next;

		free(copie);
	}
}


//inserare la sfarsit
void InserareLaSfarsit(Nod** cap, Biblioteca b)
{
	//se creaza nodul
	Nod* sfarsit = (Nod*)malloc(sizeof(Nod));

	//initializam cele 2 atribute
	//deep copy
	sfarsit->info = initializare(b.nume, b.nrCarti, b.nrCititori);
	sfarsit->next = NULL;

	if ((*cap) != NULL)
	{
		//facem un aux
		Nod* capA = (*cap);
		//parcurgem
		while (capA->next!=NULL)
		{
			capA = capA->next;

		}

		capA->next = sfarsit;
	}
	else
	{
		*cap = sfarsit;
	}
}

void main()
{
	//declaram o lista
	Nod* cap = NULL; //capul listei 


	Biblioteca b1 =initializare("Mihai Eminescu", 150, 20);
	cap = inserareInceput(cap, b1);

	//cap = inserareInceput(cap, initializare("Ioan Slavici", 200, 30));
	Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
	cap = inserareInceput(cap, b2);

	//cap = inserareInceput(cap, initializare("Tudor Arghezi", 100, 15));
	Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);
	cap = inserareInceput(cap, b3);


	afisareLista(cap);
	
	char* numeDeAfisat = getBibliotecaNrCartiPerCititor(cap);
	printf("Biblioteca cu media maxima : %s \n",numeDeAfisat);
	free(numeDeAfisat);
	printf("\n\n");

	Biblioteca b4 = initializare("Radu Tudoran", 100, 15);
	cap = inserareInceput(cap, b4);
	InserareLaSfarsit(&cap, b4);
	afisareLista(cap);

	stergeLista(&cap);
	afisareLista(cap);

	//dezalocam bibliotecile b1...
	free(b1.nume);
	free(b2.nume);
	free(b3.nume);
	free(b4.nume);
}