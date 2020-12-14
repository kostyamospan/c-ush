int mx_sqrt(int x)
{
    if(x <= 0) return 0;

    int i = 1;
    for(i = 1; i*i < x;i++){}
	
    if(i*i != x) return 0;
    
    return i;
}
