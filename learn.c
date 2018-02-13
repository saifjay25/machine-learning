#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double transpose(int rows, int columns, double **array, double **transarray) {
    int count;
    count=rows;                                 // to count down for the rows
    int count2;
    count2=columns;                                // to count down for the columns
    int a=0;
    int b=0;
    while(count>0){
        while(count2>0){
            transarray[a][b]=array[b][a];
            b++;                                // array2 col and array rows are incrementing
            count2--;
        }
        a++;                                    // array2 row and array col is incremented
        count--;
    }
    return **transarray;
}

double matrix_transposemult(int columns, int rows, double **transarray, double **array, double **matrix) {
    int counter = 0;   //col=10 for trans
    int counter2 = 0;  //row=4 for trans
    double sum = 0;     //cols=4 for array
    int transa = 0;
    int transb = 0;
    int b = 0;
    while(counter<columns){                     //plus one is added to so the last row will be filled
        while (counter2<columns) {              //plus one is added to so the last column will be filled
            while (b < rows) {                  //plus one is added to so the last numbers will be multiplied
                sum += transarray[transa][b] * array[b][transb];
                b++;
            }
            b=0;                                //restarts cols for transarray and rows for array
            matrix[counter][counter2] = sum;
            counter2++;                         //moves to next column in mult matrix
            transb++;                           //moves to next column for array so first->
        }                                       //row transarray multiplies with next col of array
        counter++;                              //moves to next row in mult matrix
        transa++;                               //moves to next row in transarray
        transb=0;                               //restarts array cols so it can be multiplied by array rows
        counter2=0;                             //restarts mult matrix cols so numbers can be inserted
    }
    return **matrix;
}

double matrix_transposemult2(int columns, int rows, double **transarray, double **array, double **matrix) { //matrix row=4 col=10
    int counter = 0;   //col=10 for trans
    int counter2 = 0;  //row=4 for trans
    double sum = 0;     //cols=4 for array
    int transa = 0;
    int transb = 0;
    int b = 0;
    while(counter<rows){                     //plus one is added to so the last row will be filled
        while (counter2<columns) {              //plus one is added to so the last column will be filled
            while (b < rows) {                  //plus one is added to so the last numbers will be multiplied
                sum += transarray[transa][b] * array[b][transb];
                b++;
            }
            b=0;                                //restarts cols for transarray and rows for array
            matrix[counter][counter2] = sum;
            counter2++;                         //moves to next column in mult matrix
            transb++;                           //moves to next column for array so first->
        }                                       //row transarray multiplies with next col of array
        counter++;                              //moves to next row in mult matrix
        transa++;                               //moves to next row in transarray
        transb=0;                               //restarts array cols so it can be multiplied by array rows
        counter2=0;                             //restarts mult matrix cols so numbers can be inserted
    }
    return **matrix;
}

double identity(int j,double **inverse){
    int counter=0;
    int row=0;
    int column=0;
    while (row<=j){
        while (column<=j){
            if (counter==row && counter==column) {  // if counter equals rows and cols then that coordinate equals 1
                inverse[row][column]=1;
                counter++;                          // counter increments because 1 moves diagonally in identity matrix
            }else{
                inverse[row][column]=0;             // everything equals 0
            }
            column++;
        }
        column=0;                                   // restart column
        row++;
    }
    return **inverse;
}

double row_divide(int j, double **matrix,int colholder, int rowholder, double num){ // divides the whole row
    for (colholder=0;colholder<j;colholder++){
        matrix[rowholder][colholder]=matrix[rowholder][colholder]/num;
    }
    return **matrix;
}

double row_subtraction(int j, double **matrix, int colholder, int rowholder,int rowsub){  // subtracts the row with pivot row
    for (colholder=0;colholder<j;colholder++){
        matrix[rowholder][colholder]=matrix[rowsub][colholder]-matrix[rowholder][colholder];
        colholder++;
    }
    return **matrix;
}

double reverse_rowsub(int j, double **matrix, int colholder, int rowsub, int column) {  // subtract the pivot row with rows above the pivot
    double num=0;
    int colreverse=column;
    int reverse = rowsub;               // goes through rows above pivot rows to make the values above the pivot value zero
    reverse--;
    while (reverse >= 0) {
        num=matrix[reverse][colreverse];// holds the number that is to be multiplied by the pivot row ans subtract with with rows above the pivot row
        if (num!=0) {
            while (colholder < j) {
                matrix[reverse][colholder] = (num * matrix[rowsub][colholder]) - matrix[reverse][colholder];
                colholder++;
            }
        }
        reverse--;
        colholder=0;
    }
    return **matrix;
}

