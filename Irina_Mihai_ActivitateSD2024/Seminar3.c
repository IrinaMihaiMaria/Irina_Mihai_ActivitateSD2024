#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct Aeroport
{
	int id; 
	char* nume;
	int nrTerminale;
};


struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune)
{
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));

	//shellow copy
	copie[(*dimensiune)] = aeroport;

	for (int i = 0; i < (*dimensiune); i++)
	{
		copie[i] = vector[i];
	}

	
	if(vector!=NULL)
		free(vector);//daca faceam deep copy trebuia sa sterg fiecrae inregistrare nu doar vectorul si facea un for

	(*dimensiune)++;

	return copie;
}

struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi)
{
	struct Aeroport* vectorAeroporturi;
	vectorAeroporturi = NULL;

	FILE* f = fopen(numeFisier, "r"); //fara & la numeFisier ca primim * numeFisier

	if (f != NULL)
	{
		(*nrAeroporturi) = 0;//daca bag dimensiune =3 in mai imi da eroare fara asta aici

		//alocam STATIC -- nu trb sa dezalocam ca se ocupa alculatorul (la dinamic trb sa  facem singuri)
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL)//returneaza un pointer la char
		{
			struct Aeroport aeroport;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);//delimitatorul e , ca asa am pus in .txt (cauta , sau \n nu combinatia dintre ele)

			aeroport.id = atoi(token);//convertim la int ca e string

			token = strtok(NULL, delimitator);//am ajuns la denumire (Otopeni)
			aeroport.nume = malloc(sizeof(char) * strlen(token)+1);//citim numele
			strcpy(aeroport.nume, token);

			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi);//daca puneam & la nrAeroportuir luam adresa

		}
		fclose(f);
	}
	return  vectorAeroporturi;
}


void afisareAeroport(struct Aeroport* aeroport)
{
	printf("Aeroportul cuu ID: %d, cu numele : %s are %d terminale.\n", aeroport->id, aeroport->nume, aeroport->nrTerminale);

}

void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim)
{
	printf("AFISARE VECTOR:\n");
	for (int i = 0; i < dim; i++)
	{
		afisareAeroport(&aeroporturi[i]);
	}
}


struct Aeroport idCautat(struct Aeroport* aeroporturi, int dim, int id)
{
	for (int i = 0; i < dim; i++)
	{
		if (aeroporturi[i].id == idCautat)
		{
			return aeroporturi[i];
			
		}
	}
	/*struct Aeroport aeroport;
	aeroport.id = -1;
	aeroport.nrTerminale = "N/A";
	aeroport.nume = malloc(sizeof(char) * (1 + strle("N/A")));
	strcpy(aeroport.nume, "N/A");*/
	struct Aeroport aeroportNULL = { -1,NULL,-1 };
	return  aeroportNULL;
}

void dezalocareVector(struct Aeroport** aeroporturi, int* dim)
{
	for (int i = 0; i < (*dim); i++)
	{
		free((*aeroporturi)[i].nume);
		//free(aeroporturi[i]);//????????????????????????????????????
	}
	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = 0;
}


void main()
{
	int dimensiune = 3;

	struct Aeroport* aeroporturi = NULL;
	aeroporturi = citireFisier("aeroport.txt", &dimensiune);

	//afisareAeroport(aeroporturi);
	afisareVectorAeroporturi(aeroporturi, dimensiune);
	dezalocareVector(&aeroporturi, &dimensiune);

}