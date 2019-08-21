/*递减元素使数组呈锯齿状  显示英文描述  
用户通过次数 390
用户尝试次数 584
通过次数 393
提交次数 1476
题目难度 Medium
给你一个整数数组 nums，每次 操作 会从中选择一个元素并 将该元素的值减少 1。

如果符合下列情况之一，则数组 A 就是 锯齿数组：

每个偶数索引对应的元素都大于相邻的元素，即 A[0] > A[1] < A[2] > A[3] < A[4] > ...
或者，每个奇数索引对应的元素都大于相邻的元素，即 A[0] < A[1] > A[2] < A[3] > A[4] < ...
返回将数组 nums 转换为锯齿数组所需的最小操作次数。

 

示例 1：

输入：nums = [1,2,3]
输出：2
解释：我们可以把 2 递减到 0，或把 3 递减到 1。
示例 2：

输入：nums = [9,6,1,6,2]
输出：4

*/
struct tree_array{
    int parent_index;
    int parent_val;
    int left_son_index;
    int left_son_val;
    int right_son_index;
    int right_son_val;
};

int movesToMakeZigzag(int* nums, int numsSize){
    struct tree_array t_a[1000];
    
    int i=0;
    int j=0;
    int num_tree=0;
    int count=0;
    int count_2=0;
    int flag=0;
    
    //init
    for(i=0;i<numsSize-2;i+=2)
    {
        t_a[j].parent_index=i+1;
        t_a[j].parent_val=nums[i+1];
        t_a[j].left_son_index=i;
        t_a[j].left_son_val=nums[i];
        t_a[j].right_son_index=i+2;
        t_a[j].right_son_val=nums[i+2];
        j++;
        num_tree++;
		
    }   
	if(i==numsSize-2)
	{
        t_a[j].parent_index=i+1;
        t_a[j].parent_val=nums[i+1];
        t_a[j].left_son_index=i;
        t_a[j].left_son_val=nums[i];
        t_a[j].right_son_index=-1;
        t_a[j].right_son_val=-1;
        j++;
        num_tree++;
	}		
    //show tree 
    for(j=0;j<num_tree;j++)
    {
		printf("tree %d {%d,%d,%d}\n",j,t_a[j].left_son_val,t_a[j].parent_val,t_a[j].right_son_val);
	}		
    //scan  parent > son 
    while(1)
    {
        flag = 1;
        for(j=0;j<num_tree;j++)
        {
			if(t_a[j].right_son_val == -1)
			{
				if(t_a[j].parent_val>t_a[j].left_son_val)
					continue;
				else{
					if(t_a[j].left_son_val >= t_a[j].parent_val){
						t_a[j].left_son_val -= 1;
						if(j>0)
							t_a[j-1].right_son_val -= 1;
						count+=1;
						printf("t_a[%d].left_son_val=%d t_a[%d].parent_val=%d\n",j,t_a[j].left_son_val , j,t_a[j].parent_val);
						flag = 0;
					}
				}
			}				
            else
			{
				if((t_a[j].parent_val>t_a[j].left_son_val)&&(t_a[j].parent_val>t_a[j].right_son_val))
					continue;
				else{
					if(t_a[j].left_son_val >= t_a[j].parent_val){
						t_a[j].left_son_val -= 1;
						if(j>0)
							t_a[j-1].right_son_val -= 1;
						count+=1;
						printf("t_a[%d].left_son_val=%d t_a[%d].parent_val=%d\n",j,t_a[j].left_son_val , j,t_a[j].parent_val);
						flag = 0;
					}
					if(t_a[j].right_son_val >= t_a[j].parent_val){
						t_a[j].right_son_val -= 1;
						t_a[j+1].left_son_val -= 1;
						count+=1;
						printf("t_a[%d].right_son_val=%d t_a[%d].parent_val=%d\n",j,t_a[j].right_son_val , j,t_a[j].parent_val);
						flag = 0;
					}    
					
				}
			}
        }    
        if(flag == 1)
            break;
    }    
	printf("first scan count=%d\n",count);
    //init
	j=0;
	num_tree=0;

    for(i=0;i<numsSize-2;i+=2)
    {
        t_a[j].parent_index=i+1;
        t_a[j].parent_val=nums[i+1];
        t_a[j].left_son_index=i;
        t_a[j].left_son_val=nums[i];
        t_a[j].right_son_index=i+2;
        t_a[j].right_son_val=nums[i+2];
        j++;
        num_tree++;
    } 
	if(i==numsSize-2)
	{
        t_a[j].parent_index=i+1;
        t_a[j].parent_val=nums[i+1];
        t_a[j].left_son_index=i;
        t_a[j].left_son_val=nums[i];
        t_a[j].right_son_index=-1;
        t_a[j].right_son_val=-1;
        j++;
        num_tree++;
	}		
	
    //scan  parent < son
    while(1)
    {
        flag = 1;
        for(j=0;j<num_tree;j++)
        {
			if(t_a[j].right_son_val == -1)
			{
				if(t_a[j].parent_val<t_a[j].left_son_val)
					continue;
				else{
					if(t_a[j].parent_val >= t_a[j].left_son_val){
						t_a[j].parent_val -= 1;
						count_2+=1;
						flag = 0;
					}
				   
				}				
			}
            else
			{	
				if((t_a[j].parent_val<t_a[j].left_son_val)&&(t_a[j].parent_val<t_a[j].right_son_val))
					continue;
				else{
					if(t_a[j].parent_val >= ((t_a[j].left_son_val<t_a[j].right_son_val)?t_a[j].left_son_val:t_a[j].right_son_val)){
						t_a[j].parent_val -= 1;
						count_2+=1;
						flag = 0;
					}
				   
				}
			}	
        }    
        if(flag == 1)
            break;
    }      
    printf("second scan count=%d\n",count_2);	
    return (count<count_2)?count:count_2;
}

