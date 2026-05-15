/*
A1,A2,⋯,An 是一个由 n 个自然数（即非负整数）组成的数组。

在此基础上，我们用数组 B1⋯Bn 表示 A 的前缀最大值。

Bi=max{A1,A2,⋯,Ai}

如上所示，Bi 定义为数组 A 中前 i 个数的最大值。

根据该定义易知 A1=B1，且随着 i 的增大，Bi 单调不降。

此外，我们用 sum=A1+A2+⋯+An 表示数组 A 中 n 个数的总和。

现已知数组 B，我们想要根据 B 的值来反推数组 A。

显然，对于给定的 B，A 的取值可能并不唯一。

试计算，在数组 A 所有可能的取值情况中，sum 的最大值和最小值分别是多少？
输入格式

输入的第一行包含一个正整数 n。

输入的第二行包含 n 个用空格分隔的自然数 B1,B2,⋯,Bn。
输出格式

输出共两行。

第一行输出一个整数，表示 sum 的最大值。

第二行输出一个整数，表示 sum 的最小值。
数据范围

50% 的测试数据满足数组 B 单调递增，即 0<B1<B2<⋯<Bn<105；
全部的测试数据满足 n≤100 且数组 B 单调不降，即 0≤B1≤B2≤⋯≤Bn≤105。
输入样例1：

6
0 0 5 5 10 10

输出样例1：

30
15

样例1解释

数组 A 的可能取值包括但不限于以下三种情况。

    情况一：A=[0,0,5,5,10,10]
    情况二：A=[0,0,5,3,10,4]
    情况三：A=[0,0,5,0,10,0]

其中第一种情况 sum=30 为最大值，第三种情况 sum=15 为最小值。
输入样例2：

7
10 20 30 40 50 60 75

输出样例2：

285
285

样例2解释

A=[10,20,30,40,50,60,75] 是唯一可能的取值，所以 sum 的最大、最小值均为 285。
*/

#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

int main(){
	int n;
	cin>>n;
	long sum_max =0;
	long sum_min =0;
	int pre = 0;
	int num_b = 0;
	while(n>0){
		cin>>num_b;
		if(num_b>pre){
			sum_min+=num_b;
			sum_max+=num_b; 
		}
		else{
			sum_min+=0;
			sum_max+=pre;
		}
		pre=num_b;
		n--;
	}
	cout<<sum_max<<endl;
	cout<<sum_min;
	return 0;
} 

