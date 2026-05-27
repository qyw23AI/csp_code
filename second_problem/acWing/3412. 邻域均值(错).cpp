/*
 3412. 邻域均值

      题目
      提交记录
      讨论
      题解
      视频讲解


顿顿在学习了数字图像处理后，想要对手上的一副灰度图像进行降噪处理。

不过该图像仅在较暗区域有很多噪点，如果贸然对全图进行降噪，会在抹去噪点的同时也模糊了原有图像。

因此顿顿打算先使用邻域均值来判断一个像素是否处于较暗区域，然后仅对处于较暗区域的像素进行降噪处理。

待处理的灰度图像长宽皆为 n 个像素，可以表示为一个 n×n 大小的矩阵 A，其中每个元素是一个 [0,L) 范围内的整数，表示对应位置像素的灰度值。

对于矩阵中任意一个元素 Aij（0≤i,j<n），其邻域定义为附近若干元素的集和：

Neighbor(i,j,r)={Axy|0≤x,y<n and |x−i|≤r and |y−j|≤r}

这里使用了一个额外的参数 r 来指明 Aij 附近元素的具体范围。

根据定义，易知 Neighbor(i,j,r) 最多有 (2r+1)2 个元素。

如果元素 Aij 邻域中所有元素的平均值小于或等于一个给定的阈值 t，我们就认为该元素对应位置的像素处于较暗区域。

下图给出了两个例子，左侧图像的较暗区域在右侧图像中展示为黑色，其余区域展示为白色。

1.png

现给定邻域参数 r 和阈值 t，试统计输入灰度图像中有多少像素处于较暗区域。
输入格式

输入共 n+1 行。

输入的第一行包含四个用空格分隔的正整数 n、L、r 和 t，含义如前文所述。

第二到第 n+1 行输入矩阵 A。第 i+2（0≤i<n）行包含用空格分隔的 n 个整数，依次为 Ai0,Ai1,⋯,Ai(n−1)。
输出格式

输出一个整数，表示输入灰度图像中处于较暗区域的像素总数。
数据范围

70% 的测试数据满足 n≤100、r≤10。
全部的测试数据满足 0<n≤600、0<r≤100 且 2≤t<L≤256。
输入样例1：

4 16 1 6
0 1 2 3
4 5 6 7
8 9 10 11
12 13 14 15

输出样例1：

7

输入样例2：

11 8 2 2
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 7 0 0 0 7 0 0 7 7 0
7 0 7 0 7 0 7 0 7 0 7
7 0 0 0 7 0 0 0 7 0 7
7 0 0 0 0 7 0 0 7 7 0
7 0 0 0 0 0 7 0 7 0 0
7 0 7 0 7 0 7 0 7 0 0
0 7 0 0 0 7 0 0 7 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0

输出样例2：

83


*/

/*
正确的二维矩阵前缀和计算方式如下：
      s[i][j]表示 a[0][0]到a[i-1][j-1]的数据总和
      前缀和计算公式：
      s[i][j]= s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i-1][j-1];
      区间矩阵和计算公式：
      x1,y1,x2,y2的计算如下：
      sum = s[x2+1][y2+1] - s[x2+1][y1] - s[x1][y2+1] + s[x1][y1];

*/
#include<iostream>
#include<vector>
using namespace std;

