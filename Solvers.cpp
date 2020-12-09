#include "Files.hpp"
#include "Tools.hpp"
#include "Solvers.hpp"
#include <bits/stdc++.h>
#include <math.h>

void power_method_deflation(int n, double **matrix, double *eigenvalores, double ** eigenvectores, int max_iterations, int num_eigenvalues, double epsilon) {                        
    double *V_0   = create_vector_cero(n); // Old vector
    double *V_1   = create_vector_cero(n); // new vector
    double lambda = 0;                     // eigenvalue       
    int iter      = 0;                     // eigenvalue iter
    int eig_index = 0;                     // id of eigenvalue

    // Stops when we find all eigenpairs
    while (eig_index < num_eigenvalues) {
        // Initialization      
        lambda = 0;                                  
        iter   = 0;

        for (int i = 0; i < n; i++) V_0[i] = random(); // Random initialization
        normal_vector(n,V_0);                          // Normalize 
        
        // Cicle for a particular eigenpair
        while (iter < max_iterations){                    
            iter++;                                 
            
            contribuciones(n,eig_index,eigenvectores,V_0);
            normal_vector(n,V_0);
            product_mv(n,n,matrix,V_0,V_1);

            double num = 0;                           
            for (int i = 0; i < n; i++){
                num   += V_1[i]*V_0[i];
                V_0[i] = V_1[i];
            }

            if (fabs(lambda - num) < epsilon){
                /*
                printf("El método convergió en la iteración: %i\n", iter);
                printf("%d: El valor propio es: %lf\n",eig_index+1, lambda);
                */          
                // Normalize vector and save it
                normal_vector(n,V_1);
                for (int j = 0; j < n; j++) {
                    eigenvectores[eig_index][j] = V_1[j];
                }

                eigenvalores[eig_index] = lambda;   
                break;
            }
            else{
                lambda = num;
            }
        }
        // No convergence for at least one of eigenpairs
        if (iter >= max_iterations){
            cout << "El método no convergió para el intento: " << eig_index+1 << endl;
            break;
        }
        eig_index++;
    }
    
    
    /*
    char name[40];                           
    sprintf(name,"%s%s","Out/S_eigenval",".txt"); 
    write_vector(num_eigenvalues,eigenvalores,name);
    
    sprintf(name,"%s%s","Out/S_eigenvec",".txt"); 
    write_matrix(num_eigenvalues,n,eigenvectores,name);
    */
    
    free(V_0);
    free(V_1);
}