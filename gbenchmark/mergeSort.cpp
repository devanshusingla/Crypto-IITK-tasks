#include <bits/stdc++.h>

using namespace std;

void rec_merge_sort(int *a, int beg, int end){
    if(beg == end) return;
    int mid = (beg + end)/2;
    rec_merge_sort(a,beg,mid);
    rec_merge_sort(a,mid+1,end);
    int f[mid-beg+2], s[end-mid+1];
    for(int i=beg; i<=mid; i++){
        f[i-beg] = a[i];
    }
    f[mid-beg+1] = INT_MAX;
    for(int i=mid+1; i<=end; i++){
        s[i-mid-1] = a[i];
    }
    s[end-mid] = INT_MAX;
    int x=0,y=0;
    for(int i=beg; i<=end; i++){
        f[x]<s[y] ? a[i] = f[x++] : a[i] = s[y++];
    }
}

int main(){
    int n=36;
    int arr[n] = {1232,1243,456,2458,9534,9340,12456,9756,2,13,1234,3546,9564,134,45,2134,943,352,7956,324,8,967,234,567,987,3245,457,9876,3245,768,4325,1243,0,324,12323};
    rec_merge_sort(arr,0,n-1);
        for(auto i=0; i<n; i++){
            cout<<arr[i]<<endl;
        }
}