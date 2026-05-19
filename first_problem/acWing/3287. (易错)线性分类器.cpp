/*
 3287. 线性分类器

      题目
      提交记录
      讨论
      题解
      视频讲解


考虑一个简单的二分类问题——将二维平面上的点分为 A 和 B 两类。

训练数据包含 n 个点，其中第 i 个点（1≤i≤n）可以表示为一个三元组 (xi,yi,typei)，即该点的横坐标、纵坐标和类别。

在二维平面上，任意一条直线可以表示为 θ0+θ1x+θ2y=0 的形式，即由 θ0、θ1 和 θ2 三个参数确定该直线，且满足 θ1、θ2 不同时为 0。

基于这 n 个已知类别的点，我们想要在平面上找到一条直线作为一个线性分类器。

具体来说，这条线要把训练数据中的 A、B 两类点完美分隔开来，即一侧只有 A 类点、另一侧只有 B 类点。

这样，对于任意一个的未知类别的点，我们就可以根据它是位于直线的哪一侧来预测它的类别了。

在本题中我们仅需要处理 m 个如下查询：

给定一条直线，判断它是否能将训练数据中的 A、B 两类点完美分开。
输入格式

输入共 n+m+1 行。

第一行包含用空格分隔的两个正整数 n 和 m，分别表示点和查询的个数。

第二行到第 n+1 行依次输入 n 个点的信息。第 i+1 行（1≤i≤n）包含用空格分隔的三项 xi、yi 和 typei，分别表示第 i 个点的横、纵坐标和类别，其中坐标为整数、类别为一个大写英文字母 A 或 B。

第 n+2 行到第 n+m+1 行依次输入 m 个查询。第 j+n+1 行（1≤j≤m）包含用空格分隔的三个整数 θ0、θ1 和 θ2，表示第 j 个查询中给定直线的三个参数。
输出格式

输出共 m 行，每行输出一个字符串。

第 j 行（1≤j≤m）输出的字符串对应第 j 个查询的结果：如果给定直线可以完美分隔 A、B 两类点，则输出 Yes，否则输出 No。
数据范围

输入数据保证不存在恰好落在给定直线上的点;
0<n≤103、0<m≤20，且 A、B 两类点的数量均不为 0;
所有点的坐标和给定直线的三个参数均为整数，且绝对值 ≤106;
任意两个点的坐标不完全相同。

QQ截图20210225130038.png
输入样例：

9 3
1 1 A
1 0 A
1 -1 A
2 2 B
2 3 B
0 1 A
3 1 B
1 3 B
2 0 A
0 2 -3
-3 0 2
-3 1 1

输出样例：

No
No
Yes

样例解释

只有第 3 个查询给出的直线能将 A、B 两类点完美分隔。


*/
/*
以下是错误的解法思路和代码，没有正确的考虑到溢出的情况：

    考虑到数学性质，在直线同一侧的点，代入后，
    计算出来符号是相同的
    不同侧的点，相互之间的叉乘一定是负数

核心错误：long long 乘法导致数据溢出

#include<iostream>
#include<vector>

using namespace std;
int main(){
    int n, m;
    cin>> n >> m;
    vector<vector<int>> arr;
    vector<vector<int>> brr;
    for(int i=0;i<n;i++){
        int x ,y; char c;
        cin >> x >> y >> c;
        if(c=='A'){
            arr.push_back(vector<int>{x, y});
        }
        else{
            brr.push_back(vector<int>{x, y});
        }
    }
    vector<vector<int>> line(m, vector<int>(3));
    for(int i=0;i<m;i++){
        cin >> line[i][0]>> line[i][1] >> line[i][2];
    }
    //对于每一条线，判断A ， B 之间的所有点是不是都是相互间叉乘为负数
    for(int i=0;i<m;i++){
        bool ok = true;
        int theta_0 = line[i][0], theta_1 = line[i][1], theta_2 = line[i][2];
        for(int j=0;j<arr.size();j++){
            int count_a = theta_0 + theta_1 * arr[j][0] + theta_2 * arr[j][1];
            for(int k=0;k<brr.size();k++){
                int count_b = theta_0 + theta_1 * brr[k][0] + theta_2 * brr[k][1];
                if(count_b * count_a >0){
                    ok = false;
                    break;
                }
            }
            if(!ok) break;
        }
        if(ok){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}
*/
