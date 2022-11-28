#include <stdio.h>
#include <string.h>
#include <stdlib.h>
# include<time.h>
#define N 5

int main(void) {
    clock_t start, end;
    double execution_time;
    int direccionesVirtuales[N];
    int paginas[N];
    int desplazamientos[N];
    int *dV = malloc(sizeof(direccionesVirtuales));
    int *p = malloc(sizeof(paginas));
    int *desp = malloc(sizeof(desplazamientos));
    int TLBSize = 0;
    while(1) {
        char input[20];
        printf("Ingrese direccion virtual: ");
        scanf("%s", input);
        start = clock();
        if (strcmp(input, "s") == 0) {
            printf("Good bye!\n");
            free(dV);
            free(p);
            free(desp);
            break;
        }
        else {
            int dirVirtual = atoi(input);
            int desp = 0, pagina = 0, index;
            int TLBState = 0; // 0 para MISS, 1 para HIT
            for (index = 0; index<N; index++) {
                if (direccionesVirtuales[index] == dirVirtual) {
                    desp = desplazamientos[index];
                    pagina = paginas[index];
                    TLBState = 1;
                    break;
                }
            }
            if (desp == 0 && pagina == 0) {
                desp = dirVirtual % 4096;
                pagina = (dirVirtual - desp) / 4096;
                // Se usa la política FIFO para el reemplazo
                if (TLBSize == N) {
                    for (index = 0; index < N-1; index++) {
                        direccionesVirtuales[index] = direccionesVirtuales[index + 1];
                        paginas[index] = paginas[index + 1];
                        desplazamientos[index] = desplazamientos[index + 1];
                    }
                    direccionesVirtuales[N-1] = dirVirtual;
                    paginas[N-1] = pagina;
                    desplazamientos[N-1] = desp;
                }
                else {
                    direccionesVirtuales[TLBSize] = dirVirtual;
                    paginas[TLBSize] = pagina;
                    desplazamientos[TLBSize] = desp;
                    TLBSize = TLBSize + 1;
                }
            }
            end = clock();
            execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
            if (TLBState == 0) {
                printf("Numero de pagina: %d\n", pagina);
                printf("Desplazamiento: %d\n", desp);
                printf("Tiempo de traducción: %f segundos\n", execution_time);
                printf("TLB: Miss\n\n");
            }
            else if (TLBState == 1) {
                printf("Numero de pagina: %d\n", pagina);
                printf("Desplazamiento: %d\n", desp);
                printf("Tiempo de traducción: %f segundos\n", execution_time);
                printf("TLB: Hit\n\n");
            }
        }
    }
    return 0;
}
