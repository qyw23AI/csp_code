/*
 5416. 因子化简

      题目
      提交记录
      讨论
      题解
      视频讲解


质数（又称“素数”）是指在大于 1 的自然数中，除了 1 和它本身以外不再有其他因数的自然数。

小 P 同学在学习了素数的概念后得知，任意的正整数 n 都可以唯一地表示为若干素因子相乘的形式。

如果正整数 n 有 m 个不同的素数因子 p1,p2,…,pm，则可以表示为：n=pt11×pt22×…×ptmm。

小 P 认为，每个素因子对应的指数 ti 反映了该素因子对于 n 的重要程度。

现设定一个阈值 k，如果某个素因子 pi 对应的指数 ti 小于 k，则认为该素因子不重要，可以将 ptii 项从 n 中除去；反之则将 ptii 项保留。

最终剩余项的乘积就是 n 简化后的值，如果没有剩余项则认为简化后的值等于 1。

试编写程序处理 q 个查询：

每个查询包含两个正整数 n 和 k，要求计算按上述方法将 n 简化后的值。
输入格式

输入共 q+1 行。

输入第一行包含一个正整数 q，表示查询的个数。

接下来 q 行每行包含两个正整数 n 和 k，表示一个查询。
输出格式

输出共 q 行。

每行输出一个正整数，表示对应查询的结果。
数据范围

40% 的测试数据满足：n≤1000；
80% 的测试数据满足：n≤105；
全部的测试数据满足：1<n≤1010 且 1<k,q≤10。
输入样例：

3
2155895064 3
2 2
10000000000 10

输出样例：

2238728
1
10000000000

样例解释

查询一：

    n=23×32×234×107
    其中素因子 3 指数为 2，107 指数为 1。将这两项从 n 中除去后，剩余项的乘积为 23×234=2238728。

查询二：

    所有项均被除去，输出 1。

查询三：

    所有项均保留，将 n 原样输出。


*/

/*
下面这种估计素数范围的方法只能够通过70%的案例，没有办法解决本身就是极大的
素数的情况

#include<vector>
#include<iostream>
#include<cmath>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<vector<long>> arr(n, vector<long>(2,0));
    for(int i=0;i<n;i++){
        cin >> arr[i][0] >> arr[i][1];
    }
    //计算并保存素因子，初步判断是1000以内的素数构成绝大部分的整数
    vector<int> prime_number;
    for(int i=2;i<1000;i++){
        prime_number.push_back(i);
        for(int j=2;j<i;j++){
            if(i%j==0){
                prime_number.pop_back();
                break;
            }
        }
    }
    for(int i=0;i<n;i++){
        long num = arr[i][0];
        long k = arr[i][1];
        vector<int> prime_t(prime_number.size(), 0); //保存t_i
        vector<int> prime_idx; //记录达到t>k的要求的prime的索引，用于计算最后的输出，如果没有则输出1
        //试除法，直到被除数为1
        int j = 0; //试除的素数idx
        while(num>1){
            if(num % prime_number[j]==0){
                num /= prime_number[j];
                prime_t[j]++;
                if(prime_t[j]==k){
                    //达到了最小的指数要求，则算上该素因子
                    prime_idx.push_back(j);
                }
            }else{
                //无法整除就换另一个素数来除
                j++;
            }
        }
        //判断计算本次的输出
        if(prime_idx.empty()){
            cout<<1<<endl;
        }else{
            long res =1;
            for(int k=0;k<prime_idx.size();k++){
                int idx = prime_idx[k];
                res *= pow(prime_number[idx],prime_t[idx]);
            }
            cout<<res<<endl;
        }
    }
    return 0;
}
*/

#include<iostream>
#include<cmath>
using namespace std;

typedef long long LL;

int main(){
    int n;
    cin>> n;
    for(int i=0;i<n;i++){
        LL num , k;
        cin >> num >> k;
        LL x = num;
        LL res = 1;
        for(LL j=2;j * j < x; j++){
            //不需要进行质数判断，因为合数在后面,而能够构成合数的已经被前面的质数除掉了
            
            int cnt = 0;
            while(num % j==0){
                num/= j;
                cnt++;
            }
            if(cnt>=k){
                res*= pow(j, cnt);
            }
        }
        if(num>1&& k<=1){ //这里很容易出错
            res *= num;
        }
        cout<< res <<endl;
    }
    return 0;
}