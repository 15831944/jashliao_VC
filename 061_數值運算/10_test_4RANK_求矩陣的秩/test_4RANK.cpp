  #include <stdio.h>
  #include <math.h>
/*
�DM*N�x�}A����(RANK)
*/
  int rank(double *a,int m,int n)
  //int m,n;
  //double a[];
  { int i,j,k,nn,is,js,l,ll,u,v;
    double q,d;
    nn=m;
    if (m>=n) nn=n;
    k=0;
    for (l=0; l<=nn-1; l++)
      { q=0.0;
        for (i=l; i<=m-1; i++)
        for (j=l; j<=n-1; j++)
          { ll=i*n+j; d=fabs(a[ll]);
	    if (d>q) { q=d; is=i; js=j;}
          }
        if (q+1.0==1.0) return(k);
        k=k+1;
        if (is!=l)
          { for (j=l; j<=n-1; j++)
              { u=l*n+j; v=is*n+j;
                d=a[u]; a[u]=a[v]; a[v]=d;
              }
          }
        if (js!=l)
          { for (i=l; i<=m-1; i++)
              { u=i*n+js; v=i*n+l;
                d=a[u]; a[u]=a[v]; a[v]=d;
              }
          }
        ll=l*n+l;
        for (i=l+1; i<=n-1; i++)
          { d=a[i*n+l]/a[ll];
            for (j=l+1; j<=n-1; j++)
              { u=i*n+j;
                a[u]=a[u]-d*a[l*n+j];
              }
          }
      }
    return(k);
  }
  main()
  { static double a[5][4]={ {1.0,2.0,3.0,4.0},
                            {5.0,6.0,7.0,8.0},
                            {9.0,10.0,11.0,12.0},
                            {13.0,14.0,15.0,16.0},
                            {17.0,18.0,19.0,20.0}};
    double *pa;
	pa=(double *)a;
    printf("\n");
    printf("RANK=%d\n",rank(pa,5,4));
    printf("\n");
  }

