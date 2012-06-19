#include<stdio.h>
#include<omp.h>
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
void qsort_parallel(int l,int r){
	if(r>l){
	//	printf("range(%d %d) is performed by thread %d\n",l,r,omp_get_thread_num());
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
		if((r-l)<1000){
			qsort_serial(l,less-1);
			qsort_serial(less+1,r);
		}
		else{
			#pragma omp task
			qsort_parallel(l,less-1);
			#pragma omp task
			qsort_parallel(less+1,r);
			#pragma omp taskwait
		}
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
//	printf("input array is ------------------------------------------------------------------------------------\n");
///	for(i=0;i<n;i++)
//		printf("%d ",a[i]);
//	printf("\n");
#pragma omp parallel	
	#pragma omp single
	qsort_parallel(0,n-1);
//	printf("output array is ------------------------------------------------------------------------------------\n");
//	for(i=0;i<n;i++)
//		printf("%d ",a[i]);
//	printf("\n");
	
	return 0;
}
