/*
 *	Name: [044] 简单归并排序
 *	Author: Mega Show
 *	Date: 2016.11.25 17:46
 */
#define METHOD 1

#include <stdio.h>

void MergeSort(int len, int a[], int index, int alen, int blen){
	if(alen >= 2)
		MergeSort(len, a, index, alen-alen/2, alen/2);
	if(blen >= 2)
		MergeSort(len, a, index + alen, blen-blen/2, blen/2);
	int i = index, j = index + alen, k = 0, temp[alen+blen];


	#if METHOD == 1
	/* method 1 */
	while((i < index + alen) || (j < index + alen + blen)){
		if(i >= index + alen || (j < index + alen + blen && a[i] > a[j]))
			temp[k++] = a[j++];
		else
			temp[k++] = a[i++];
	}

	#elif METHOD == 2
	/* method 2 */
	while((i < index + alen) && (j < index + alen + blen)){
		if(a[i] > a[j])
			temp[k++] = a[j++];
		else
			temp[k++] = a[i++];
	}
	while(i < index + alen)
		temp[k++] = a[i++];
	while(j < index + alen +blen)
		temp[k++] = a[j++];
	/* end method branch */
	#endif

	for(i = 0; i < k; i++)
		a[i+index] = temp[i];
	for(i = 0; i < len - 1; i++)
		printf("%d ", a[i]);
	printf("%d\n", a[len-1]);
	return;
}

int main(){
	int num;
	scanf("%d", &num);
	int var[num];
	for(int i = 0; i < num; i++)
		scanf("%d", &var[i]);
	if(num > 1)
		MergeSort(num, var, 0, num-num/2, num/2);
	return 0;
}