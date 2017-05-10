
#include <cstdlib>
#include <stdio.h>
#include <time.h>


//Typedef para seleccionar el tipo de algoritmo a usar
typedef enum{ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE} inputType;


//*****************************************************************************
//              Random
//Genera un numero aleatorio tra 9 e 0
int aleatorio(){ 
    
    time_t t;
    srand(time(NULL));
    return rand() % 9;
};


//******************************************************************************
//              Funzione Genera_array
//Su funcion es generar un array(alocarlo en memoria) y llenarlo 
//
//******************************************************************************
int * genera_array(int dimensione,inputType tipo_schema){
    
    int i;  //INIZIO
    //Alocamos el vector
    int *array = (int *) malloc (dimensione * sizeof (int));
    
    //Si elegimos ordenado
    if(tipo_schema==ORDINATO){
        for(i=0;i<dimensione;i++){
            array[i]=i;
        }
    }
    
    //Si es casi ordenado(mitad ordenada)
    if(tipo_schema==QUASI_ORDINATO){
        int mitad=dimensione/2;     //mitdad del vector
        for(i=0;i<mitad;i++){
            array[i]=i;
        }
        for(mitad;mitad<dimensione;mitad++){
            array[mitad]=rand()%9;
        }
    }
    
    //Si es un vector ordenado invertidamente
    if(tipo_schema==INV_ORDINATO){   
        for(i=0;i<dimensione;i++){
            array[i]=dimensione-i;
        }
    }
    
    //Si es un vector de numero aleatorios
    if(tipo_schema==CASUALE){
        for(i=0;i<dimensione;i++){
            array[i]=rand() % 9;
        }
    }
    
    return array;
};

//*****************************************************************************
//              Funzione FindMin
//Su funcion es encontrar el minimo del array.Es un algoritmo recursivo
//******************************************************************************

int findmin (int miarray[], int minpos, int start, int dim){
    //Si el array solo tiene un elemento
    if(start==dim){
        return minpos;
    }
    //va recorriendo todo el array,comparando elementos
    if(miarray[start]<miarray[minpos]){
        minpos=start;
    }

    return findmin(miarray,minpos,start+1,dim);  
    
};

//*****************************************************************************
//              Funcion Scambia
//Su funcion es cambiar dos elementos
//******************************************************************************

void * scambia(int miarray[],int i,int j){
    int aux;
    aux=miarray[i];
    miarray[i]=miarray[j];
    miarray[j]=aux;
};

//*****************************************************************************
//              Funcion Display
//Su funcion es estampar en pantalla el array
//******************************************************************************

void * Display(int miarray[],int dimensione){
    int inicio=0;
    for(inicio;inicio<dimensione;inicio++){
        printf("%d ",miarray[inicio]);
    }
};

//*****************************************************************************
//              Funcion Ricorsiva
//Ordena el vector de forma recursiva
//******************************************************************************

int * selectionSortRec(int miarray[], int dimA, int start){

    int minIndex=0;
    //Caso base
    if(start>=dimA-1){
        return miarray;
    }
        //Buscamos el minimo
        minIndex=findmin(miarray, start, start,dimA);
        //Cambiamos el valor minimo al siguiente
        scambia(miarray,start,minIndex);
        //LLamamos de nuevo a la funcion
        selectionSortRec(miarray,dimA,start+1);
  
};


//*****************************************************************************
//              FUNCION main
//******************************************************************************

int main(int argc, char** argv) {
    
    //Tempo di esecuzione
    clock_t start, end;
    double time;
    
    //Contadores
    int i,j;
    int dimensione;
    int selezione_dimensione;
    int selezione_tipi;
    inputType type; //Tipi vettore
    
    printf("Scriva la dimensione del vettore:\n1 per 100\n2 per 1.000\n3 "
            "per 10.000\n4 per 100.000\n5 per 200.000\n6 per 500.000\n");
    scanf("%d",&selezione_dimensione);
    
    //Filtro
    while(selezione_dimensione<1 || selezione_dimensione>6){
        printf("Il numero non e justo.Scriva un numero justo\n");
        scanf("%d",&selezione_dimensione);
    }
    
    
    //Selecion de la dimension
    switch(selezione_dimensione){
        case 1: 
            dimensione=100;
            break;
        case 2:
            dimensione=1000;
            break;
        case 3:
            dimensione=10000;
            break;
        case 4:
            dimensione=100000;
            break;
        case 5:
            dimensione=200000;
            break;
        case 6:
            dimensione=500000;
            break;
    
    }
 
    printf("\nScriva il tipo di vettore:\n7 per un vettore ordinato\n8 per un "
            "vettore quasi ordinato\n9 per un vettore inversamente ordinato\n10 "
            " per un vettore aleatorio\n");
    
    scanf("%d",&selezione_tipi);
    //Filtro
    while(selezione_tipi<7 || selezione_tipi>10){
        printf("Il numero non e justo.Scriva un numero justo\n");
        scanf("%d",&selezione_tipi);
    }
    //Seleccion de tipo de vector
    switch(selezione_tipi){
        case 7: 
            type=ORDINATO;
            break;
        case 8:
            type=QUASI_ORDINATO;
            break;
        case 9:
            type=INV_ORDINATO;
            break;
        case 10:
             type=CASUALE;
            break;
    
    }
    
    printf("La dimension es:%d\n",dimensione);
    
    //Genera el vector segun las opciones indicadas
    int * miarray=genera_array(dimensione,type);
    
    //*****************************************
    //Descomentar para comprobar
    //*****************************************
    
    //printf("\nNostro array original e:");
    //Display(miarray,dimensione);
    
    printf("\n\n");
    int k=0;
    start=clock();
    
    //Se ordena el vector    
    selectionSortRec(miarray,dimensione,k);
    
    end=clock();
    //*****************************************
    //Decomentare per comprobare
    //*****************************************
            
    //printf("\n***** il array ordinato e \n");
    //Display(miarray,dimensione);
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\ntempo impiegato: %f secondi", time);

    
}