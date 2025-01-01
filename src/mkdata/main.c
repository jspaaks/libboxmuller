#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "boxmuller/boxmuller.h"
#include "matrix/matrix.h"

void print_usage (FILE *, char * []);
void populate_features (const Matrix * lower_bounds, const Matrix * upper_bounds, Matrix * features);
void populate_labels (const Matrix * true_weights, const Matrix * features, float sigma, Matrix * labels, Matrix * true_residuals);

int main (int argc, char * argv[]) {

    if (argc > 1) {
        print_usage(stdout, argv);
        bool a = strncmp(argv[1], "-h", 3) == 0;
        bool b = strncmp(argv[1], "--help", 7) == 0;
        if (a || b) {
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    }

    // ======================= COLLECT USER INPUT ========================= //

    const size_t nsamples = 7;
    constexpr size_t nfeatures = 2;
    const float sigma = 10.0f;
    const char basename[128] = "artificial-data.";

    // ======================= INITIALIZE ARRAYS ========================== //

    Matrix * features = matrix_create(nsamples, nfeatures);
    Matrix * labels = matrix_create(nsamples, 1);
    Matrix * lower_bounds = matrix_create(1, nfeatures);
    Matrix * true_residuals = matrix_create(nsamples, 1);
    Matrix * true_weights = matrix_create(1, 1 + nfeatures);
    Matrix * upper_bounds = matrix_create(1, nfeatures);

    lower_bounds->vals[0] = 0.01;
    lower_bounds->vals[1] = 100;

    upper_bounds->vals[0] = 0.02;
    upper_bounds->vals[1] = 200;

    true_weights->vals[0] = 98.7;
    true_weights->vals[1] = 65.4;
    true_weights->vals[2] = 32.1;

    // =================== INITIALIZE RANDOMIZATION ======================= //

    srand(time(nullptr));

    // ============================= DATA ================================= //

    populate_features(lower_bounds, upper_bounds, features);
    populate_labels(true_weights, features, sigma, labels, true_residuals);

    // ============================== IO ================================== //


    matrix_print(stdout, "true_weights", true_weights);
    matrix_print(stdout, "features", features);
    matrix_print(stdout, "labels", labels);
    matrix_print(stdout, "true_residuals", true_residuals);

    matrix_write(basename, "true_weights", true_weights);
    matrix_write(basename, "features", features);
    matrix_write(basename, "labels", labels);
    matrix_write(basename, "true_residuals", true_residuals);

    // =================== DEALLOCATE DYNAMIC MEMORY ====================== //

    matrix_destroy(&features);
    matrix_destroy(&labels);
    matrix_destroy(&lower_bounds);
    matrix_destroy(&true_residuals);
    matrix_destroy(&true_weights);
    matrix_destroy(&upper_bounds);

    return EXIT_SUCCESS;
}


void populate_features (const Matrix * lower_bounds, const Matrix * upper_bounds, Matrix * features) {
    assert(lower_bounds->nr == 1 && "Expected number of rows in lower bounds to be equal to 1");
    assert(upper_bounds->nr == 1 && "Expected number of rows in upper bounds to be equal to 1");
    assert(lower_bounds->nc == upper_bounds->nc && "Expected number of columns in lower bounds to be equal to number of columns in upper bounds");
    assert(features->nc == upper_bounds->nc && "Expected number of columns in features to be equal to number of columns in upper bounds");
    for ( size_t ic = 0; ic < lower_bounds->nc; ic++) {
        assert(lower_bounds->vals[ic] < upper_bounds->vals[ic] && "Expected lower bounds to be smaller than their corresponding upper bounds");
    }
    for (size_t ir = 0; ir < features->nr; ir++) {
        for (size_t ic = 0; ic < features->nc; ic++) {
            size_t i = ir * features->nc + ic;
            float range = upper_bounds->vals[ic] - lower_bounds->vals[ic];
            float u = (float) rand() / RAND_MAX;
            features->vals[i] = lower_bounds->vals[ic] + u * range;
        }
    }
}


void populate_labels (const Matrix * true_weights, const Matrix * features, float sigma, Matrix * labels, Matrix * true_residuals) {
    size_t nsamples = features->nr;
    size_t nfeatures = features->nc;
    for (size_t isample = 0; isample < nsamples; isample++) {
        true_residuals->vals[isample] = (float) (sigma * boxmuller_randn());
    }
    Matrix * features_prime = matrix_create(nsamples, 1 + nfeatures);
    Matrix * features_prime_transp = matrix_create(1 + nfeatures, nsamples);
    Matrix * labels_transp = matrix_create(1, nsamples);
    Matrix * ones = matrix_create(nsamples, 1);
    matrix_ones(ones);
    matrix_hstack(ones, features, features_prime);
    matrix_transp(features_prime, features_prime_transp);
    matrix_dotpro(true_weights, features_prime_transp, labels_transp);
    matrix_transp(labels_transp, labels);
    matrix_ebeadd(labels, true_residuals, labels);
    matrix_destroy(&features_prime_transp);
    matrix_destroy(&features_prime);
    matrix_destroy(&labels_transp);
    matrix_destroy(&ones);
}


void print_usage(FILE * stream, char * argv[]) {
    fprintf(stream,
            "Usage: %s\n", argv[0]);
}