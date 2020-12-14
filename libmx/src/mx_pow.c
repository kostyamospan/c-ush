double mx_pow(double n, unsigned int pow) 
{
    double res = 1;
    unsigned int i = 0;
    
    if(pow)
        while(i++ != pow) 
            res*=n;
    
    return res;
}
