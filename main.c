#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define E 5

typedef struct {
    char * nombre;
    char * apellidos;
    char * telefono;
    int edad;
} paciente;

int N = E; 
paciente * pacientes;

typedef void (* opcion)();

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
    pacientes = (paciente *) malloc(sizeof(paciente) * N);
    int opc = 0;

    opcion * opciones = (opcion *) malloc(6 * sizeof(opcion));

    *(opciones) = ingresarPaciente;
    *(opciones+1) = pacienteEnCama;
    *(opciones+2) = altaDePacienteEnCama;
    *(opciones+3) = listaDePacientes;
    *(opciones+4) = numeroDeCamasDisponibes;
    *(opciones+5) = numeroDeCamasOcupadas;
    
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
    
    liberarMemoria();

    return 0;
}

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

void pacienteEnCama() {
    int cama;
    printf("\nIngrese el numero de cama: ");
    scanf("%d", &cama);

    if (cama >= N) {
        printf("La cama %d aun no existe.\n\n", cama);
        return;
    }
    else if ((pacientes+cama)->nombre == NULL) {
        printf("La cama %d se encuentra desocupada.\n\n", cama);
        return;
    }

    printf("Paciente:\n");
    printf("\tNombre: %s %s\n", (pacientes+cama)->nombre, (pacientes+cama)->apellidos);
    printf("\tTelefono: %s\n", (pacientes+cama)->telefono);
    printf("\tEdad: %d\n\n", (pacientes+cama)->edad);
}

void altaDePacienteEnCama() {
    int cama;
    printf("\nIngrese el numero de cama: ");
    scanf("%d", &cama);

    if ((pacientes+cama)->nombre == NULL) {
        printf("La cama %d se encuentra desocupada.\n\n", cama);
        return;
    }

    printf("\nEl paciente %s %s ha sido dado de alta, la cama %d ahora se encuentra desocupada.\n\n", (pacientes+cama)->nombre, (pacientes+cama)->apellidos, cama);

    (pacientes+cama)->nombre = NULL;
    (pacientes+cama)->apellidos = NULL;
    (pacientes+cama)->telefono = NULL;
    (pacientes+cama)->edad = NULL;
}

void listaDePacientes() {
    printf("\nListado de pacientes:\n");

    for (int i=0; i<N; ++i)
        if ((pacientes+i)->nombre != NULL)
            printf("[%d] %s %s\n", i, (pacientes+i)->nombre, (pacientes+i)->apellidos);
    
    printf("\n");
}

void numeroDeCamasDisponibes() {
    int count = 0;
    for (int i=0; i<N; ++i)
        if ((pacientes+i)->nombre == NULL)
            count++;
    
    printf("\nActualmente hay %d camas disponibles.\n\n", count);
}

void numeroDeCamasOcupadas() {
    int count = 0;
    for (int i=0; i<N; ++i)
        if ((pacientes+i)->nombre != NULL)
            count++;
    
    printf("\nActualmente hay %d camas ocupadas.\n\n", count);
}

void liberarPaciente(paciente * paciente){
    free(paciente->nombre);
    free(paciente->apellidos);
    free(paciente->telefono);
}

void liberarMemoria(){
    for (int i=0; i<N; ++i)
        liberarPaciente(pacientes+i);

    free(pacientes);
}