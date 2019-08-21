
/*
726. 原子的数量

给定一个化学式formula（作为字符串），返回每种原子的数量。

原子总是以一个大写字母开始，接着跟随0个或任意个小写字母，表示原子的名字。

如果数量大于 1，原子后会跟着数字表示原子的数量。如果数量等于 1 则不会跟数字。例如，H2O 和 H2O2 是可行的，但 H1O2 这个表达是不可行的。

两个化学式连在一起是新的化学式。例如?H2O2He3Mg4 也是化学式。

一个括号中的化学式和数字（可选择性添加）也是化学式。例如 (H2O2) 和 (H2O2)3 是化学式。

给定一个化学式，输出所有原子的数量。格式为：第一个（按字典序）原子的名子，跟着它的数量（如果数量大于 1），然后是第二个原子的名字（按字典序），跟着它的数量（如果数量大于 1），以此类推。

示例 1:

输入: 
formula = "H2O"
输出: "H2O"
解释: 
原子的数量是 {'H': 2, 'O': 1}。
示例 2:

输入: 
formula = "Mg(OH)2"
输出: "H2MgO2"
解释: 
原子的数量是 {'H': 2, 'Mg': 1, 'O': 2}。
示例 3:

输入: 
formula = "K4(ON(SO3)2)2"
输出: "K4N2O14S4"
解释: 
原子的数量是 {'K': 4, 'N': 2, 'O': 14, 'S': 4}。
注意:

所有原子的第一个字母为大写，剩余字母都是小写。
formula的长度在[1, 1000]之间。
formula只包含字母、数字和圆括号，并且题目中给定的是合法的化学式。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-atoms
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
//需求拆解；
//大写字母解析处理，小写字母处理，作为原子单元
//括号左边，右边处理，括号内部原子计数处理
//数字计数处理
//重复原子计数累加处理

//多遍扫描可能会简单一些；方便功能隔离
//先扫描出原子；
//然后查看原子的位置
//后面是否有数字
//是否在括号里面，在多个括号里面？
//括号外面一般都是有数字的

#include "stdio.h"
#include "stdlib.h"

char * countOfAtoms(char * formula)
{
    int i=0;
    char result_str[2000]={0};
    char atomic_list[100][100];
    char atomic_list_finish[100][100];
    int atomic_index = 0;
    int atomic_num[100]={0};
    char temp[100]={0};
    int temp_num=0;
    
    int atomic_start = 0;
    char atomic_temp[100]={0};
    int atomic_temp_index = 0;
    int left_brack_start = 0;
    int right_brack_flag = 0;
    int left_brack_start_index[100] = {0};
    int left_brack_start_index_num = 0;
    int j=0;
    int atomic_index_finish=0;
    int ret_str = 0;
    
    memset(atomic_list,0,100*100);
    
    if((formula[0]>=0x41)&&(formula[0]<=0x5a))/* A-Z */
    {
        //printf("normal begin strlen=%d\n",strlen(formula));
    }        
    else
        return NULL;
        
    for(i=0;i<strlen(formula)+1;i++)
    {
        //printf("i=%d %c\n",i,formula[i]);
        if((formula[i]>=0x41)&&(formula[i]<=0x5a))/* A-Z */
        {
            
            if(1 == atomic_start)
            {
                atomic_start = 0;
                if(0 == atomic_num[atomic_index])
                {
                    atomic_num[atomic_index] += 1;
                }                
                //add_atomic_to_list(atomic_temp[atomic_index]);
                strcpy(&atomic_list[atomic_index++][0],atomic_temp);
                
                atomic_temp_index = 0;
                memset(atomic_temp,0,100);
                atomic_start = 1;//连续两个大写
                atomic_temp[atomic_temp_index++]=formula[i];
                
            }
            else if(0 == atomic_start)    
            {
                atomic_start = 1;
                atomic_temp[atomic_temp_index++]=formula[i];
                
            }    
            
            
        }    
        if((formula[i]>=0x61)&&(formula[i]<=0x7a))/* a-z */
        {
            //??
            atomic_temp[atomic_temp_index++]=formula[i];
        }    
            
        if(formula[i] == 0x28/*'('*/)
        {    
            if(1 == atomic_start)
            {
                atomic_start = 0;
                //add_atomic_to_list(atomic_temp[atomic_index]);
                //strcpy(atomic_list[atomic_index],atomic_temp);
                if(0 == atomic_num[atomic_index])
                {
                    atomic_num[atomic_index] += 1;
                }    
                strcpy(&atomic_list[atomic_index++][0],atomic_temp);
                
                atomic_temp_index = 0;
                memset(atomic_temp,0,100);
                //atomic_start = 1;
                //atomic_temp[atomic_temp_index++]=formula[i];
                                
            }
            left_brack_start = 1;
            left_brack_start_index[left_brack_start_index_num] = atomic_index;
            left_brack_start_index_num += 1;
            
            
        }            
        if(formula[i] == 0x29/*')'*/)    
        {

            if(1 == atomic_start)
            {
                atomic_start = 0;
                //add_atomic_to_list(atomic_temp[atomic_index]);
                //strcpy(atomic_list[atomic_index],atomic_temp);
                if(0 == atomic_num[atomic_index])
                {
                    atomic_num[atomic_index] += 1;
                }    
                strcpy(&atomic_list[atomic_index++][0],atomic_temp);
                
                atomic_temp_index = 0;
                memset(atomic_temp,0,100);
                               
            }
            right_brack_flag=1;
        }    
        if((formula[i]>=0x31)&&(formula[i]<=0x39))/* 1-9 */
        {
            //??
            if(1 == atomic_start)
            {
                atomic_start = 0;
                atomic_num[atomic_index] += formula[i] - 0x30;
                //add_atomic_to_list(atomic_temp[atomic_index]);
                strcpy(&atomic_list[atomic_index++][0],atomic_temp);
                
                atomic_temp_index = 0;
            
            }   
            else if(right_brack_flag == 1)
            {
                left_brack_start_index_num -= 1;    
                for(j=left_brack_start_index[left_brack_start_index_num];j<atomic_index;j++)
                    atomic_num[j] *= formula[i] - 0x30;
                
                right_brack_flag = 0;
            }              
            //atomic_start = 1;
            //atomic_temp[atomic_temp_index++]=formula[i];            
        }   
        if((formula[i] == '\0') || (formula[i] == '\n') || (formula[i] == 0))
        {
            //printf("str end\n");
            if(1 == atomic_start)
            {    
                atomic_start = 0;
                if(0 == atomic_num[atomic_index])
                {
                    atomic_num[atomic_index] += 1;
                }                
                //add_atomic_to_list(atomic_temp[atomic_index]);
                strcpy(&atomic_list[atomic_index++][0],atomic_temp);            
            }
        }                  
                
    }
    
    //sync();
    //printf("atomic_index=%d\n",atomic_index);
    for(i=0;i<atomic_index;i++)
    {
        //printf(" %d atomic is %s num is %d\n",i,atomic_list[i],atomic_num[i]);
        strcat(result_str,atomic_list[i]);
        
        
        if(atomic_num[i] > 1)
        {
            memset(temp,0,100);
            sprintf(temp,"%d",atomic_num[i]);
            strcat(result_str,temp);
        }    
            
        
    }     
    //printf("result:%s\n",result_str);
    //合并相同原子
    memset(atomic_list_finish,0,100*100);
    strcpy(atomic_list_finish[0],atomic_list[0]);
    atomic_index_finish += 1;
    for(i=1;i<atomic_index;i++)
    {
        //printf(" %d atomic is %s num is %d\n",i,atomic_list[i],atomic_num[i]);
        for(j=0;j<i;j++)
        {
            ret_str = strcmp(atomic_list_finish[j],atomic_list[i]);
            if(ret_str == 0)
            {
                atomic_num[j] += atomic_num[i];
                break;
            }   
        }
        if (j==i)
        {    
            strcpy(atomic_list_finish[i],atomic_list[i]);
            atomic_index_finish += 1;
        }    
        
    } 
    
    //最后重新按照大写顺序排序；?
    for(i=0;i<atomic_index_finish;i++)
    {
        memset(temp,0,100);
        strcpy(temp,atomic_list_finish[i]);
        for(j=i;j<atomic_index_finish;j++)
        {

            ret_str = strcmp(atomic_list_finish[j],temp);
            if(ret_str < 0)
            {
                strcpy(temp,atomic_list_finish[j]);
                temp_num=atomic_num[j];
                strcpy(atomic_list_finish[j],atomic_list_finish[i]);
                atomic_num[j] = atomic_num[i];
                strcpy(atomic_list_finish[i],temp);
                atomic_num[i] = temp_num;                
            }   
        }
        
    } 
        
    memset(result_str,0,2000);
    //printf("atomic_index_finish=%d\n",atomic_index_finish);
    for(i=0;i<atomic_index_finish;i++)
    {
        //printf(" %d atomic is %s num is %d\n",i,atomic_list_finish[i],atomic_num[i]);
        strcat(result_str,atomic_list_finish[i]);
        
        
        if(atomic_num[i] > 1)
        {
            memset(temp,0,100);
            sprintf(temp,"%d",atomic_num[i]);
            strcat(result_str,temp);
        }    
            
        
    }    
    //printf("result:%s\n",result_str);

    
   
    //printf("result:%s\n",result_str);      
    return result_str;  
}
void main()
{
    printf("Input  : %s\n","H2O");
    printf("Answer : %s\n","H2O");
    printf("Output : %s\n",countOfAtoms("H2O"));
    printf("Input  : %s\n","Mg(OH)2");
    printf("Answer : %s\n","H2MgO2");    
    printf("Output : %s\n",countOfAtoms("Mg(OH)2"));
    printf("Input  : %s\n","K4(ON(SO3)2)2");
    printf("Answer : %s\n","K4N2O14S4");     
    printf("Output : %s\n",countOfAtoms("K4(ON(SO3)2)2"));
}
