#include "pd_main.h"

void pd_merge(size_t *arr, size_t l, size_t m, size_t r) 
{ 
    size_t i, j, k; 
    size_t n1 = m - l + 1; 
    size_t n2 =  r - m; 
    size_t L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
            arr[k] = L[i++]; 
        else
            arr[k] = R[j++]; 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i++]; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j++]; 
        k++; 
    } 
} 
  
void pd_merge_sort(size_t *arr, size_t l, size_t r) 
{ 
    if (l < r) 
    {
        size_t m = l+(r-l)/2; 
        pd_merge_sort(arr, l, m); 
        pd_merge_sort(arr, m+1, r); 
        pd_merge(arr, l, m, r); 
    } 
} 

void  pd_math_si_sort(pd_arr *arr) 
{
    if (arr->type != PD_T_SIZE_T)
        return ;
    pd_merge_sort((size_t*)arr->val, 0, arr->len - 1); 
}