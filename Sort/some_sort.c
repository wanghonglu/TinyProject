#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
#include "merge_sort.h"
#include "quick_sort.h"
#include<sys/time.h>
int *ProduceRandomArray(int len)
{
    static int init=0;
    if(!init)
    {
        srand(time(NULL));
        init = 1;
    }
    int *ptr = (int*)malloc(sizeof(int)*len);
    assert(ptr != NULL );
    int i=0;
    for(;i<len;++i)
        ptr[i]=random();
    return ptr;
}
long
now_mic()
{
    struct timeval tm;
    gettimeofday(&tm, NULL);
    return tm.tv_sec*1e6+tm.tv_usec;    
}
typedef void(*fun)(int*,int );
typedef struct SortTest{
    char*  msg;
    fun    sort_fun;
}SortTest;

void PrintArray(const char*msg,  int* ptr, int len )
{
    if( len>100 )
        return;
    int i=0;
    printf( "%s\n", msg );
    for( i=0;i<len;i++ )
    {
        printf("%d ", ptr[i]);
    }
    printf("\n");
}
int Check(int *ptr, int len )
{
    if(len <=1 )return 1;

    int idx=0;
    for( idx=1;idx<len;idx++ )
    {
        if( ptr[idx]<ptr[idx-1] )
            return 0;
    }
    return 1;
}
#define IntLen(a) sizeof(a)/sizeof(int)
#define MaxOrderredNumber 100000 
int *orderredNumber = NULL;//有序数组
#define MutipleNumberArray 100000
int *mutipleNumberArray = NULL;//全部重复数组

void GetOrderredNumber()
{
    if( orderredNumber )
        free(orderredNumber);
    orderredNumber = (int*)malloc(sizeof(int)*MaxOrderredNumber);
    int beg = 1;
    int i=0;
    for( ;i<MaxOrderredNumber;i++ )
        orderredNumber[i]=beg+i;

}
void GetMutipleNumberArray()
{
    if( mutipleNumberArray )
        free(mutipleNumberArray);
    mutipleNumberArray =(int*)malloc(sizeof(int)*MutipleNumberArray);
    int beg = random();
    int i=0;
    for( ;i<MutipleNumberArray;i++ )
        mutipleNumberArray[i]=beg;
}
int main(int argc ,char**argv)
{
    GetOrderredNumber();
    GetMutipleNumberArray();
    int count =0;
    if( argc >= 2 )
        count  = atoi(argv[1]);
    int sort_idx=0;
    SortTest arry[]={
        {"迭代版归并排序", merge_sort },
        {"递归版归并排序", recursive_merge_sort},
        {"普通快排", quick_sort},
        {"基准选右边快排", quick_sort2},
        {"三数取中法快排", better_quick_sort},//数组如果本来就有序 复杂度将达到n^2
        {"带去重的三数取中法快排", better_quick_sort2},//数组如果本来就有序 复杂度将达到n^2
        {NULL, NULL}
    };
    //int a[]={3,3,3,6,2,1};
    int a[]={3,3,3,3,3,3,3,3,3,3,3,3};

    int *ptr = NULL;
    if(count > 0 )
    {
        ptr = ProduceRandomArray(count);
    }
    else if( count == -1 )//有序数据排序
    {
        ptr = orderredNumber;    
        count = MaxOrderredNumber;
    }
    else if( count == -2 )//重复数据排序
    {
        ptr =mutipleNumberArray;
        count = MutipleNumberArray;  
    }
    else 
    {
        ptr = a;
        count = sizeof(a)/sizeof(int);
    }

    int *b = (int*)malloc(sizeof(int)*count);
    assert( NULL!=b);

    memcpy( b, ptr,count*sizeof(int));
    SortTest *tmp=NULL;
    while( (tmp = &arry[sort_idx++]) && tmp->sort_fun !=NULL )
    {
        fprintf( stderr, "=== %s === \n", tmp->msg ); 
        memcpy( ptr, b, count*sizeof(int));
        PrintArray("排序前", ptr, count);
        long t1 = now_mic();
        tmp->sort_fun( ptr, count );
        printf("耗时:%d 微秒\n", now_mic()-t1 );
        PrintArray("排序后", ptr, count);
        fprintf( stderr, "%s\n", Check(ptr, count)?"正确":"错误!!!!!" );
        printf("===   end  ====\n\n");
    }

    if( ptr!=a )
        free(ptr);
    free(b);
}