void main()
{
    int test_array_1[10]={1,2,3};
	int test_array_2[10]={9,6,1,6,2};
	int test_array_3[10]={2,1,2};
    int test_array_4[10]={2,7,10,9,8,9};
	int test_array_5[40]={10,1,1,6,6,6,1,8,8,5,1,2,6,6,6,4,4,8,7,1};
	int test_array_6[10]={2,1,2,1};
	int test_array_7[100] = {48,280,658,556,516,931,940,553,780,477,
	                      107,791,911,30,306,606,389,534,437,405,
						  837,194,61,977,71,987,82,131,218,903,
						  990,141,766,720,689,993,645,1000,392,984,
						  208,677,194,945,871,249,175,796,146,17,
						  439,208,229,86,345,571,601,86,490,664,
						  838,916,481,469,932,415,984,754,196,837,
						  930,935,894,582,647,718,973,726,848,611,
						  395,713,751,840,714,352,912,326,302,171,
						  218,534,847,232,302,792,194,250,411,680};
	int ret=0;
	ret = movesToMakeZigzag(test_array_1,3);
	printf("test 1 : {1,2,3}\n");
	printf("expect : 2\n");
	printf("result : %d\n",ret);
	ret = movesToMakeZigzag(test_array_2,5);
	printf("test 2 : {9,6,1,6,2}\n");
	printf("expect : 4\n");
	printf("result : %d\n",ret);
	ret = movesToMakeZigzag(test_array_3,3);
	printf("test 3 : {2,1,2}\n");
	printf("expect : 0\n");
	printf("result : %d\n",ret);
	ret = movesToMakeZigzag(test_array_4,6);
	printf("test 4 : {2,7,10,9,8,9}\n");
	printf("expect : 4\n");
	printf("result : %d\n",ret);	
	ret = movesToMakeZigzag(test_array_5,20);
	printf("test 5 : {10,1,1,6,6,6,1,8,8,5,1,2,6,6,6,4,4,8,7,1}\n");
	printf("expect : 32\n");
	printf("result : %d\n",ret);	
	ret = movesToMakeZigzag(test_array_6,4);
	printf("test 6 : {2,1,2,1}\n");
	printf("expect : 0\n");
	printf("result : %d\n",ret);	
	ret = movesToMakeZigzag(test_array_7,100);
	printf("test 7 : {...}\n");
	printf("expect : unkonwn\n");
	printf("result : %d\n",ret);	
}
