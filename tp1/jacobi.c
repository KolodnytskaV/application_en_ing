#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ESPILON 1e-10
#define MAX_ITER 10000


//creer la matrice A5
void creer_A5(double **A, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j){
                A[i][j] = 1; 
            }
            else if(i == 0){
                A[i][j] = pow(2, -j);  //pour la puissance de 2
            }
            else if(j == 0){
                A[i][j] = pow(2, -i);  //pour la puissance de 2
            }
            else {
                A[i][j] = 0; 
            }
        }
    }
}

//creer la matrice A6
void creer_A6(double **A, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j){
                A[i][j] = 3;
            }
            else if(j == i + 1 && i < n - 1){
                A[i][j] = -1; 

            }
            else if(j == i - 1 && i > 0){
                A[i][j] = -2;
            }
            else{
                A[i][j] = 0;
            }
        }
    }
}

//faut calculer le b (Ax = b)
//x est exacte x_exact = (1, ... , 1)
void calculer_b(double **A, double *b, int n){
    for(int i = 0; i < n; i++){
        b[i] = 0;
        for(int j = 0; j < n; j++){
            b[i] += A[i][j]; //on calcule la somme des éléments de la ligne i
        }
    }
}

//on calcule l'erreur relative
double erreur_relative(double *x, int n){
    double erreur = 0;
    double diff;

    for(int i = 0; i < n; i++){
        diff = fabs(1.0 - x[i]);

        if(diff > erreur) {
            erreur = diff; 
        }
    }
    return erreur; 
}

//methode de jacobi
int jacobi(double **A, double *b, double *x, int n, double epsilon, int maxIter, double *erreur){
    double *x_new;
    double somme; 
    int iteration;

    x_new = malloc(n * sizeof(double));

    if(x_new == NULL){
        return -1; //erreur memoire
    }
    
    for(int i = 0; i < n; i++){ //solution initiale
        x[i] = 0;
    }

    for (iteration = 1; iteration <= maxIter; iteration++){
        for(int i = 0; i < n; i++){
            somme = 0; 
            
            for (int j = 0; j < n; j++){
                if(j != i) {
                    somme += A[i][j] * x[j];
                }
            }

            x_new[i] = (b[i] - somme) / A[i][i];
        }

        //copier x_new dans x
        for(int i = 0; i < n; i++){
            x[i] = x_new[i]; 
        }

        //calcul de l'erreur
        *erreur = erreur_relative(x, n);

        if(*erreur < epsilon){
            break;
        }
    }

    free(x_new);

    return iteration;
}


//Méthode de Gauss-Seidel
int gaussSeidel(double **A, double *b, double *x, int n, double epsilon, int maxIter, double *erreur){
    double somme;
    int iteration;

    //solution initial
    for(int i = 0; i < n; i++){
        x[i] = 0;
    }
    
    for(iteration = 1; iteration <= maxIter; iteration++){
        for(int i = 0; i < n; i++){
            somme = 0;
            for(int j = 0; j < n; j++){
                if(j != i){
                    somme += A[i][j] * x[j];
                }
            }

            x[i] = (b[i] - somme) / A[i][i];
        }

        //calcul de l'erreur
        *erreur = erreur_relative(x, n);

        if(*erreur < epsilon){
            break;
        }
    }

    return iteration;
}

int main(){
    int tailles[] = {3, 6, 8, 10};
    int nombreTailles = 4; 
    
    double **A;
    double *b;
    double *xJ;
    double *xGS;

    double erreurJ;
    double erreurGS;

    int iterJ;
    int iterGS;

    for (int k = 0; k < nombreTailles; k++) {

        int n = tailles[k];

        // Allocation de la matrice
        A = malloc(n * sizeof(double *));

        for (int i = 0; i < n; i++) {
            A[i] = malloc(n * sizeof(double));
        }

        //Allocation des vecteurs 
        b = malloc(n * sizeof(double));
        xJ = malloc(n * sizeof(double));
        xGS = malloc(n * sizeof(double));

        creer_A5(A, n);
        calculer_b(A, b, n);
        iterJ = jacobi(A, b, xJ, n, ESPILON, MAX_ITER, &erreurJ);
        iterGS = gaussSeidel(A, b, xGS, n, ESPILON, MAX_ITER, &erreurGS);

        printf("A5 - n = %d\n", n);
        printf("Jacobi       : iterations = %d, erreur = %.12e\n", iterJ, erreurJ);
        printf("Gauss-Seidel : iterations = %d, erreur = %.12e\n", iterGS, erreurGS);

        for (int i = 0; i < n; i++) {
            free(A[i]);
        }

        free(A);
        free(b);
        free(xJ);
        free(xGS);
    }

    return 0; 
}