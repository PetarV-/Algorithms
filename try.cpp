#include <stdio.h>
double slope[701];
void qsort(int levi,int desni)
{
    if (levi < desni)
    {
        int i=levi;
        int j=desni;
        double tmp;
        double piv1=slope[(levi+desni)/2];
        while (i<=j)
        {
            while (slope[i]<piv1) i++;
            while (slope[j]>piv1) j--;
            if (i<=j)
            {
                tmp=slope[i];
                slope[i]=slope[j];
                slope[j]=tmp;
                i++;
                j--;
            }
        }
        qsort(levi,j);
        qsort(i,desni);
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    int x[701],y[701];
    for (int i=0;i<n;i++)
    {
        scanf("%d %d",&x[i],&y[i]);
    }
    int k=0;
    int count;
    int maxc=-1;
    for (int i=0;i<n-1;i++)
    {
        for (int j=i+1;j<n;j++)
        {
            if (y[j]==y[i]) slope[k]=999.999;
            else slope[k]=(x[j]*1.0-x[i]*1.0)/(y[j]*1.0-y[i]*1.0);
            k++;
        }
        qsort(0,k-1);
        count=2;
        for (int s=1;s<k;s++)
        {
            if (slope[s]==slope[s-1]) count++;
            else count=2;
            if (count>maxc) maxc=count;
        }
        if (count>maxc) maxc=count;
        k=0;
    }
    printf("%d",maxc);
    return 0;
}
