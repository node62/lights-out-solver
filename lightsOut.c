// lightsOut
#include<stdio.h>
#include<stdlib.h>

void show(int row, int col, int* arr[row]){
    printf("\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(arr[i][j]==-1) arr[i][j]=1;
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void rowswap(int row, int col, int* arr[row], int row1, int row2){
    int temp;
    for(int i=0;i<col;i++){
        temp=arr[row1][i];
        arr[row1][i]=arr[row2][i];
        arr[row2][i]=temp;
    }
}

void rowdef(int row, int col, int* arr[row], int scalar, int row1, int row2){
    for(int i=0;i<col;i++){
        arr[row2][i] = (arr[row1][i]*scalar + arr[row2][i]) % 2;
    }
}

void echelon(int row, int col, int* arr[row]){
    for(int lead=0;lead<row-1; lead++){
        if(arr[lead][lead]!=0){
            for(int i=lead+1;i<row;i++){
                rowdef(row, col, arr, arr[i][lead], lead, i);
            }
        }
        else{
            for(int i=row-1;i>lead;i--){
                if(arr[i][lead]==0) continue;
                else{
                    rowswap(row, col, arr, lead, i);
                    lead--;
                    break;
                }
            }
        }
    }
}

// int rank(int row, int col, int* arr[row]){
//     int rank=0;
//     for(int i=row-1;i>=0;i--){
//         for(int j=0;j<col;j++){
//             if(arr[i][j]!=0){
//                 rank++;
//                 break;
//             }
//     }}
//     return rank;
// }

int arithmetic(int row, int col, int* arr[row], int a){
    int temp=0;
    for(int i=0;i<col;i++){
        if(arr[a][i]==1)
            temp++;
    }
    temp++;
    temp%=2;
return temp;
}

void colMul(int row, int col, int* arr[row], int scalar, int colx){
    for(int i=0;i<row;i++)
        arr[i][colx]*=scalar;
}

void solve(int row, int col, int* arr[row], int var[]){
    int num=row-1;
    for(int i=row-1;i>=0;i--){
    if(arr[i][i]==0){ 
        --num;
        colMul(row, col, arr, 0, i);
        continue;
        }
    else{
        var[num--]=arithmetic(row, col, arr, i);
    if(var[num+1]==0)
        colMul(row, col, arr, 0, i);
    }
    }
}
  
int* specialVectors(int row, int col, int ri, int ci){
    int rxc=row*col;
    int* temp=malloc(rxc*sizeof(int));

    for(int i=0;i<(row*col);i++){
        temp[i]=0;
    }
    temp[ri*col+ci]=1;

    if(ri*col+ci+1<ri*col+col)
        temp[ri*col+ci+1]=1;

    if(ri*col+ci-1>=ri*col)
        temp[ri*col+ci-1]=1;

    if(ri*col+col+ci<rxc)
        temp[ri*col+col+ci]=1;
        
    if(ri*col+ci-col>=0)
        temp[ri*col+ci-col]=1;

return temp;
}

int main(){
    int row, col;
    printf("Enter no of rows and columns:"); scanf("%d %d", &row, &col);
    int arr[row][col];
    int rxc=row*col;
    printf("\nEnter the Lights matrix \n(Lights OFF= 0    Lights ON= 1):\n ");

    //formatting and taking input
    for(int i=0;i<col;i++) printf(" %c", 'A'+i);
    for(int i=0;i<row;i++){
        printf("\n%d|",i+1);
        for(int j=0;j<col;j++){
            scanf("%d", &arr[i][j]);
        }
    }

    //making of special vectors and mapping them to total matrix
    int* totalMatrix[rxc];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            totalMatrix[i*col+j]= specialVectors(row, col, i, j); 
        }
    }

// show(rxc, rxc, totalMatrix);


    //multiple equation solver
    int *tempArray[rxc];

    for(int i = 0; i < rxc; i++)
        tempArray[i] = malloc((rxc+1) * sizeof(int));

    for(int i=0; i<rxc;i++){
        for(int j=0;j<rxc+1;j++){
            if(j==rxc){
                tempArray[i][j]=arr[i/col][i%col];
            }
            else tempArray[i][j]=totalMatrix[i][j];
        }
    }

    //echelon form
        echelon(rxc, rxc+1, tempArray);



    int var[rxc];
    for(int i=0;i<rxc;i++)
        var[i]=0;
    int key=0;

    solve(rxc, rxc+1, tempArray, var);

// show(rxc, rxc+1, tempArray);

    for(int i=0;i<rxc;i++){
        var[i]%=2;
        if(var[i]==-1)
            var[i]=1;
    }
    
    for(int i=0;i<rxc;i++){
    if(var[i]==1){
        key=1;
        break;
    }
    }

    if(key==0){
        printf("\nNo soln exists :/");
        return 0;
    }

    printf("\nA soln exists , press the following: \n");
    for(int i=0;i<rxc;i++){
        if(var[i]==1)
            printf("%c%d ", 'A'+(i%col), (i/col)+1);
    }

return 0;
}
