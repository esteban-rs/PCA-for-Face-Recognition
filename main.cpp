#include <bits/stdc++.h>
#include <time.h>
#include "Files.hpp"
#include "Tools.hpp"
#include "Solvers.hpp"

int main(int argc, char const *argv[]){
    /* ----- P a r a m e t e r s ----- */
    // PGM IMAGES 
    int rows       = 112;
    int cols       = 92;
    int max_scale  = 255;
    set_ORL_info(rows, cols, max_scale);
    // DATA
    int star_index = 1;
    int end_index  = 40;
    int images_per_person = 8;
    int images_per_person_testing = 2;
    int K = PCA_Component();
    // Choose number of components in line 57 
    /* -------------- T R A I N I N G -------------- */
    int M = images_per_person*end_index;
    int N = rows*cols;

    clock_t start = clock();
    
    // 1. UPDATE DATA
    double **AT = create_matriz_cero(M, N);
    update_dataset(images_per_person, end_index, rows, cols, max_scale, AT);
    
    // 2. CALCULATE AVERAGE FACE

    double *average_face = calculate_average(M, N, AT);
    average_contribution(M, N, average_face, AT);
    write_average_face(rows, cols, max_scale, average_face);
    
    // 3. COMPUTE L = ATA
    double **A = create_matriz_cero(N, M);
    transpose_matrix(M, N, AT, A);

    double **L  = create_matriz_cero(M, M);
    matrix_multiplication(M, N, M, AT, A, L);
    freeMatrix(M, AT);

    // 4. GET EIGENPAIS
    double *eigenvalues   = create_vector_cero(M);
    double **eigenvectors = create_matriz_cero(M, M);
    power_method_deflation(M, L, eigenvalues, eigenvectors, 10000, M, 0.00001);

    // 5. PLOT EIGEN GRAPH
    /*
    string name = "Out/eigengraph.txt";
    write_eigengraph(M, eigenvalues, name);
    char name1[20] = "Out/eigengraph.txt";
    eigenplot_gnu(name1);
    */
    
    freeMatrix(M, L);
    free(eigenvalues);

    // 6. CHOOSE NUMBER OF COMPONENTS
    //int K = 5;
    
    double **ET = create_matriz_cero(K, N);
    get_eigenface_matrix(N, M, A, eigenvectors, K, ET);
    //change_interval(K, rows*cols, ET);
    //write_eigenfaces(K, rows, cols, max_scale, ET);
    

    freeMatrix(M, eigenvectors);

    // Proyect A into eigenface space, save it in Y
    double **Y = create_matriz_cero(K, M);
    matrix_multiplication(K, N, M, ET, A, Y);

    freeMatrix(N, A);

    // 7. SET THETA FOR A DISTANCE
    /*
    double theta = 0.8 * get_max_distance(K,M,Y);
    cout << theta << endl;
    */

    /* --------------- T E S T I N G --------------- */
    // 1. SET LABEL FROM TRAINING SET

    int *A_index = set_training_index(images_per_person,end_index,M);

    // 2. CHOOSE IMAGES FOR TESTING 
    int end  = images_per_person + images_per_person_testing;

    // allocation for new image
    double *image = create_vector_cero(N);
    double *w     = create_vector_cero(K);

    // Variables for accuaracy
    int conter = 0;
    int total  = 0;

    // Star testing
    double d       = 0;
    double min     = 0;
    int index_test = 0;
    
    for (int h = images_per_person; h < end; h++) {
        for (int m = 0; m < end_index; m++) {
            total++;
            update_PGMTest(h, m, rows, cols, max_scale, image);
            //write_Individual_PGM(h, m,rows, cols, max_scale, image);

            // center image
            for (int i = 0; i < rows*cols; i++) {
                image[i] = image[i] - average_face[i];
            }

            // Project to eigenspace
            product_mv(K, rows*cols,ET, image, w);
            // check distances with Y
            d          = 0;
            min        = 10000;
            index_test = 0;

            for (int j = 0; j < M; j++) {
                for (int i = 0; i < K; i++) {
                    d += (Y[i][j] - w[i])*(Y[i][j] - w[i]);
                }
                d = sqrt(d);

                // Update minimun distance
                if (d < min) {
                    min = d;
                    index_test = j;
                }
            }

            // See results
            // cout << m+1 << " " << A_index[index_test] << endl;
            if (m+1 == A_index[index_test]) {
                conter++;
            }
        }
    }

    clock_t end_t = clock();
    double cpu_time_used = ((double)(end_t - start))/CLOCKS_PER_SEC; 
    double acurracy = (double) conter/total;

    cout << "Accuracy       : " << acurracy << endl;
    cout << "Execution Time : " << cpu_time_used << " seconds." << endl; 


    free(image);
    free(w);
    free(A_index);
    
    freeMatrix(K, Y);
    freeMatrix(K, ET);
    free(average_face);
    return 0;
}