int main(){
      //输入
      int n,L,r,t;
      cin>> n >> L >> r >> t;
      vector<vector<int>> matrix(n, vector<int>(n,0));
      for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                  cin>> matrix[i][j];
            }
      }
      //计算前缀和
      vector<vector<long>> s(n+1, vector<long>(n+1,0));
      for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                  s[i][j]= s[i][j-1]+s[i-1][j]- s[i-1][j-1]+ matrix[i-1][j-1];
            }
      }
      //计算子矩阵
      int res_count =0;
      for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                  int x1 = max(0, i-r);
                  int y1 = max(0, j-r);
                  int x2 = min(n-1, i+r);
                  int y2 = min(n-1, j+r);
                  //计算子矩阵
                  long sum = s[x2+1][y2+1] - s[x2+1][y1] -s[x1][y2+1] +s[x1][y1];
                  //计算总元素个数
                  int count = (y2 -y1+1)* ( x2-x1+1);
                  //计算总值大小
                  int num = count*t;
                  if(sum<= num){
                        res_count++;
                  }
            }
      }
      cout<< res_count;
      return 0;
}
/*
 二维矩阵前缀和，计算一个二维矩阵A，表示（0,0）到（i，j）构成的矩阵的和
 之后求中间某个矩阵时，就可以转化为前缀和矩阵的减法操作
 如求 （x1,y1）(x2,y2)就可以化为A（x2,y2） - A(x2, y1) - A(x1,y2) + A(x1,y1)
 边界处理：
      x1<0,y1<0: 等于A(x2,y2)
      x1<0,y1>0: 等于A(x2,y2) - A(x2,y1)
      x1<0,0<y1<n,0<x2<n,y2>n: 等于A(x2,n) -A(x2,y1)
      0<x1<n,0<y1<n, 0<x2<n,y2>n: 等于 A(x2,n)-A(x2,y1)-A(x1,n) + A(x1,y1)

// 下面是错误的二维前缀和计算方法，时间复杂度达到了惊人的N^4

// #include<iostream>
// #include<vector>
// using namespace std;

// int main(){
//       //读数据构建输入矩阵
//       int n, L, r, t;
//       cin >> n >> L >> r >> t;
//       vector<vector<int>> res(n, vector(n,0));
//       for(int i=0;i<n;i++){
//             for(int j=0;j<n;j++){
//                   cin>> res[i][j];
//             }
//       }
//       //计算并保存二维前缀和 O(n^2 * i*j)
//       vector<vector<long>> sum_matrix(n, vector<long>(n,0));
//       for(int i=0;i<n;i++){
//             for(int j=0;j<n;j++){
//                   for(int k1=0;k1<=i;k1++){
//                         for(int k2=0;k2<=j;k2++){
//                               sum_matrix[i][j]+= res[k1][k2];
//                         }
//                   }
//             }
//       }
//       //计算每个数的邻域矩阵的值，并进行判断
//       int res_count = 0;
//       for(int i=0;i<n;i++){
//             for(int j=0;j<n;j++){
//                   double near_num =0.0;
//                   int x1 = i-r;int y1 = j-r;
//                   int x2 = i+r;int y2 = j+r;
//                   //进行边界逻辑判断后，确定A（x2,y2） - A(x2, y1) - A(x1,y2) + A(x1,y1)
//                   if(x2>=n){
//                         x2 = n-1;
//                   }
//                   if(y2>=n){
//                         y2 = n-1;
//                   }
//                   long  A_x2_y2 = sum_matrix[x2][y2];
//                   long A_x2_y1 = 0;
//                   long A_x1_y2 = 0;
//                   long A_x1_y1 = 0;
//                   if(y1>0){
//                         A_x2_y1 = sum_matrix[x2][y1-1];
//                   }
//                   if(x1>0){
//                         A_x1_y2 = sum_matrix[x1-1][y2];
//                   }
//                   if(x1>0 && y1>0){
//                         A_x1_y1 = sum_matrix[x1-1][y1-1];
//                   }
//                   //使用二维前缀和计算出邻域矩阵的总数
//                   long near_sum = A_x2_y2 - A_x1_y2 - A_x2_y1 + A_x1_y1;
//                   //计算这个邻域矩阵中一共有多少个像素
//                   double count =1;
//                   x1 = x1<0? 0: x1;
//                   y1 = y1<0? 0: y1;
//                   int row = x2 - x1 +1;
//                   int col = y2 -y1 +1;
//                   count = row * col;
//                   near_num = near_sum / count;
//                   if(near_num <= t){
//                         res_count ++;
//                   }
//             }
//       }
//       cout<< res_count;
//       return 0;
// }

 */

