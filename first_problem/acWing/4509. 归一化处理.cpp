/*
 4509. 归一化处理


在机器学习中，对数据进行归一化处理是一种常用的技术。

将数据从各种各样分布调整为平均值为 0、方差为 1 的标准分布，在很多情况下都可以有效地加速模型的训练。

这里假定需要处理的数据为 n 个整数 a1,a2,⋯,an。

这组数据的平均值：

a¯=a1+a2+⋯+ann

方差：

D(a)=1n∑i=1n(ai−a¯)2

使用如下函数处理所有数据，得到的 n 个浮点数 f(a1),f(a2),⋯,f(an) 即满足平均值为 0 且方差为 1：

f(ai)=ai−a¯D(a)−−−−√
输入格式

第一行包含一个整数 n，表示待处理的整数个数。

第二行包含空格分隔的 n 个整数，依次表示 a1,a2,⋯,an。
输出格式

输出共 n 行，每行一个浮点数，依次表示按上述方法归一化处理后的数据 f(a1),f(a2),⋯,f(an)。

如果你输出的每个浮点数与参考结果相比，均满足绝对误差不大于 10−4，则该测试点满分，否则不得分。
数据范围

全部的测试数据保证 n,|ai|≤1000，其中 |ai| 表示 ai 的绝对值。
且输入的 n 个整数 a1,a2,⋯,an 满足：方差 D(a)≥1。
输入样例：

7
-4 293 0 -22 12 654 1000

输出样例：

-0.7485510379073613
0.04504284674812264
-0.7378629047806881
-0.7966476369773906
-0.7057985054006686
1.0096468614303775
1.9341703768876082

样例解释

平均值：a¯≈276.14285714285717
方差：D(a)≈140060.69387755104
标准差：D(a)−−−−√≈374.24683549437134
*/
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

int main(){
	double n=0;
	cin>>n;
	vector<int> arr;
	int i=0;
	double sum=0;
	while(i<n){
		i++;
		int num=0;
		cin>>num;
		arr.push_back(num);
		sum += num; 
	} 
	double average = sum / n;
	i=0;
	double sum_d = 0;
	while(i<n){
		i++;
		sum_d += pow(arr[i]- average, 2);
	}
	double d = sum_d / n;
	double d_half = pow(d, 0.5);
	i =0;
	while(i<n){
		cout<< (arr[i]-average)/d_half<<endl;
		i++;
	}
	return 0;
} 

