// code has passed all test cases then cheking its logic readability
double fun(double arr[] , int n ){
    double array[n] ;
    int range ;
    int sum ;
    range = n ;
    int i ; 
    sum = 0 ;
    i = 0 ;
    for(;i<n;i++){
        array[i] = arr[i] ;
    }

    i = 0 ;
    for(;i<n;i++){
        sum = sum + array[i];
    }

    double average ;
    average = sum / range;
    return average;
}