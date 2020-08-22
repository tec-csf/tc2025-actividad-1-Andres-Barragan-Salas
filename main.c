/* Autor: Andres Barragan Salas
          A01026567
   Actividad 1: Programación Avanzada
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define E 5

// Estructura para mantener los datos de los pacientes
typedef struct {
    char * nombre;
    char * apellidos;
    char * telefono;
    int edad;
} paciente;

// Variables globales para mantener el numero de camas y sus respectivas asignaciones
int N = E; 
paciente * pacientes;

// Definición genérica de los métodos utilizados
typedef void (* opcion)();

// Declaración de los métodos utilizados
void ingresarPaciente();
void pacienteEnCama();
void altaDePacienteEnCama();
void listaDePacientes();
void numeroDeCamasDisponibes();
void numeroDeCamasOcupadas();
void liberarPaciente(paciente * paciente);
void liberarMemoria();

int main(int argc, char **argv)
{
    // Se asigna el la cantidad de camas inicial
    pacientes = (paciente *) malloc(sizeof(paciente) * N);
    int opc = 0;

    // Cada opción disponible es asignada a un arreglo de métodos
    opcion * opciones = (opcion *) malloc(6 * sizeof(opcion));
    *(opciones) = ingresarPaciente;
    *(opciones+1) = pacienteEnCama;
    *(opciones+2) = altaDePacienteEnCama;
    *(opciones+3) = listaDePacientes;
    *(opciones+4) = numeroDeCamasDisponibes;
    *(opciones+5) = numeroDeCamasOcupadas;
    
    // Obtener la opción deseada por el usuario hasta que elija salir del programa
    do {
        printf("1-Ingresar un paciente\n2-Conocer estado de una cama\n3-Dar de alta a un paciente\n4-Lista de pacientes\n5-Cantidad de camas disponibles\n6-Cantidad de camas ocupadas\n0-Salir\nSeleccione la opción: ");
        scanf("%d",&opc);
        
        if (opc == 0) 
            break; 
        else if (opc>=1 && opc<=6)
            (*(opciones+opc-1))();
        else
            printf("Opcion no valida");
        
    } while (opc != 0);
    
    // Liberar la memoria al finalizar la ejecución
    liberarMemoria();

    return 0;
}

/* Ingresa los datos del paciente y le asigna una cama (en un arreglo de pacientes) */
void ingresarPaciente() {
    // Obtener la primera cama disponible: 
    int i; 
    for (i=0; i<=N; ++i)
        if (i == N) {
            pacientes = realloc(pacientes, sizeof(paciente) * (N+=E));
            break;
        }
        else if ((pacientes+i)->nombre == NULL)
            break;

    // Obtener la información del paciente y asignarlo a la cama disponible
    printf("\nDatos de la paciente:\n");
        
    printf("Ingrese el nombre: ");
    (pacientes+i)->nombre = (char *) malloc(sizeof(char) * 30);
    scanf("%s", (pacientes+i)->nombre);
    
    printf("Ingrese el apellido: ");
    (pacientes+i)->apellidos = (char *) malloc(sizeof(char) * 35);
    scanf("%s", (pacientes+i)->apellidos);
    
    printf("Ingrese el telefono: ");
    (pacientes+i)->telefono = (char *) malloc(sizeof(char) * 10);
    scanf("%s", (pacientes+i)->telefono);

    printf("Ingrese la edad: ");
    scanf("%d", &(pacientes+i)->edad);

    printf("El paciente %s %s ha sido asignado a la cama %d.\n\n", (pacientes+i)->nombre, (pacientes+i)->apellidos, i);
}

/* Obtiene la información de un paciente dado su número de cama*/
void pacienteEnCama() {
    // Se pide al usuario el número de cama
    int cama;
    printf("\nIngrese el numero de cama: ");
    scanf("%d", &cama);

    // Se determina si la cama no existe o está desocupada
    if (cama >= N) {
        printf("La cama %d aun no existe.\n\n", cama);
        return;
    }
    else if ((pacientes+cama)->nombre == NULL) {
        printf("La cama %d se encuentra desocupada.\n\n", cama);
        return;
    }

    // Se imprime la información del paciente
    printf("Paciente:\n");
    printf("\tNombre: %s %s\n", (pacientes+cama)->nombre, (pacientes+cama)->apellidos);
    printf("\tTelefono: %s\n", (pacientes+cama)->telefono);
    printf("\tEdad: %d\n\n", (pacientes+cama)->edad);
}

/* Se da de alta el paciente en una cama dada */
void altaDePacienteEnCama() {
    // Se pide al usuario el número de cama
    int cama;
    printf("\nIngrese el numero de cama: ");
    scanf("%d", &cama);

    // Se determina si la cama no existe o está desocupada
    if (cama >= N) {
        printf("La cama %d aun no existe.\n\n", cama);
        return;
    }
    else if ((pacientes+cama)->nombre == NULL) {
        printf("La cama %d se encuentra desocupada.\n\n", cama);
        return;
    }

    printf("\nEl paciente %s %s ha sido dado de alta, la cama %d ahora se encuentra desocupada.\n\n", (pacientes+cama)->nombre, (pacientes+cama)->apellidos, cama);

    // Se asignan valores nulos al paciente que se encuentra en esta cama
    (pacientes+cama)->nombre = NULL;
    (pacientes+cama)->apellidos = NULL;
    (pacientes+cama)->telefono = NULL;
    (pacientes+cama)->edad = NULL;
}

/* Se obtiene la lista de todos los pacientes presentes en el hospital */
void listaDePacientes() {
    printf("\nListado de pacientes:\n");

    // Se itera sobre todas las capas y se presenta la información de los pacientes presentes
    for (int i=0; i<N; ++i)
        if ((pacientes+i)->nombre != NULL)
            printf("[%d] %s %s\n", i, (pacientes+i)->nombre, (pacientes+i)->apellidos);
    
    printf("\n");
}

/* Se obtiene el total de camas actualmente disponibles en el hospital */
void numeroDeCamasDisponibes() {
    // Se cuenta el numero de camas con un valor nulo como camas disponibles
    int count = 0;
    for (int i=0; i<N; ++i)
        if ((pacientes+i)->nombre == NULL)
            count++;
    // Se imprime el valor encontrado
    printf("\nActualmente hay %d camas disponibles.\n\n", count);
}

/* Se obtiene el total de camas actualmente ocupadas en el hospital */
void numeroDeCamasOcupadas() {
    // Se cuenta el numero de camas con un valor distinto a nulo como camas ocupadas
    int count = 0;
    for (int i=0; i<N; ++i)
        if ((pacientes+i)->nombre != NULL)
            count++;
    // Se imprime el valor encontrado
    printf("\nActualmente hay %d camas ocupadas.\n\n", count);
}

/* Libera todos los elementos que conformana a la estructura "paciente" */
void liberarPaciente(paciente * paciente){
    free(paciente->nombre);
    free(paciente->apellidos);
    free(paciente->telefono);
}

/* Libera el arreglo de camas/pacientes y cada uno de los pacientes que se encuentran dentro */
void liberarMemoria(){
    for (int i=0; i<N; ++i)
        liberarPaciente(pacientes+i);

    free(pacientes);
}