/*
 * suppress mac os only linker warnings clang: warning: overriding
 * deployment version from '16.0' to '26.0' [-Woverriding-deployment-version]
 *
 * gcc-14 ./Seda.c -o app -mmacosx-version-min='26.0' -DNUM_ES_PALABARAS=10
 *
 */

#include <stdio.h>
#include <time.h>

#ifdef __APPLE__
#include <mach/mach.h>
#elif __linux__
#include <sys/resource.h>
#elif _WIN32
#include <windows.h>
#include <psapi.h>
#endif

// memoria en las programas son virtaul y NO es el mismo de la memoria fisical
// en palabaras sencillas, memoria virtaul es en tu codigo y memoria fisical es en tu hardware
// y tambien hay translaciones de CPU y kernel por "fisical lookups

#define NUM_ES_PALABARAS 4
#define C_UNO "\n│                       ▐▛███▜▌"
#define C_DOS "│                      ▝▜█████▛▘"
#define C_TRS "│                        ▘▘ ▝▝"

void corre_corre_corre();
void statisticos();

void disfruta(int n, const char *w);
void arrays();
void poitnersss();
void tipos();
double get_memory_mb();

int main() {
    corre_corre_corre();
    return 0;
}

void corre_corre_corre() {
    clock_t start = clock();

    disfruta(1, "Matrizes");
    arrays();
    disfruta(2, "Agujas");
    poitnersss();
    disfruta(3, "Tipos");
    tipos();

    printf("\nMemory: %.2f MB", get_memory_mb());
    clock_t end = clock();
    printf("\nTiempo de programa: %.4f segundos", (double)(end - start) / CLOCKS_PER_SEC);
}

void disfruta(int n, const char *w) {
    puts(C_UNO);
    puts(C_DOS);
    puts(C_TRS);
    puts("────────────────────────────────────────");
    printf("%d %s\n", n, w);
    puts("────────────────────────────────────────");
}

void arrays() {
    // char *palabaras[NUM_ES_PALABARAS] = {"tejon", "zorillo", "imanes", "lechuza"};
    char *palabaras[NUM_ES_PALABARAS];
    memset(&palabaras, '\0', sizeof(palabaras));
    palabaras[0] = "tejon";
    palabaras[1] = "zorillo";
    palabaras[2] = "imanes";
    palabaras[3] = "lechuza";
    printf("Elemento cuatro: %s\n", palabaras[3]);
    printf("Elemento cuatro ptr: %c\n", *palabaras[3]);
}
struct pkmn {
    int numero;
    int generacion;
    char *tipo;
};
void poitnersss() {
    int beeg_data = 1000000;
    int *ptr = &beeg_data; // direccion de nuestro variable
    printf("deference el ptr para dar el value %d\n", *ptr);
    printf("justo el poitner %p\n", (void *)ptr);
}

void tipos() {
    struct pkmn Lapras;
    Lapras.numero     = 131;
    Lapras.generacion = 1;
    Lapras.tipo       = "Agua/Hielo";
    
    printf("Pokedex\n--\n%d\n%d\n%s\n", Lapras.numero, Lapras.generacion, Lapras.tipo);
    
    printf("Mira los tamanos de mis variables");
    char byte;
    short dos_bytes;
    int four_byte_en_32_bit_sistemas;
    long long int eight_bytes;
    
    int max_con_un_B = 2147483647;
    unsigned int max_u = 4294967295;
    
    float flotador = 3.14;
    double doble = 3.1459;
}

double get_memory_mb() {
    const float uno_mb = 1024.0;
    #ifdef __APPLE__
        struct mach_task_basic_info info;
        mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;
        task_info(mach_task_self(), MACH_TASK_BASIC_INFO, (task_info_t)&info, &count);
        return info.resident_size / (uno_mb * uno_mb);
    #elif __linux__
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        return usage.ru_maxrss / uno_mb;
    #elif _WIN32
        PROCESS_MEMORY_COUNTERS pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
        return pmc.WorkingSetSize / (uno_mb * uno_mb);
    #else
        return 0.0;
    #endif
}
