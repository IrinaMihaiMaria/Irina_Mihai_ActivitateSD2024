/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Elev Elev;
typedef struct Nod Nod;

struct Elev
{
	int id;
	int nrMedii;
	float* medii;
};

struct Nod
{
	Elev info;
	Nod* st;
	Nod* dr; 
};


void inserareArbore(Nod** radacina, Elev elev)
{
	if ((*radacina)!=NULL)
	{
		if ((*radacina)->info.id > elev.id)
		{
			inserareArbore(&((*radacina)->st), elev);
		}
		else
		{
			inserareArbore(&((*radacina)->dr), elev);
		}
	}
	else
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod));

		nod->info = elev;
		nod->st = NULL; 
		nod->dr = NULL;

		*radacina = nod;
	}
}

Elev citireElev(FILE* fp)
{
	Elev elev;
	fscanf(fp, "%d", &elev.id);
	fscanf(fp, "%d", &elev.nrMedii);

	elev.medii = malloc(sizeof(float) * elev.nrMedii);

	for (int i = 0; i < elev.nrMedii; i++)
	{
		fscanf(fp, "%f", &(elev.medii[i]));
	}
	
	return elev;
}



Nod* citireFisier(char* numeFisier)
{
	Nod* arbore = NULL;
	if (numeFisier != NULL)
	{
		FILE* fp = fopen(numeFisier, "r");

		int nrElevi;
		fscanf(fp, "%d", &nrElevi);

		for (int i = 0; i < nrElevi; i++)
		{
			Elev elev = citireElev(fp);

			inserareArbore(&arbore, elev);
		}

		fclose(fp);
	}
	else
	{
		return NULL;
	}

	

	return arbore;
}



void afisareElev(Elev e)
{
	printf("Elevul cu id-ul %d are mediile, " , e.id);
	for (int i = 0; i < e.nrMedii; i++)
	{
		printf("%5.2f  ", e.medii[i]);
	}
	printf("\n");
}



void afisareInOrder(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareInOrder(arbore->st);
		afisareElev(arbore->info);
		afisareInOrder(arbore->dr);

	}
}



float calculeazaMedieElev(Elev e)
{
	if (e.nrMedii != NULL)
	{
		float suma = 0;
		for (int i = 0; i < e.nrMedii; i++)
		{
			suma += e.medii[i];
		}
		return suma / e.nrMedii;
	}
	else
	{
		printf("Elevul nu are medii!");
	}
	
}



float calculeazaSumaNote(Nod* arbore, int* nrNote)
{
	if (arbore != NULL)
	{
		
		float suma = 0;
		
		for (int i = 0; i < arbore->info.nrMedii; i++)
		{
			suma += arbore->info.medii[i];
		}

		(*nrNote) += arbore->info.nrMedii;
		
		float sumaS = calculeazaSumaNote(arbore->st, nrNote );


		
		float sumaD = calculeazaSumaNote(arbore->dr, nrNote);
		
		return suma + sumaS + sumaD;
	}
	else {
		return 0;
	}

}



float calculeazaMedieGenerala(Nod* arbore)
{
	int nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &nrNote);
	printf("\n\n%d", nrNote);
	if (nrNote > 0)
	{
		return suma / nrNote;
	}
	else
	{
		return 0;
	}

	
}


void main()
{
	Nod* arbore = citireFisier("Elevi.txt");
	afisareInOrder(arbore);

	printf("Media este: %5.2f", calculeazaMedieGenerala(arbore));
}

*/

