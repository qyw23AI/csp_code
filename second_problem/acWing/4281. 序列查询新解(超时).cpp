/*
 4281. 序列查询新解

      题目
      提交记录
      讨论
      题解
      视频讲解


上一题“序列查询”中说道：

A=[A0,A1,A2,⋯,An] 是一个由 n+1 个 [0,N) 范围内整数组成的序列，满足 0=A0<A1<A2<⋯<An<N。

基于序列 A，对于 [0,N) 范围内任意的整数 x，查询 f(x) 定义为：序列 A 中小于等于 x 的整数里最大的数的下标。

对于给定的序列 A 和整数 x，查询 f(x) 是一个很经典的问题，可以使用二分搜索在 O(logn) 的时间复杂度内轻松解决。

但在 IT 部门讨论如何实现这一功能时，小 P 同学提出了些新的想法。

小 P 同学认为，如果事先知道了序列 A 中整数的分布情况，就能直接估计出其中小于等于 x 的最大整数的大致位置。

接着从这一估计位置开始线性查找，锁定 f(x)。

如果估计得足够准确，线性查找的时间开销可能比二分查找算法更小。

比如说，如果 A1,A2,⋯,An 均匀分布在 (0,N) 的区间，那么就可以估算出：

f(x)≈(n+1)⋅xN

为了方便计算，小 P 首先定义了比例系数 r=⌊Nn+1⌋，其中 ⌊ ⌋ 表示下取整，即 r 等于 N 除以 n+1 的商。

进一步地，小 P 用 g(x)=⌊xr⌋ 表示自己估算出的 f(x) 的大小，这里同样使用了下取整来保证 g(x) 是一个整数。

显然，对于任意的询问 x∈[0,N)，g(x) 和 f(x) 越接近则说明小 P 的估计越准确，后续进行线性查找的时间开销也越小。

因此，小 P 用两者差的绝对值 |g(x)−f(x)| 来表示处理询问 x 时的误差。

为了整体评估小 P 同学提出的方法在序列 A 上的表现，试计算：

error(A)=∑i=0N−1|g(i)−f(i)|=|g(0)−f(0)|+⋯+|g(N−1)−f(N−1)|
输入格式

输入的第一行包含空格分隔的两个正整数 n 和 N。

输入的第二行包含 n 个用空格分隔的整数 A1,A2,⋯,An。

注意 A0 固定为 0，因此输入数据中不包括 A0。
输出格式

仅输出一个整数，表示 error(A) 的值。
数据范围

70% 的测试数据满足 1≤n≤200 且 n<N≤1000；
全部的测试数据满足 1≤n≤105 且 n<N≤109。
输入样例1：

3 10
2 5 8

输出样例1：

5

样例1解释

A=[0,2,5,8]
r=⌊Nn+1⌋=⌊103+1⌋=2
i 	0 	1 	2 	3 	4 	5 	6 	7 	8 	9
f(i) 	0 	0 	1 	1 	1 	2 	2 	2 	3 	3
g(i) 	0 	0 	1 	1 	2 	2 	3 	3 	4 	4
∥g(i)−f(i)∥ 	0 	0 	0 	0 	1 	0 	1 	1 	1 	1
输入样例2：

9 10
1 2 3 4 5 6 7 8 9

输出样例2：

0

输入样例3：

2 10
1 3

输出样例3：

6

样例3解释

A=[0,1,3]
r=⌊Nn+1⌋=⌊102+1⌋=3
i 	0 	1 	2 	3 	4 	5 	6 	7 	8 	9
f(i) 	0 	1 	1 	2 	2 	2 	2 	2 	2 	2
g(i) 	0 	0 	0 	1 	1 	1 	2 	2 	2 	3
∥g(i)−f(i)∥ 	0 	1 	1 	1 	1 	1 	0 	0 	0 	1
提示

需要注意，输入数据 [A1⋯An] 并不一定均匀分布在 (0,N) 区间，因此总误差 error(A) 可能很大。

*/
#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n, N;
    cin>> n >> N;
    vector<int> a(n+2,0);
    for(int i=1;i<=n;i++)
    cin>> a[i];

    //记录最大的N
    a[n+1]=N;

    //计算r
    int r = N / (n+1);
    //总误差
    long long sum =0;
    // [a[i], a[i+1]-1]区间的f值不变
    for(int i=0;i<=n;i++){
        int L = a[i];
        int R = a[i+1]-1;
        while(L<=R){
           int g = L / r;
           int nr = min(R, (g+1)*r-1);
           sum += 1LL * abs(g-i) * (nr - L +1);
           L = nr + 1; 
        }
    }
    cout<< sum;
    return 0;
}

/*
    超时的代码如下：
    #include<vector>
    #include<iostream>
    using namespace std;

    int main(){
        int n,N;
        cin>> n >> N;
        vector<int> A(n+1, 0);
        for(int i=1;i<n+1;i++){
            cin>> A[i];
        }
        //计算r
        int r = N / (n+1);
        //计算每个值
        int cur_f=0;
        int cur_g=0;
        long long sum =0;
        for(int i=0;i<N;i++){
            int error =0;
            cur_g = i / r;
            //计算error
            if(i<A[cur_f+1]){
                error = abs(cur_f-cur_g);
            }else{
                //先找出cur_f
                while(i>=A[cur_f+1]&&cur_f<n){
                    cur_f++;
                }
                error = abs(cur_f-cur_g);
            }
            sum+=error;
        }
        cout<<sum;
        return 0;
    }
*/
