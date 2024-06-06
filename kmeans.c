# include <stdio.h>
# include <stdlib.h>
#include <math.h>

struct cord
{
    double value;
    struct cord *next;
};
struct vector
{
    struct vector *next;
    struct cord *cords;
};

double  * vecToArr(struct vector *v1, int d);
int epsilonCheck(double ** oldArr, double ** newArr, int d, int k, double eps);
double **pointsToArr(int Pnum, int d, struct vector *headVec);
double **initKMeans(double **pointsArr, int k,int d);
double **kMeans(double  **pointsArr, double **KmeansArr , int d, int k, int Pnum);
void sumTwoArr(double * arr1, double * arr2, int d);
void findAvg(int *counter, double ** sumArr, int k, int d);
double euclidian_dist(double * arr1, double * arr2, int d);
void freeLinkedList(struct vector* head);
void deallocate2DArray(double** arr, int rows);
int isAllDigits(char *str);




int main(int argc, char **argv) {

    struct vector *head_vec, *curr_vec;
    struct cord *head_cord, *curr_cord;
    int i;
    int j;
    int t;
    double n;
    char c;
    float tempk;
    int k;
    int iter = 0;
    float tempiter;
    int flag = 0;
    int d = 0;
    int Pnum = 0;
    double **arr;
    double **oldArr;
    double **newArr;

    head_cord = malloc(sizeof(struct cord));
    if (head_cord==NULL){
        printf("An Error Has Occurred\n");
        return 0;
    }

    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = malloc(sizeof(struct vector));
    if (head_vec==NULL){
        printf("An Error Has Occurred\n");
        return 0;
    }
    curr_vec = head_vec;
    curr_vec->next = NULL;

    if ((argc>3) || (argc<2)){
        printf("An Error Has Occurred\n");
        return 0;
    }
    tempk = atof(argv[1]);
    k = atoi(argv[1]);
    
    if (argc == 3) {
        if(isAllDigits(argv[2])==1){
            iter = atoi(argv[2]);
            tempiter = atof(argv[2]);
        }
        else {
            printf("Invalid maximum iteration!\n");
            return 0;
        }
    }
    else{
        iter = 200;
        tempiter=200;
    }
    if (tempk - k == 0 && k > 1) {
        if (tempiter - iter == 0 && iter < 1000 && iter > 1) {


            while (scanf("%lf%c", &n, &c) == 2) {
                if (flag == 0) {
                    d++;
                }

                if (c == '\n') {
                    flag = 1;
                    Pnum++;
                    curr_cord->value = n;
                    curr_vec->cords = head_cord;
                    curr_vec->next = malloc(sizeof(struct vector));
                    if (head_vec->next==NULL){
                        printf("An Error Has Occurred\n");
                        return 0;
                    }
                    curr_vec = curr_vec->next;
                    curr_vec->cords = NULL;
                    curr_vec->next = NULL;
                    head_cord = malloc(sizeof(struct cord));
                    if (head_cord==NULL){
                        printf("An Error Has Occurred\n");
                        return 0;
                    }
                    curr_cord = head_cord;
                    curr_cord->next = NULL;
                    continue;
                }

                curr_cord->value = n;
                curr_cord->next = malloc(sizeof(struct cord));
                if (curr_cord->next==NULL){
                    printf("An Error Has Occurred\n");
                    return 0;
                }
                curr_cord = curr_cord->next;
                curr_cord->next = NULL;


            }
            if (k < Pnum) {
                arr = pointsToArr(Pnum, d, head_vec);
                if(arr == NULL){
                        printf("An Error Has Occurred\n");
                        return 0;    
                    }
                freeLinkedList(head_vec);
                free(head_cord);
                oldArr = initKMeans(arr, k,d);
                if(oldArr == NULL){
                        printf("An Error Has Occurred\n");
                        return 0;    
                    }

                newArr = kMeans(arr, oldArr, d, k, Pnum);
                if(newArr == NULL){
                        printf("An Error Has Occurred\n");
                        return 0;    
                    }
                t=0;
                while (t < iter && (epsilonCheck(oldArr, newArr, d, k, 0.001) == 1)) {
                    for (i = 0; i < k; i++) {
                        free(oldArr[i]); 
                    }
                    free(oldArr); 
                    oldArr = newArr;
                    newArr = kMeans(arr, oldArr, d, k, Pnum);
                    if(newArr == NULL){
                        printf("An Error Has Occurred\n");
                        return 0;    
                    }
                    t++;
                }
            

                for (i = 0; i < k; i++) {
                    for (j = 0; j < d; j++) {
                        printf("%.4f", newArr[i][j]);
                        if (j < d - 1) {
                            printf(",");
                        }

                    }
                    printf("\n");
                }
                for (i = 0; i < Pnum; i++) {
                free(arr[i]); 
                    }
                free(arr); 
                
                for (i = 0; i < k; i++) {
                free(oldArr[i]); 
                    }
                free(oldArr); 
                
                for (i = 0; i < k; i++) {
                free(newArr[i]); 
                    }
                free(newArr); 
        
                return 0;
            
            }
            
            else{
                printf("Invalid number of clusters!\n");
            }

        }
        else {
            printf("Invalid maximum iteration!\n");
        }
    }
    else {
        printf("Invalid number of clusters!\n");
        if  (tempiter - iter != 0 || iter >= 1000 || iter <= 1) {
            printf("\nInvalid maximum iteration!\n");
        }
    }
    return 0;
}


