#include<stdio.h>
#include<stdio.h>
#include<time.h>

int a[10000009];
void qsort_serial(int l,int r){
	if(r>l){
		int pivot=a[r],tmp;
		int less=l-1,more;
		for(more=l;more<=r;more++){
			if(a[more]<=pivot){
				less++;
				 tmp=a[less];
				a[less]=a[more];
				a[more]=tmp;
			}
		}
		qsort_serial(l,less-1);
		qsort_serial(less+1,r);
	}
}
int main(){
	int n,i;
	//scanf("%d",&n);
	n=10000000;
	int range=10000;
	srand(time(NULL));
	for( i=0;i<n;i++)
		a[i]=rand()%range;
	qsort_serial(0,n-1);
	return 0;
}
