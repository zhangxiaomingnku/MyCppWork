#include <iostream>
using namespace std;

template <typename T> void Merge( T* arr, int low, int mid, int high )
{
    int i, j, k;
    i = low;
    j = mid + 1;
    k = 0;
    T* tmp = new T[high - low + 1];

    while( i <= mid && j <= high )
    {
        if ( *(arr + i) <= *(arr + j) )
            *(tmp + k++) = *(arr + i++);
        else
            *(tmp + k++) = *(arr + j++);
    }

    while( i <= mid )
        *(tmp + k++) = *(arr + i++);
    while( j <= high )
        *(tmp + k++) = *(arr + j++);

    for( i=low, k=0; i<=high; i++, k++ )
    {
        *(arr + i) = *(tmp + k);
    }

    delete [] tmp;
}

template <typename T> void MergeSort( T* arr, int low, int high )
{
    int mid;
    if ( low < high )
    {
        mid = ( low + high ) / 2;
        MergeSort( arr, low, mid );
        MergeSort( arr, mid+1, high );
        Merge( arr, low, mid, high );
    }
}

int main()
{
    int i;
    int a[]={1,4,2,66,22,23,5,6,8,7,99,54};
    MergeSort<int>(a, 0, 11);
    for(i=0;i<12;i++)
        cout<<a[i]<<endl;

    double b[]={5.1,4.5,2.2,66.5,22.6,23,5,6,18.1,7,99,54};
    MergeSort<double>(b, 0, 11);
    for(i=0;i<12;i++)
        cout<<b[i]<<endl;

    return 0;
}
