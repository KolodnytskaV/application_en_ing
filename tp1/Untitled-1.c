#include <stdio.h>
#include <stdlib.h>

double *gauss(double tab[][3], int n){
    double alpha;
    double *b = calloc(n, sizeof(double));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            b[i] += tab[i][j];
        }
    }

    double s;

    for(int i = 0; i <= n - 1; i++){
        for(int j = 0; j < n; j++){
            alpha = tab[j][i]/tab[i][i];
        }
    }  

}

void affiche(double *tab, int n){
    for(int i = 0; i < n; i++){
        printf("%d\n", tab[i]);
    }
}

int main(void){
    double A1[3][3] = {{3, 0, 4}, {7, 4, 2}, {-1, 1, 2}};
    double A2[3][3] = {{-3, 3, -6}, {-4, 7, 8}, {5, 7, -9}};
    double A3[3][3] = {{4, 1, 1}, {2, -9, 0}, {0, -8, 6}};
    double A4[3][3] = {{7, 6, 9}, {4, 5, -4}, {-7, -3, 8}};

    double *X1 = gauss(A1, 3);
    affiche(X1, 3);

    return 0; 
}