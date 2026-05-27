/*
 5298. 坐标变换（其二）

对于平面直角坐标系上的坐标 (x,y)，小 P 定义了如下两种操作：

    拉伸 k 倍：横坐标 x 变为 kx，纵坐标 y 变为 ky；
    旋转 θ：将坐标 (x,y) 绕坐标原点 (0,0) 逆时针旋转 θ 弧度（0≤θ<2π）。易知旋转后的横坐标为 xcosθ−ysinθ，纵坐标为 xsinθ+ycosθ。

设定好了包含 n 个操作的序列 (t1,t2,…,tn) 后，小 P 又定义了如下查询：

    i j x y：坐标 (x,y) 经过操作 ti,…,tj（1≤i≤j≤n）后的新坐标。

对于给定的操作序列，试计算 m 个查询的结果。
输入格式

输入共 n+m+1 行。

输入的第一行包含空格分隔的两个正整数 n 和 m，分别表示操作和查询个数。

接下来 n 行依次输入 n 个操作，每行包含空格分隔的一个整数（操作类型）和一个实数（k 或 θ），形如 1 k（表示拉伸 k 倍）或 2 θ（表示旋转 θ）。

接下来 m 行依次输入 m 个查询，每行包含空格分隔的四个整数 i、j、x 和 y，含义如前文所述。
输出格式

输出共 m 行，每行包含空格分隔的两个实数，表示对应查询的结果。

如果你输出的浮点数与参考结果相比，满足绝对误差不大于 0.1，则该测试点满分，否则不得分。
数据范围

1≤n,m≤105,
输入的坐标均为整数且绝对值不超过 106，
单个拉伸操作的系数 k∈[0.5,2],
任意操作区间 ti,…,tj（1≤i≤j≤n）内拉伸系数 k 的乘积在 [0.001,1000] 范围内。
输入样例：

10 5
2 0.59
2 4.956
1 0.997
1 1.364
1 1.242
1 0.82
2 2.824
1 0.716
2 0.178
2 4.094
1 6 -953188 -946637
1 9 969538 848081
4 7 -114758 522223
1 9 -535079 601597
8 8 159430 -511187

输出样例：

-1858706.758 -83259.993
-1261428.46 201113.678
-75099.123 -738950.159
-119179.897 -789457.532
114151.88 -366009.892

样例解释

第五个查询仅对输入坐标使用了操作八：拉伸 0.716 倍。

横坐标：159430×0.716=114151.88

纵坐标：−511187×0.716=−366009.892

由于具体计算方式不同，程序输出结果可能与真实值有微小差异，样例输出仅保留了三位小数。

*/

#include<vector>
#include<cmath>
#include<iostream>
using namespace std;

typedef long long ll ;
typedef long double ld ;

int main(){
    int n, m;
    cin>> n >> m;

    vector<ld> k_sum(n+1, 1);
    vector<ld> theta_sum(n+1, 0);
    for(int i=0; i<n;i++){
        int id =0;
        cin >> id;
        ld change_1 =1;
        ld change_2 =0;
        if(id==1){
            cin>> change_1;
        }else{
            cin>> change_2;
        }
        k_sum[i+1]= k_sum[i] * change_1;
        theta_sum[i+1]= theta_sum[i] + change_2;
    }     
    for(int k=0; k<m; k++){
        int i , j;
        cin >> i >> j;
        ld x , y;
        cin >> x >> y;
        ld k_sum_i_j = k_sum[j] / k_sum[i-1];
        ld theta_sum_i_j = theta_sum[j] - theta_sum[i-1];
        ld x_change = k_sum_i_j * (x* cos(theta_sum_i_j) - y* sin(theta_sum_i_j));
        ld y_change = k_sum_i_j * (x* sin(theta_sum_i_j) + y* cos(theta_sum_i_j));
        cout << x_change << " " << y_change << endl;
        // printf("%Lf %Lf\n", x_change, y_change);
    }
    return 0;
}