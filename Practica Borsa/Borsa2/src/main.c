#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include "rlutil.h"
#include "llibreriaPropia.h"
#include "llibreriaExercici.h"

#define MINCOTMIN 0
#define MAXCOTMIN 10
#define MINCOTMAX 30
#define MAXCOTMAX 40

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand(time(NULL));
    
    int min, max, inicial;                 // Variables per les preguntes inicials
    int dia = 1, baixades = 0, errors = 0; // contador dies, baixades, errors
    int cotAnt1, cotActual;       // variables per guardar valors
    int numGenerat;                        // variable per el rand
    int x = 1, y = 8;                      // variables posicionament inicial
    bool sortir = false;                   // variable per controlar la sortida

    printf("Benvingut al SISTEMA GESTOR DE COTITZACIONS A BORSA.\n");
    printf("Realitzat per: Ivan Fernàndez Montalvo.\n\n");

    /// Inici de les peticions de variables al usuari. Controlades dins els nombres correctes.
    do
    {
        printf("Introdueix la cotització mínima. (0...10): ");
        scanf("%d", &min);
        if (min > 10 || min < 0)
        {
            errors++;
        } // Variable per controlar si l'usuari erra la introduccio de dades.
    } while (min > MAXCOTMIN || min < MINCOTMIN);
    do
    {
        printf("Introdueix la cotització màxima. (30...40): ");
        scanf("%d", &max);
        if (max > 40 || max < 30)
        {
            errors++;
        }
    } while (max > MAXCOTMAX || max < MINCOTMAX);
    do
    {
        printf("Introdueix la cotització inicial. (%d...%d): ", min, max);
        scanf("%d", &inicial);
        if (inicial > max || inicial < min)
        {
            errors++;
        }
    } while (inicial > max || inicial < min);

	cls();

    // Guardo la cotitzacio inicial a cotActual, per no perdre-la.
    cotActual = inicial;
   
	int amplada=60, alçada=40;
	int x0dibuix=1,y0dibuix=1;

	//pinto la vertical desde 0 a 40.
	for(int fila=alçada;fila>=0;fila--)
	{
		gotoxy(x0dibuix,y0dibuix);
		printf("%2d|",fila);
		y0dibuix=y0dibuix+1;
		if(fila==max)
		{
			gotoxy (x0dibuix+3,y0dibuix-1);
			setColor(BLUE);
			for (x0dibuix=1;x0dibuix<61;x0dibuix++){
				printf("-");
			} 
			setColor(WHITE);
			x0dibuix=1;
		}
		if(fila==min)
		{
			gotoxy (x0dibuix+3,y0dibuix-1);
			setColor(RED);
			for (x0dibuix=1;x0dibuix<61;x0dibuix++){
				printf("-");
			} 
			setColor(WHITE);
			x0dibuix=1;
		}

	}
	//pinto la horitzontal
	int numero=0;
	for(int col=1;col<=48;col++)
	{		
		if(col<=1){gotoxy(x0dibuix+2,y0dibuix);printf("01");}
		gotoxy(x0dibuix+3,y0dibuix-1);
		x0dibuix=x0dibuix+1;
		printf("-");

		if(col%4==0 && col<=amplada)
		{
			x0dibuix=x0dibuix+1;
			printf("|");
			gotoxy(x0dibuix+2,y0dibuix);
			numero=numero+5;
			printf("%d",numero);
		}
		
	}

    gotoxy(x0dibuix+3,y0dibuix-1);
    printf("------>");
	gotoxy(x0dibuix+9,y0dibuix);
	printf("dia");

    dia=1;
    x=4,y=41;
    sortir=false;
    baixades=0;
    do{
        if(inicial<min){ // controlo si es menor a cotitzacio inicial
            setColor(RED);
            gotoxy(x,y-inicial);
            baixades++; //incremento baixades en 1
            printf("*");
        }else if (inicial>=max && inicial<=MAXCOTMAX){ //controlo si es major a cotitzacio maxima i menor o igual al define (40)
            setColor(BLUE);
            gotoxy(x,y-inicial);
            printf("*");    
        }else if(inicial>MAXCOTMAX){ //controlo si es major al define Maxim (40)
            gotoxy(x,1);
            setColor(GREEN);
            printf("^");
        }else{ 
            baixades=0; //resetejo les baixades
            setColor(GREY); 
            gotoxy(x,y-inicial);
            printf("*");
        }
        //Controlo si es menor a 0 per sortir
        if(inicial<0){
            sortir=true; 
        }
        x++;
        cotAnt1=inicial; //guardo el valor a cotAnt1
        numGenerat=rand()%5-2; // genero l'aleatori
        inicial=cotAnt1+numGenerat; // el sumo a cotAnt1 i l'assigno a inicial
        dia++; // incremento el dia
        Sleep(200);
    }while (dia <= 60 && sortir==false && baixades<3); 

    gotoxy (1,43);
    setColor(GREY);
    acabament();
    return 0;
}
