#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_DATA_POINTS 41

int main(int argc, char *argv[])
{
    char input_file[256], output_file[256];
    double p[MAX_DATA_POINTS], pc, percolation[MAX_DATA_POINTS];
    int i, n = 0;
    double sum_p = 0, sum_log_percolation = 0, sum_p2 = 0, sum_log_percolation_p = 0;

    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    strcpy(input_file, argv[1]);
    strcpy(output_file, argv[2]);

    FILE *fp = fopen(input_file, "r");
    if (!fp) {
        printf("Error opening input file %s\n", input_file);
        return 1;
    }

    // Read data from input file
    while (fscanf(fp, "%lf,%lf", &p[n], &percolation[n]) != EOF) {
        sum_p += p[n];
        sum_p2 += p[n] * p[n];
        sum_log_percolation += log(percolation[n]);
        sum_log_percolation_p += log(percolation[n]) * p[n];
        n++;
    }
    fclose(fp);

    if (n < 3) {
        printf("Error: Insufficient data. Need at least 3 data points.\n");
        return 1;
    }

    // Calculate critical exponents beta and nu
    pc = (sum_p * sum_log_percolation_p - sum_p2 * sum_log_percolation) /
         (sum_p * sum_p - n * sum_p2);
    double beta = (sum_log_percolation - pc * sum_p) / n;
    double nu = 1 / (2 * beta);

    // Write results to output file
    fp = fopen(output_file, "w");
    if (!fp) {
        printf("Error opening output file %s\n", output_file);
        return 1;
    }
    fprintf(fp, "beta,%lf\n", beta);
    fprintf(fp, "nu,%lf\n", nu);
    fclose(fp);

    printf("Calculation successful. Results written to %s.\n", output_file);

    return 0;
}