/*input : vector and num of cord. output : array of doubles in size d*/
double  * vecToArr(struct vector *v1, int d){
    int i;
    struct cord *curCord = v1->cords;
    double *arr = (double *)calloc(d,sizeof (double ));
    if (arr==NULL){
        printf("An Error Has Occurred\n");
        return NULL;
    }
    
    for(i=0 ; i<d; i++){
        arr[i] = curCord->value;
        curCord  = curCord->next;
    }
    return arr;
}

double **pointsToArr(int Pnum, int d, struct vector *headVec){
    int j;
    struct vector * curVec;
    double **PointsArr = (double **)malloc(Pnum*sizeof (double* ));
    if (PointsArr==NULL){
        printf("An Error Has Occurred\n");
        return NULL;
    }
    curVec = headVec;
    for(j=0;j<Pnum;j++){
        PointsArr[j] = vecToArr(curVec, d);
        if(PointsArr[j] == NULL){
            return NULL;
        }
        curVec = curVec->next;
    }
    return PointsArr;
}


double **initKMeans(double **pointsArr, int k,int d){
    int i;
    int j;
    double **kMeans = (double **)malloc(k*sizeof (double* ));
    if (kMeans==NULL){
        printf("An Error Has Occurred\n");
        return NULL;
    }
    for (i=0; i<k; i++){
        kMeans[i] = (double*)calloc(d,sizeof (double));
        if (kMeans[i]==NULL){
            printf("An Error Has Occurred\n");
            return NULL;
        }
        for(j = 0;j<d;j++){
        kMeans[i][j] = pointsArr[i][j];
        }
    }
    return kMeans;
}

void sumTwoArr(double * arr1, double *arr2, int d){
    int i;
    for(i=0; i<d; i++ ){
        arr1[i] += arr2[i];
    }

}

double **kMeans(double  **pointsArr, double **KmeansArr , int d, int k, int Pnum) {
    int *counter;
    double **sumArr;
    double temp;
    double minDist;
    int minIndex;
    int i;
    int j;
    int t;



    sumArr = (double **) calloc(k, sizeof(double * ));
    if (sumArr==NULL){
        printf("An Error Has Occurred\n");
        return NULL;
    }
    for(t=0; t<k; t++) {
        sumArr[t]= (double *) calloc(d, sizeof(double ));
        if (sumArr[t]==NULL){
            printf("An Error Has Occurred\n");
            return NULL;
        }
    }

    counter = (int *) calloc(k, sizeof(int ));
    if (counter==NULL){
        printf("An Error Has Occurred\n");
        return NULL;
    }

    for (i = 0; i < Pnum; i++) {

        minDist = euclidian_dist(pointsArr[i],KmeansArr[0], d);
        minIndex = 0;
        /*go over all the means and find the closest one*/
        for (j = 1; j < k; j++) {

            temp = euclidian_dist(pointsArr[i], KmeansArr[j], d);
            if (temp < minDist) {
                minIndex = j;
                minDist = temp;
            }
        }
        /*add the point to the sum of the closest mean*/
        sumTwoArr(sumArr[minIndex], pointsArr[i], d);
        /*add 1 to the counter of this mean*/
        counter[minIndex] += 1;


    }
    findAvg(counter, sumArr, k, d);
    free(counter);
    return sumArr;
}

double euclidian_dist(double * arr1, double * arr2, int d){
    double sum = 0;
    int i;
    for (i=0; i<d; i++ ){
        sum += pow((arr1[i] - arr2[i] ), 2);
    }

    return sqrt(sum);
}

void findAvg(int *counter, double ** sumArr, int k, int d){
    int i;
    int j;
    for(i=0; i<k; i++){
        if(counter[i] == 0){
            continue;
        }
        for(j=0; j<d; j++){
            sumArr[i][j] = sumArr[i][j] / counter[i];
        }
    }
}
int epsilonCheck(double ** oldArr, double ** newArr, int d, int k, double eps){
    int i;
    int r;
    for (r=0; r<k; r++){
        for(i=0;i<d;i++){
            if ((oldArr[r][i] - newArr[r][i])>= eps  || (oldArr[r][i] - newArr[r][i]) <= -eps ){
                return 1;
            }
        }
    }
    return 0;
}

void freeLinkedList(struct vector* head) {
    struct vector* outerCurrent = head;
    struct vector* outerNext;
    struct cord* currCord;
    struct cord* nextCord;


    while (outerCurrent != NULL) {
        currCord = outerCurrent->cords;

        while (currCord != NULL) {
            nextCord = currCord->next;
            free(currCord);
            currCord = nextCord;
        }

        outerNext = outerCurrent->next;
        free(outerCurrent);
        outerCurrent = outerNext;
    }
}

void deallocate2DArray(double** arr, int rows) {
    int i;
    if (arr == NULL) {
        return; 
    for (i = 0; i < rows; i++) {
        free(arr[i]); 
    }
    free(arr); 
    }
}


int isAllDigits(char* str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {

        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}