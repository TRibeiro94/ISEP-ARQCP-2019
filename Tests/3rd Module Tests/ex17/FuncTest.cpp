#include <CppUTest/TestHarness.h>

extern "C"
{
#include <stdio.h>
#include <memory.h> 
#include <string.h> 
#include "asm.h"   	
int  * ptrvec;  
int num;  
void call_func(void (*f)()); 

}

//START: testGroup
TEST_GROUP(array_sort)
{
    int test_vec[100];
    int *expected;
    void setup()
    {
        memset(test_vec, 0xaa, sizeof test_vec);
        expected = NULL; 
	ptrvec=test_vec; 
    }
    void teardown()
    {
    }
    void expect(int * exp)
    {
        expected = exp;
    }
    void given(int * vec, int num_elem)
    { 
	memcpy(test_vec,vec,num_elem*sizeof(int)); 
	num=num_elem; 
	call_func(array_sort); 
	MEMCMP_EQUAL(expected,test_vec,num_elem*sizeof(int)) ; 
        BYTES_EQUAL(0xaa, test_vec[num_elem]& 0xff);
    }
};
//END: testGroup

TEST(array_sort, NullVector)
{
    int e[]={0}; 
    expect(e); 
    int v[]={0}; 
    given(v,0);
}

TEST(array_sort, One)
{
    int e[]={1}; 
    expect(e);
    int v[]={1}; 
    given(v,1);
}


TEST(array_sort,Zero)
{
    int e[]={2,1,0}; 
    expect(e);
    int v[]={2,0,1}; 
    given(v,3);
}


TEST(array_sort,MinusThree)
{
    int e[]={-1,-2,-3}; 
    expect(e);
    int v[]={-1,-2,-3}; 
    given(v,3);
}

TEST(array_sort,Ten)
{
    int e[]={2,1,1,1,1,1,1,1,1}; 
    expect(e);
    int v[]={1,1,1,1,1,1,1,1,2}; 
    given(v,9);
}




