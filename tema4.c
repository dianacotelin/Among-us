// 311CD COTELIN MARIA-DIANA
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));
	switch(playerRole)
	{
		case Rotator:
			str = strcpy(str, "Rotator");
			break;
		case Decoder:
			str = strcpy(str, "Decoder");
			break;
		case Invertor:
			str = strcpy(str, "Invertor");
			break;
		case Impostor:
			str = strcpy(str, "Impostor");
			break;
	}
	return str;
}

// Task 1
void *RotateMatrix(void *input)
{
	int n = *((int*) input);
	int i, j, temp, p;
	int **Matrix = (int **)calloc(n, sizeof(int *));
	if (Matrix == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}
	for (i = 0; i < n; i++)
	{
		Matrix[i] = calloc(n, sizeof(int));
	}

	for(i = 0; i < n; i++)
	{
	    for(j = 0; j < n; j++)
		{
			temp = j + 1;
			p = 10;
			while (temp > 9)
			{
				p = p*10;
				temp = temp/10;
			}
		   Matrix[i][j] = (i + 1)*p + j + 1;
		}
	}

    for (i = 0; i < n/2; i++)
	{
        for (j = i; j < n - i - 1; j++)
		{
            temp = Matrix[i][j];
            Matrix[i][j] = Matrix[n - 1 - j][i];
            Matrix[n - 1 - j][i] = Matrix[n - 1 - i][n - 1 - j];
            Matrix[n - 1 - i][n - 1 - j] = Matrix[j][n -1 - i];
            Matrix[j][n - 1 - i] = temp;
        }
    }
    
    char *aux;
	char sir[100];
	sir[0] = '\0';

	aux = (char*)calloc(MAX_LEN_STR_OUT, sizeof(char));
	if (aux == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

	for( i = 0; i < n; i++)
	{
	    for ( j = 0; j < n; j++)
		{
		    sprintf(sir, "%d", Matrix[i][j]);
			if((i == 0)&&(j == 0))
                strcpy(aux, sir);
            else
		       strcat (aux, sir);
			if( j != n-1)
			   strcat (aux, " ");
		}
		if( i != n-1 )
		   strcat(aux, "\n");
	}

	for (i = 0; i< n; i++)
	{
		free(Matrix[i]);
	}
	free(Matrix);

	return (void*)aux;
}

// Task 2
void *DecodeString(void *input)
{
	char *sir_c = (char*)input;
	char *tok, *aux;
	char sumaf[100];

	aux = (char*)calloc(MAX_LEN_STR_OUT, sizeof(char));
	if (aux == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

	int auxiliar = 0, sum = 0;
    tok=strtok(sir_c, "_");
    auxiliar = atoi(tok);
    sum = sum + auxiliar;
    tok = strtok(NULL, "_");
	while(tok)
	{
		auxiliar = atoi(tok);
		sum = sum + auxiliar;
		tok = strtok(NULL, "_");
	}

	sprintf(sumaf, "%d", sum);
	strcpy(aux, sumaf);

	return (void*)aux;
}

//Task 3
void *InvertArray(void *input)
{
	int *point = (int*)input;
	int n, i, cop = 0, inc, sf;
	char *aux;
	aux = (char*)calloc(MAX_LEN_STR_OUT, sizeof(char));
	if (aux == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

    n = point[0];
	char sir[100];
	sir[0] = '\0';

	if(n % 2 == 0)
	{
		for( i = 1; i < n; i++ )
		{
           cop = point[i];
		   point[i] = point[i + 1];
		   point[i + 1] = cop;
           i = i + 1;
		}
	}
	else
	{
		inc = 1;
		sf = n;
		while (inc < sf)
		{
			cop = point[inc];
			point[inc] = point[sf];
			point[sf] = cop;
			inc++;
			sf--;
		}
	}

	for( i = 1; i <= n; i++)
	{
		    sprintf(sir, "%d", point[i]);
			if(i == 1)
                strcpy(aux, sir);
            else
		       strcat (aux, sir);
			if( i != n)
			   strcat (aux, " ");
	}

	return (void*)aux;
}

//Task 4
Player *allocPlayer()
{
	Player *aux = (Player*)malloc(sizeof(Player));
	if (aux == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

	aux->alive = 1;
	aux->name = malloc(sizeof(char)*MAX_LEN_STR_ATR);
	if (aux->name == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}
	aux->color = malloc(sizeof(char)*MAX_LEN_STR_ATR);
	if (aux->color == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}
	aux->hat = malloc(sizeof(char)*MAX_LEN_STR_ATR);
	if (aux->hat == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

	aux->indexOfLocation = 0;
	
    return aux;
}

//Task 4
Game *allocGame()
{   
	Game *aux = (Game*)malloc(sizeof(Game));
	if (aux == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

	aux->name = (char*)malloc(sizeof(char)*MAX_LEN_STR_ATR);
	if (aux->name == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

	return (void*)aux;
}

//Task 5
Player *ReadPlayer(FILE *inputFile)
{   
	Player* p;
    int i = 0, aux1 = 0, aux2 = 0;
	char aux[20];

    p=allocPlayer();
	if (p == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

    fscanf(inputFile, "%s", p->name);
    fscanf(inputFile, "%s", p->color);
	fscanf(inputFile, "%s", p->hat);
	fscanf(inputFile, "%d\n", &(p->numberOfLocations));

	p->locations = (Location*)calloc(MAX_LEN_STR_ATR, sizeof(Location));
	if (p == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}
	
	for(i = 0; i < (p->numberOfLocations); i++)
	{
		fscanf(inputFile,"(%d,%d)\n", &aux1, &aux2);
		p->locations[i].x = aux1;
		p->locations[i].y = aux2;
	}

	fscanf(inputFile, "%s", aux);
    if (aux == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

	if(strcmp("Rotator", aux) == 0)
	{
	    p->ability = Abilities[0];
		p->playerRole = Rotator;
	}
	if(strcmp("Decoder", aux) == 0)
	{
		p->ability = Abilities[1];
		p->playerRole = Decoder;
	}
	if(strcmp("Invertor", aux) == 0)
	{
	    p->ability = Abilities[2];
		p->playerRole = Invertor;
	}
	if(strcmp("Impostor", aux) == 0)
	{
	    p->ability = Abilities[3];
		p->playerRole = Impostor;
	}
	return p;
}

// Task 5
Game *ReadGame(FILE *inputFile)
{   
    Game* g;
	int j;

	g = allocGame();
	if (g == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}
	fscanf(inputFile, "%s", g->name);
	fscanf(inputFile, "%d", &(g->killRange));
	fscanf(inputFile, "%d", &(g->numberOfCrewmates));

	g->crewmates = (Player *)calloc((g->numberOfCrewmates), sizeof(Player));
	if (g->crewmates == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

	for(j = 0; j < (g->numberOfCrewmates); j++)
	{
		g->crewmates[j] = ReadPlayer(inputFile);
	}
	
    g->impostor = ReadPlayer(inputFile);
	return g;
}

// Task 6
void WritePlayer(Player *player, FILE *outputFile)
{
	int i, aux1, aux2;
	char* r;
	r = fromEnumtoString(player->playerRole);

	fprintf(outputFile, "Player %s with color %s, hat %s and role %s has entered the game.\n", player->name, player->color, player->hat, r);
	fprintf(outputFile, "Player's locations:");
	for(i = 0; i < (player->numberOfLocations); i++)
	{
		aux1=player->locations[i].x;
		aux2=player->locations[i].y;
		fprintf(outputFile, " (%d,%d)", aux1, aux2);
	}
	fprintf(outputFile, "\n");

	free(r);
}

// Task 6
void WriteGame(Game *game, FILE *outputFile)
{
	int j;

	fprintf(outputFile, "Game %s has just started!\n", game->name);
	fprintf(outputFile, "	Game options: \n");
	fprintf(outputFile, "Kill Range: %d\n", game->killRange);
	fprintf(outputFile, "Number of crewmates: %d\n", game->numberOfCrewmates);
	fprintf(outputFile, "\n");
	fprintf(outputFile, "	Crewmates:\n");
	for(j = 0; j < (game->numberOfCrewmates); j++)
	{
		WritePlayer(game->crewmates[j], outputFile);
	}
	fprintf(outputFile, "\n");
	fprintf(outputFile, "	Impostor:\n");
	WritePlayer(game->impostor, outputFile);
}

//Task 7
void *KillPlayer(void *input)
{
    Game *game = (Game*)input;
	int a, b, c, d, j, ok = 0, aux, dist, dist1;
	char sir[MAX_LEN_STR_OUT], distanta[20];
	char *outp;
	sir[0] = '\0';

	outp = (char*)calloc(MAX_LEN_STR_OUT, sizeof(char));
	if (outp == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

	a = game->impostor->locations[game->impostor->indexOfLocation].x;
	b = game->impostor->locations[game->impostor->indexOfLocation].y;
    dist = (game->killRange);
	for(j = 0; j < (game->numberOfCrewmates); j++)
	{
		c = game->crewmates[j]->locations[game->crewmates[j]->indexOfLocation].x;
		d = game->crewmates[j]->locations[game->crewmates[j]->indexOfLocation].y;
		dist1 = abs(a-c) + abs(b-d);
		if((dist1 <= dist) && ((game->crewmates[j]->alive) == 1))
		{
			dist = dist1;
			ok = 1;
			aux = j;
		}
	}

	strcpy(sir, "Impostor ");
	strcat(sir, game->impostor->name);
	if(ok == 0)
	{
		strcat(sir, " couldn't kill anybody.");
	}
	else
	{
		game->crewmates[aux]->alive=0;
		strcat(sir, " has just killed crewmate ");
		strcat(sir, game->crewmates[aux]->name);
		strcat(sir, " from distance ");
		sprintf(distanta, "%d", dist);
		strcat(sir, distanta);
		strcat(sir, ".");
	}

    strcpy(outp, sir);
    return (void*)outp;
}

// Task 8
void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{   
	int i;
	char* auxil;
	
	for(i = 0; i < (game->numberOfCrewmates); i++)
	{
		game->crewmates[i]->indexOfLocation++;	
		if ((game->crewmates[i]->indexOfLocation) >= (game->crewmates[i]->numberOfLocations))
		{
			game->crewmates[i]->indexOfLocation = 0;
		}
		if(game->crewmates[i]->alive == 0)
		{
			fprintf(outputFile, "Crewmate %s is dead.\n", game->crewmates[i]->name);	
		}
		else
		{
			fprintf(outputFile, "Crewmate %s went to location (%d,%d).\n", game->crewmates[i]->name, game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation].x, game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation].y);
			fprintf(outputFile, "Crewmate %s's output:\n", game->crewmates[i]->name);
			auxil = (char*)(game->crewmates[i]->ability(inputMatrix[i]));
			fprintf(outputFile, "%s", auxil);
			fprintf(outputFile, "\n");

			free(auxil);
		}
	}

	game->impostor->indexOfLocation++;
	if((game->impostor->indexOfLocation)>=(game->impostor->numberOfLocations))
	{
		game->impostor->indexOfLocation = 0;
	}

	fprintf(outputFile, "Impostor %s went to location (%d,%d).\n", game->impostor->name, game->impostor->locations[game->impostor->indexOfLocation].x, game->impostor->locations[game->impostor->indexOfLocation].y);
	fprintf(outputFile, "Impostor %s's output:\n", game->impostor->name);
	auxil = (char*)(game->impostor->ability(game));
	fprintf(outputFile, "%s", auxil);
	fprintf(outputFile, "\n");

    free(auxil);
}

// Task 9
void FreePlayer(Player *player)
{
	free(player->name);
	free(player->color);
	free(player->hat);
	free(player->locations);
	free(player);
}

// Task 9
void FreeGame(Game *game)
{
	int i;
	free(game->name);
	for (i = 0; i < game->numberOfCrewmates; i++)
	{
	    FreePlayer(game->crewmates[i]);
	}
	FreePlayer(game->impostor);
	free(game->crewmates);
	free(game);
}