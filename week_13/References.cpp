/*2015.7.14cyq*/
#include <iostream>
#include <vector>
#include <map>
using namespace std;
//拓扑排序
struct node {
    int num;//结点数值
    int degree;//结点的入度，表示当前位置与首次哈希位置的偏移值，即冲突次数
    vector<int> next;//后继结点
};
int main() {
    int N;
    cin >> N;
    map<int, int> map;
    int count = 0;
    vector<node> a(N);
    for (int i = 0; i < N; i++) { //结点序号0到N-1
        cin >> a[i].num;
        if (a[i].num >= 0) {
            count++;//有效结点的个数，用于输出控制
            if (a[i].num % N == i) { //一次命中，入度为0
                a[i].degree = 0;
                map[a[i].num] = i; //数值为key，自动升序排列，便于直接找到最小值,位置为value
            } else {
                a[i].degree = ((i + N) - a[i].num % N) % N; //与首次hash的偏移值，即线性探测的次数
                int k = a[i].degree;
                while (k) {
                    a[(i - k + N) % N].next.push_back(i); //该结点push到所有前驱结点的next数组
                    k--;
                }
            }
        }
    }
    while (!map.empty()) { //map中存储所有入度为0的结点
        auto it = map.begin();
        cout << it->first << (--count ? " " : ""); //first是结点数值，second是结点序号
        for (auto index = a[it->second].next.begin(); index != a[it->second].next.end(); index++) {
            a[*index].degree--;//所有后继节点入度减1
            if (a[*index].degree == 0)
                map[a[*index].num] = *index;
        }
        map.erase(it);
    }

    return 0;
}
