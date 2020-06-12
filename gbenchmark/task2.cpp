#include <benchmark/benchmark.h>
#include <bits/stdc++.h>
#define ll long long

void rec_merge_sort(int *a, ll beg, ll end){
    if(beg == end) return;
    ll mid = (beg + end)/2;
    rec_merge_sort(a,beg,mid);
    rec_merge_sort(a,mid+1,end);
    int f[mid-beg+2], s[end-mid+1];
    for(ll i=beg; i<=mid; i++){
        f[i-beg] = a[i];
    }
    f[mid-beg+1] = INT_MAX;
    for(ll i=mid+1; i<=end; i++){
        s[i-mid-1] = a[i];
    }
    s[end-mid] = INT_MAX;
    ll x=0,y=0;
    for(int i=beg; i<=end; i++){
        f[x]<s[y] ? a[i] = f[x++] : a[i] = s[y++];
    }
}

/*void merge_sort(int *a, ll beg, ll end){
    std::stack<ll> b,e;
    b.push(beg); e.push(end);
    while(!b.empty()){
        while(beg<end){
            
        }
    }
}*/

static void IntAddition(benchmark::State& state){
    int a = 90912;
    int b = 219545;
    for(auto _ : state)
        a+b;
}

BENCHMARK(IntAddition);

static void StdSort(benchmark::State& state){
    ll n=101001000;
    int *arr = (int *)malloc(n*sizeof(int));
    for(ll i=0; i<n; i++){
        srand(time(0));
        arr[i] = rand();
    }
    for(auto _ : state){
        std::sort(arr, arr+n);
    }
    free(arr);
}

BENCHMARK(StdSort);

static void RecMergeSort(benchmark::State& state){
    ll n=1001000;
    int *arr = (int *)malloc(n*sizeof(int));
    for(ll i=0; i<n; i++){
        srand(time(0));
        arr[i] = rand();
    }
    for(auto _ : state){
        rec_merge_sort(arr,0,n-1);
    }
    free(arr);
}

BENCHMARK(RecMergeSort);

/*static void MergeSort(benchmark::State& state){
    ll n=1001000;
    int *arr = (int *)malloc(n*sizeof(int));
    for(ll i=0; i<n; i++){
        srand(time(0));
        arr[i] = rand();
    }
    for(auto _ : state){
        merge_sort(arr,0,n-1);
    }
}*/

BENCHMARK_MAIN();