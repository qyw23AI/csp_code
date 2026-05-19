/*
 5415. 仓库规划

      题目
      提交记录
      讨论
      题解
      视频讲解


西西艾弗岛上共有 n 个仓库，依次编号为 1∼n。

每个仓库均有一个 m 维向量的位置编码，用来表示仓库间的物流运转关系。

具体来说，每个仓库 i 均可能有一个上级仓库 j，满足：仓库 j 位置编码的每一维均大于仓库 i 位置编码的对应元素。

比如编码为 (1,1,1) 的仓库可以成为 (0,0,0) 的上级，但不能成为 (0,1,0) 的上级。

如果有多个仓库均满足该要求，则选取其中编号最小的仓库作为仓库 i 的上级仓库；如果没有仓库满足条件，则说明仓库 i 是一个物流中心，没有上级仓库。

现给定 n 个仓库的位置编码，试计算每个仓库的上级仓库编号。
输入格式

输入共 n+1 行。

输入的第一行包含两个正整数 n 和 m，分别表示仓库个数和位置编码的维数。

接下来 n 行依次输入 n 个仓库的位置编码。其中第 i 行（1≤i≤n）包含 m 个整数，表示仓库 i 的位置编码。
输出格式

输出共 n 行。

第 i 行（1≤i≤n）输出一个整数，表示仓库 i 的上级仓库编号；如果仓库 i 没有上级，则第 i 行输出 0。
数据范围

50% 的测试数据满足 m=2；
全部的测试数据满足 0<m≤10、0<n≤1000，且位置编码中的所有元素均为绝对值不大于 106 的整数。
输入样例：

4 2
0 0
-1 -1
1 2
0 -1

输出样例：

3
1
0
3

样例解释

对于仓库 2：(−1,−1) 来说，仓库 1：(0,0) 和仓库 3：(1,2) 均满足上级仓库的编码要求，因此选择编号较小的仓库 1 作为其上级。
难度： 简单
时/空限制： 1s / 512MB
总通过数： 5444
总尝试数： 9941
来源：
第32次CCF-CSP计算机软件能力认证
算法标签

*/

//简单的暴力解法，时间复杂度O(N^2*m)，每个仓库都要和所有仓库进行比较
#include<iostream>
#include<vector>
using namespace std;
int main(){
	int n, m;
	cin>>n >> m;
	vector<vector<int>> arr(n, vector<int>(m));
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin >> arr[i][j];
		}
	}
	//进行枚举
	vector<int> up_id(n, 0);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			bool ok = true;
			for(int k=0;k<m;k++){
				if(arr[i][k]>=arr[j][k]){
					ok = false;
					break;
				}
			}
			if(ok){
				cout<<j+1<<endl;
				break;
			}else{
				if(j==n-1){
					cout<<0<<endl;
				}
			}
		}
	}
	return 0;
}
/* 这里使用复杂的剪枝方法，但是没有提高效率，反而更慢了，时间复杂度仍然是O(N!*m)，因为每个仓库都要和所有总和更大的仓库进行比较
并且打乱了编号，明明可以直接找打最小的编号，反而要找总和更大的编号，增加了复杂度
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//结构体排序，排序的比较函数是和更大的放后面，要每个编号 都大于，则总和一定大于
//并且编号最小的优先
//遍历所有总和更大的数的所有情况，并且选择出其中满足条件的最小编号 
struct Repository{
	vector<int> arr;
	int id;
	int sum;
	Repository(vector<int>& a, int id, int sum):arr(a), id(id), sum(sum){}
};

int main(){
	int n, m;
	cin>>n >> m;
	vector<Repository> r;
	for(int i=1;i<=n;i++){
		vector<int> a;
		int sum=0;
		for(int j=1;j<=m;j++){
			int x=0;
			cin >> x;
			sum += x;
			a.push_back(x); 
		}
		r.emplace_back(a, i, sum);   
	}
	sort(r.begin() , r.end() , [](const Repository& a, const Repository& b){
		return a.sum < b.sum;
	});
	//��С����������вֿ������O(N!*m)
	vector<int> up_r(n, 0); //ȫ����ʼ��Ϊ��ת�ֿ� 
	for(int i=0;i<n;i++){
		//�Ƚ����п��ܣ��ҵ���С���
		int min_id = n+1;
		for(int j=i+1; j<n;j++){
			bool ok = true;
			for(int k=0;k<m;k++){
				if(r[i].arr[k]>=r[j].arr[k]){
					ok = false;
					break;
				}			
			}
			if(ok){
				if(min_id>r[j].id){
					min_id = r[j].id;
					up_r[r[i].id-1]=min_id;
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<up_r[i]<<endl;
	}
	return 0;
} 

*/

