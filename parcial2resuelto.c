#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    int direccionesVirtuales[20];
    int paginas[20];
    int desplazamientos[20];
    int *p = malloc(sizeof(paginas));
    while(1) {
        char input[5];
        int dirVirtual;
        printf("Ingrese direccion virtual: ");
        scanf("%s", input);
        if (strcmp(input, "s") == 0) {
            printf("Good bye!\n");
            break;
        }
        else {
            dirVirtual = atoi(input);
            int desp = dirVirtual % 4096;
            int pagina = (dirVirtual - desp) / 4096;
            printf("Numero de pagina: %d\n", pagina);
            printf("Desplazamiento: %d\n\n", desp);
        }
    }
    return 0;
}