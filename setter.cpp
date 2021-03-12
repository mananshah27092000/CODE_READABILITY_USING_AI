double fun(double arr[] , int n ){
    
    double sum ;
    sum = 0 ;
    int i ;
    i = 0 ;

    for(;i<n;i++){
        sum = sum + arr[i];
    }

    sum = sum / n;
    return sum;
}