double inverse_matrix(int columns, double **inverse, double **mult_matrix) {
    int rowsub = 0;                                       // pivot row that is supposed to subtract with all rows to make those rows zero
    double num = 0;
    int rowholder = 0;                                    // checks to see if there are zeros below the pivot value
    int colholder = 0;
    int counter = 0;
    int column = 0;                                       // this and rowsub are coordinates for each pivot row
    while (column<columns) {
        while (rowholder<columns) {
            if (counter == rowsub && counter == column) { // counter is to see where number 1 goes in matrix
                if (mult_matrix[rowsub][column] == 1) {
                    if(rowsub==columns-1){                                          // checks last pivot row and subtracts all rows above that
                        reverse_rowsub(columns, mult_matrix, colholder, rowsub, column);   // performs subtraction rows above pivot row
                        reverse_rowsub(columns, inverse, colholder, rowsub,column);
                        break;
                    }
                    rowholder++;                             // pivot value is 1 row modification is done so it goes to next row
                } else {                                     // if its not one then whole row is divided by first value
                    num = mult_matrix[rowsub][column];
                    row_divide(columns, mult_matrix, colholder, rowsub, num);
                    row_divide(columns, inverse, colholder, rowsub, num);  //divide identity matrix with num from mult matrix
                }
                if(rowsub==columns-1){                                          // checks last pivot row and subtracts all rows above that
                    reverse_rowsub(columns, mult_matrix, colholder, rowsub, column);   // performs subtraction rows above pivot row
                    reverse_rowsub(columns, inverse, colholder, rowsub,column);
                }
            } else {                                         //if it is not a pivot value then turn value equal to zero
                num = mult_matrix[rowholder][column];
                row_divide(columns, mult_matrix, colholder, rowholder, num);
                row_divide(columns, inverse, colholder, rowholder, num);
                if (rowholder >= 1) {
                    row_subtraction(columns, mult_matrix, colholder, rowholder, rowsub);   // subtract the rowholder with rowsub
                    row_subtraction(columns, inverse, colholder, rowholder, rowsub);       // same for identity matrix
                    if (rowholder == columns-1) {     // this executes after all the rows beneath the rowsub (pivot row) are all evaluated and zero
                        reverse_rowsub(columns, mult_matrix, colholder, rowsub, column);   // performs subtraction rows above pivot row
                        reverse_rowsub(columns, inverse, colholder, rowsub,column);
                    }
                }
            }
            rowholder++;
        }
        counter++;
        rowsub++;
        column++;
        rowholder = rowsub+1;
    }
    return **inverse;
}

void matrixmult(double *testmatrix,double *onecol, int columns){
    double sum=0;
    int holder=0;
    while(holder<columns){
        sum+=testmatrix[holder]+onecol[holder];
        holder++;
    }
    printf("%0.0f\n", sum);
}
double matrix(double **testmatrix, double *onecol, double *end,int columns, int rows){ //one big matrix with one col matrix
    int counter=0;
    float sum=0;
    int holder=0;
    int j=0;
    while(j<columns) {
        while (holder<rows) {
            sum += testmatrix[j][holder] + onecol[holder];
            holder++;
        }
        end[counter]=sum;
        counter++;
        j++;
    }
    return *end;
}

int main(int argc, char **argv) {
    FILE *training = fopen(argv[1], "r");
    FILE *test= fopen(argv[2],"r");
    int i = 0;                                    // count down for columns
    int j = 0;                                    // counter for rows
    int k = 0;                                    // counter for columns
    int attribute=0;
    int b = 0;
    int d=0;
    int columns = 0;
    int rows = 0;
    fscanf(training,"%d %d\n",&columns,&rows);
    double **transarray;                               // pointer to an array of pointers (int array[rows][columns])
    transarray = (double**)malloc(columns*sizeof(double *));        // distribute memory for enough rows int pointers
    for(b=0;b<columns;b++) {
        transarray[b] =(double*) malloc(rows * sizeof(double));
        b++;
    }
    double **arry;
    arry=(double **) malloc(rows*sizeof(double *));
    for (d=0;d<rows;d++){
        arry[d]=(double *) malloc(columns*sizeof(double));
        d++;
      
    }
    double *houseprices;
    houseprices=(double*) malloc(rows*sizeof(double));
    i = columns;
    double aa;
    char content[128];
    char *token;
    while (fgets(content, 128,training)!=NULL) {
       token=strtok(content,",");
        while(token!=NULL){
            aa = atof(token);
            if (i== 0) {
                houseprices[j] = aa;
                j++;
                if (j==rows){
                   break;
                } 
                i = columns;
                k = 0;
            } else {
                arry[j][k] = aa;
                k++;
                i--;
            }
           token = strtok(NULL, ",");
        }
    }
    transpose(rows, columns, arry, transarray);                                 // gets the transpose
    double **mult_transmatrix;
    mult_transmatrix = malloc(columns * sizeof(double *));
    for (b = 0; b <columns; b++) {
        mult_transmatrix = malloc(columns * sizeof(double));
    }
    matrix_transposemult(columns,rows,transarray, arry, mult_transmatrix);          // gets the multiplied matrix of original and transpose
    double **inverse;
    inverse = malloc(columns* sizeof(double *));
    for (b = 0; b<columns; b++) {
        inverse = malloc(columns * sizeof(double));
    }
    identity(columns, inverse);                                              // builds idenity matrix with just 1s on diagonal
    inverse_matrix(columns, inverse, mult_transmatrix);                      // performs inverse method
    double **bigmatrix;
    bigmatrix = malloc(columns*sizeof(double *));
    for (b = 0; b<columns; b++) {
        bigmatrix = malloc(rows * sizeof(double));
    }
    matrix_transposemult2(rows,columns, inverse, transarray, bigmatrix);              // mulitplies the inverse with the transpose
    double *onecol;
    onecol = (double*) malloc(columns*sizeof(double ));
    matrix(bigmatrix, houseprices, onecol,columns,rows);
    fscanf(test,"%d\n",&attribute);
    int done=columns;
    double *testmatrix;
    testmatrix = (double*) malloc(columns*sizeof(double));
    int col2=0;
    double bb;
    char con[128];
    char *toke;
    int hold=1;
    while (fgets(con, 128,test)!=NULL) {
        toke=strtok(content,",");
        while(toke!=NULL){
            bb = atof(token);
            if (done == 0) {
                col2=0;
                matrixmult(testmatrix, onecol, columns);
                hold++;
                if (hold==attribute){
                    break;
                }
            } else {
                testmatrix[col2] = bb;
                col2++;
                done--;
            }
            toke=strtok(NULL, ",");
        }
    }
    return 0;
}
