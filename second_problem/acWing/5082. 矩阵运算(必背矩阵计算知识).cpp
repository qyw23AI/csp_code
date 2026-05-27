/*
 5082. 矩阵运算

Softmax(Q×KTd√)×V 是 Transformer 中注意力模块的核心算式，其中 Q、K 和 V 均是 n 行 d 列的矩阵，KT 表示矩阵 K 的转置，× 表示矩阵乘法。

为了方便计算，顿顿同学将 Softmax 简化为了点乘一个大小为 n 的一维向量 W：

(W⋅(Q×KT))×V

点乘即对应位相乘，记 W(i) 为向量 W 的第 i 个元素，即将 (Q×KT) 第 i 行中的每个元素都与 W(i) 相乘。

现给出矩阵 Q、K 和 V 和向量 W，试计算顿顿按简化的算式计算的结果。
输入格式

输入的第一行包含空格分隔的两个正整数 n 和 d，表示矩阵的大小。

接下来依次输入矩阵 Q、K 和 V。每个矩阵输入 n 行，每行包含空格分隔的 d 个整数，其中第 i 行的第 j 个数对应矩阵的第 i 行、第 j 列。

最后一行输入 n 个整数，表示向量 W。
输出格式

输出共 n 行，每行包含空格分隔的 d 个整数，表示计算的结果。
数据范围

70% 的测试数据满足：1≤n≤100 且 1≤d≤10；输入矩阵、向量中的元素均为整数，且绝对值均不超过 30。
全部的测试数据满足：1≤n≤104 且 1≤d≤20；输入矩阵、向量中的元素均为整数，且绝对值均不超过 1000。
输入样例：

3 2
1 2
3 4
5 6
10 10
-20 -20
30 30
6 5
4 3
2 1
4 0 -5

输出样例：

480 240
0 0
-2200 -1100


*/

#include<vector>
#include<iostream>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
    int n, d;
    cin >> n >> d;
    vector<vector<ll>> Q(n,vector<ll>(d,0));
    vector<vector<ll>> K(n,vector<ll>(d,0));
    vector<vector<ll>> V(n,vector<ll>(d,0));
    vector<ll> W(n,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<d;j++){
            cin>> Q[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<d;j++){
            cin>> K[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<d;j++){
            cin>> V[i][j];
        }
    }
    for(int i=0;i<n;i++){
        cin>> W[i];
    }
    //从右向左进行计算，减少计算复杂度和中间结果的大小
    //如果是按从左到右的计算，为O(n*n*d)
    //如果是从右向左计算，为O(d*d* n),时间复杂度和空间复杂度指数级下降
    vector<vector<ll>> B(d,vector<ll>(d,0));
    //计算K_T x V
    for(int i=0;i<d;i++){
        for(int k=0;k<n;k++){
            for(int j=0;j<d;j++){
                //技巧二： 矩阵转置不需要进行真的转置，只需要取用的时候转置
                B[i][j] += K[k][i] * V[k][j];
            }
        }
    }
    //计算 W . Q x B
    vector<vector<ll>> R(n,vector<ll>(d,0));
    for(int i=0;i<n;i++){   
        for(int k=0;k<d;k++){
            for(int j=0;j<d;j++){
                R[i][j] += W[i] * Q[i][k] * B[k][j]; 
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<d;j++){
            cout<< R[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}