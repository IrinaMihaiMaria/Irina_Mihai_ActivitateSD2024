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


	if (vector != NULL)
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
			aeroport.nume = malloc(sizeof(char) * strlen(token) + 1);//citim numele
			strcpy(aeroport.nume, token);

			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi);//daca puneam & la nrAeroportuir luam adresa

		}
		fclose(f);
	}
	return  vectorAeroporturi;
}


//sem 4 - modific
void citireMatriceFisier(const char* numeFisier, int* nrAeroporturiLinie, int nrClustere, struct Aeroport** aeroporturi)//clustere - liniile
{
	FILE* f = fopen(numeFisier, "r"); //fara & la numeFisier ca primim * numeFisier


	if (f != NULL)
	{
		//alocam STATIC -- nu trb sa dezalocam ca se ocupa alculatorul (la dinamic trb sa  facem singuri)
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL)//returneaza un pointer la char
		{
			struct Aeroport aeroport;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);//delimitatorul e , ca asa am pus in .txt (cauta , sau \n nu combinatia dintre ele)

			aeroport.id = atoi(token);//convertim la int ca e string

			token = strtok(NULL, delimitator);//am ajuns la denumire (Otopeni)
			aeroport.nume = malloc(sizeof(char) * strlen(token) + 1);//citim numele
			strcpy(aeroport.nume, token);

			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			int poz = aeroport.nrTerminale % 2;//inserez pe prima linie aeroporturile care au nr par de terminale (linia 1 pt pare ex Otopeni)

			aeroporturi[poz] = adaugaAeroport(aeroporturi[poz], aeroport, &(nrAeroporturiLinie[poz]));

		}
		fclose(f);
	}

}

//sem 4 modific
void afisareAeroport(struct Aeroport* aeroport)
{
	printf(" %d. %s are %d terminale.\t",  aeroport-> id, aeroport->nume, aeroport->nrTerminale);

}

void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim)
{
	printf("AFISARE VECTOR:\n");
	for (int i = 0; i < dim; i++)
	{
		afisareAeroport(&aeroporturi[i]);
	}
}


//sem 4 - adaug
void afisareMatrice(struct Aeroport** matrice, int nrClustere, int* nrColoane)
{
	for (int i = 0; i < nrClustere; i++)
	{
		for (int j = 0; j < nrColoane[i]; j++)
		{
			afisareAeroport(&matrice[i][j]);
		}
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


//nr mediu dxe terminale pt aeroporturile par/impare
float mediaTerminale(struct Aeroport** matrice, int* nrAeroporturiLinie, int paritate)
{
	paritate = paritate % 2;
	int count = 0;
	int suma = 0;

	for (int i = 0; i < nrAeroporturiLinie[paritate]; i++)
	{
	
		
		suma += matrice[paritate][i].nrTerminale;
	}
	if (nrAeroporturiLinie[paritate])
	{
		return suma / nrAeroporturiLinie[paritate];

	}
	
	return 0;
}

//returneaza un aeroport dupa id
struct Aeroport* cautaAeroportID(struct Aeroport** matrice, int* nrColoane, int nrLinii, int Id)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; i < nrColoane[i]; j++)
		{
			if (matrice[i][j].id == Id)
			{
				return &(matrice[i][j]);
			}
		}
	
	}
	return NULL;
}

void dezalocareVector(struct Aeroport** aeroporturi, int* dim)
{
	for (int i = 0; i < (*dim); i++)
	{
		free((*aeroporturi)[i].nume);
		//free(aeroporturi[i]);//??
	}
	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = 0;
}


//seminar 4 - adaug 
void dezalocareMatrice(struct Aeroport*** matrice, int** nrColoane, int* nrClustere)
{
	for (int i = 0; i < (*nrClustere); i++)
	{
		dezalocareVector(&((*matrice)[i]), &((*nrColoane)[i]));
	}

	free(*matrice);
	(*matrice) = NULL;

	free(*nrColoane);
	(*nrColoane) = NULL;
	(*nrClustere) = 0;

}


void main()
{
	struct Aeroport** aeroporturi ;
	int nrLinii=2;

	//alocam spatiu
	int* nrColoane= (int*) malloc(sizeof(int)*nrLinii);
	aeroporturi = (struct Aeroport**)malloc(sizeof(struct Aeroport*)*nrLinii);
	
	//parcurgem vectorii (matricea)
	for (int i = 0; i < nrLinii; i++)
	{
		nrColoane[i] = 0;
		aeroporturi[i] = NULL;//matricea
	}

	citireMatriceFisier("aeroport.txt", nrColoane, nrLinii, aeroporturi);

	afisareMatrice(aeroporturi, nrLinii, nrColoane);

	float medie = mediaTerminale(aeroporturi, nrColoane, 12);

	printf("Media pt aeroporturile pare : %.2f", medie);
	printf("\n\n");

	afisareAeroport(cautaAeroportID(aeroporturi, nrColoane, nrLinii, 2));


	dezalocareMatrice(&aeroporturi, &nrColoane, &nrLinii);


}