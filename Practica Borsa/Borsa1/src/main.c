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
    int diaTempMax, diaTempMin;            // variables per controlar que el dia Max o Min repetit, guardi l'ultim
    int cotAnt1, cotAnt2, cotActual;       // variables per guardar valors
    int numGenerat;                        // variable per el rand
    int acumCot = 0;                       // acumulador suma cotitzacions
    int cotMax, diaMax, cotMin, diaMin;    // variables pel resum final
    int x = 1, y = 8;                      // variables posicionament inicial
    float mitjana;                         // variable per la mitjana
    bool sortir = false;                   // variable per controlar la sortida

    printf("Benvingut al SISTEMA GESTOR DE COTITZACIONS A BORSA.\n");
    printf("Realitzat per: Ivan Fernàndez Montalvo.\n\n");

    /// Inici de les peticions de variables al usuari. Controlades dins els nombres correctes.
    do
    {
        printf("Introdueix la cotització mínima. (%d...%d): ",MINCOTMIN,MAXCOTMIN);
        scanf("%d", &min);
        if (min >MAXCOTMIN  || min < MINCOTMIN)
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

    // Guardo la cotitzacio inicial a cotActual, per no perdre-la. També a mínima i màxima.
    cotActual = inicial;
    cotMax = inicial;
    cotMin = inicial;
    // Guardo diaMax i diaMin
    diaMax = 1;
    diaMin = 1;
    // Faig un while per controlar els 60 dies o la entrada en baixades.
    while (dia <= 60 && baixades < 3 && sortir == false)
    {
        // controlo si baixa de 0
        if (cotActual < 0)
        {
            sortir = true;
        }
        // switch pels 3 casos: dia 1, dia 2, resta
        switch (dia)
        {
        case 1:
            printf("\nDia %d:\t  %2d", dia, cotActual);
            break;
        case 2:
            printf("\nDia %d:\t  %2d\t%2d", dia, cotActual, cotAnt1);
            break;
        default:
            gotoxy(x, y + errors);
            printf("Dia %d:\t  %2d\t%2d\t%2d", dia, cotActual, cotAnt1, cotAnt2);
            break;
        }
        // Controlo si la cotitzacio actual es major o igual a la maxima i actualitzo si cal en el temporal
        if (cotActual >= cotMax)
        {
            cotMax = cotActual;
            diaMax = dia;
        } // Controlo si la cotitzacio actual es menor o igual i actualitzo si cal en el temporal
        else if (cotActual <= cotMin)
        {
            cotMin = cotActual;
            diaMin = dia;
        }
        

        // Si el dia es igual a 31, modifico x i y, per posicionarme per la seguent columna.
        if (dia == 31)
        {
            x = 44;
            y = 8;
        }
        // vaig sumant a la variable totes les cotitzacions generades
        acumCot = acumCot + cotActual;
        // si la cotitzacio actual es menor a la minima, augmento baixades en 1. Sino, resetejo.
        if (cotActual < min)
        {
            baixades++;
        }
        else
        {
            baixades = 0;
        }
        // guardo cotitzacio anterior 1 a cotitzacio anterior 2
        cotAnt2 = cotAnt1;
        // guardo cotitzacio actual a cotitzacio anterior 1
        cotAnt1 = cotActual;
        // genero un valor entre 0 i 4, i li resto 2 per obtenir: -2, -1, 0, 1, 2
        numGenerat = rand() % 5 - 2;
        // assigno a cotitzacio actual el valor generat anterior + el random generat
        cotActual = cotAnt1 + numGenerat;
        // controlo els valors i pinto quan toqui
        if (cotActual < min)
        {
            setColor(RED);
        }
        else if (cotActual > max)
        {
            setColor(BLUE);
        }
        else
        {
            setColor(GREY);
        }
        dia++; // incremento el dia
        y++;   // incremento la y per anar baixant
    }
    
    setColor(GREY);

    // per no trepitjar el missatge final
    if (dia > 30)
    {
        gotoxy(1, 37 + errors);
    }
    // if per saber si ha sortit perque baixades ha arribat a 3, printo missatge.
    if (baixades == 3)
    {
        printf("\n\nL'EMPRESA HA ENTRAT EN SUSPENSIO DE PAGAMENTS.");
    }
    else if (sortir == true)
    { // else if per si baixa de 0
        printf("\n\nL'EMPRESA HA CAIGUT PER SOTA DE ZERO.");
    }
    // Quan dia surt del bucle li he de restar 1, per tenir el valor real
    dia = dia - 1;
    // Calculo la mitjana
    mitjana = (float)acumCot / dia;
    // RESUM
    printf("\n\nDADES INICIALS:\n");
    printf("\tCotització Mínima: %d\n\tCotització Màxima: %d\n\tCotització Inicial: %d\n", min, max, inicial);
    printf("DADES RESUM:\n");
    printf("\tEl valor promig de les cotitzacions ha sigut de: %.2f\n", mitjana);
    printf("\tEl dia que s'ha obtingut la darrera màxima cotització ha sigut: %d i amb un valor màxim de: %d\n", diaMax, cotMax);
    printf("\tEl dia que s'ha obtingut la darrera mánima cotització ha sigut: %d i amb un valor mínim de: %d\n\n", diaMin, cotMin);

    acabament();
    return 0;
}
