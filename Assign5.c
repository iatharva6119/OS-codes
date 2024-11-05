#include<stdio.h>
#include<stdlib.h>

int max[10][10], allocation[10][10], need[10][10];
int avail[10];
int np, nr;

void readmatrix(int matrix[10][10]){
    int i, j;
    for(i = 0; i < np; i++){
        for(j = 0; j < nr; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
}

void display_matrix(int matrix[10][10]){
    int i, j;
    for(i = 0; i < np; i++){
        for(j = 0; j < nr; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void calculate_need(){
    int i, j;
    for(i = 0; i < np; i++){
        for(j = 0; j < nr; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void banker(){
    int i, j, k = 0, flag;
    int finish[10] = {0}, safe_seq[10] = {0};

    for(i = 0; i < np; i++){
        finish[i] = 0;
    }

    while (k < np) {
        flag = 0;

        for(i = 0; i < np; i++){
            if(finish[i] == 0){
                int can_proceed = 1;
                for(j = 0; j < nr; j++){
                    if(need[i][j] > avail[j]){
                        can_proceed = 0;
                        break;
                    }
                }

                if(can_proceed){
                    finish[i] = 1;
                    safe_seq[k++] = i;
                    for(j = 0; j < nr; j++){
                        avail[j] += allocation[i][j];
                    }
                    flag = 1;
                }
            }
        }

        if(flag == 0) {
            printf("\n The system is in deadlock\n");
            return;
        }
    }

    printf("\n The process is in a safe state\n");
    for(i = 0; i < np; i++){
        printf("\n Process %d has finished", safe_seq[i]);
    }
}

int main(){
    int j;
    printf("\n Enter the number of processes: ");
    scanf("%d", &np);
    printf("\n Enter the number of resources: ");
    scanf("%d", &nr);
    printf("\n Enter the allocation matrix:\n");
    readmatrix(allocation);
    printf("\n Enter the max matrix:\n");
    readmatrix(max);
    printf("\n Enter the available resources:\n");
    for(j = 0; j < nr; j++){
        scanf("%d", &avail[j]);
    }

    printf("\n********* Entered Data *************\n\n");
    printf("\n Allocation Matrix:\n");
    display_matrix(allocation);
    printf("\n Max Matrix:\n");
    display_matrix(max);
    printf("\n Available Resources:\n");
    for(j = 0; j < nr; j++){
        printf("%d ", avail[j]);
    }

    calculate_need();
    printf("\n\n Need Matrix:\n");
    display_matrix(need);
    banker();
    printf("\n\n");

    return 0;
}