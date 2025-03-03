#include <stdio.h>

void subsetSum(int set[],int subset[],int n,int subsetSize,int total,int nodeCount,int target) {
    if (total == target) {
        printf("Subset found: ");
        for (int i=0;i<subsetSize;i++) {
            printf("%d ",subset[i]);
        }
        printf("\n");
        return;
    }
    else if(nodeCount==n) {
        return;
    }
    else if(total+set[nodeCount]<=target) {
        subset[subsetSize]=set[nodeCount];
        subsetSum(set,subset,n,subsetSize+1,total+set[nodeCount],nodeCount+1,target);
        subsetSum(set,subset,n,subsetSize,total,nodeCount+1,target);
    }
    return;
}

int main() {
    int set[]={2,3,1,5,1,6};
    int n=sizeof(set)/sizeof(set[0]);
    int subset[n];
    int target=6;
    subsetSum(set,subset,n,0,0,0,target);
    return 0;
}