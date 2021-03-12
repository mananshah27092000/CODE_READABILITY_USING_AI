// code has passed all test cases then cheking its logic readability
double fun(double arr[] , int n ){
    
    int sum ;
    sum = 0 ;
    int i ;
    i = 0 ;

    for(;i<n;i++){
        sum = sum + arr[i];
    }

    double average ;
    average = sum / n;
    return average;
}