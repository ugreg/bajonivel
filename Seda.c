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

void statisticos();
void arrays();
double get_memory_mb();

int main() {
    clock_t start = clock();

    char *nombre = "goyin";
    printf("Que royooo, me llamo %s, que paso chices.\n", nombre);
    arrays();
    
    printf("\nMemory: %.2f MB", get_memory_mb());
    clock_t end = clock();
    printf("\nTiempo de programa: %.4f segundos", (double)(end - start) / CLOCKS_PER_SEC);
}

void arrays() {
    // char *palabaras[NUM_ES_PALABARAS] = {"tejon", "zorillo", "imanes", "lechuza"};
    char *palabaras[NUM_ES_PALABARAS];
    memset(&palabaras, '\0', sizeof(palabaras));
    palabaras[0] = "tejon";
    palabaras[1] = "zorillo";
    palabaras[2] = "imanes";
    palabaras[3] = "lechuza";
    printf("%s\n", palabaras[3]);
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
