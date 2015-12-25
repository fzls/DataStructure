/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 test.cpp
* @version:
* @Time:
* @Description:
*
+----------------------------------------------------------
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

#include "HashTable.h"

using namespace std;



int main() {
	freopen("test_2.in", "r", stdin);
	freopen("test.in", "w", stdout);
	clock_t _time = clock();
	default_random_engine _e(_time);

	int nums = 100 + _e() % 20;
	cout << nums << endl;
	HashTableWithOpenAddressing table(nums);
	vector<int> input(nums, 0) ;
	for (int i = 0; i < nums; ++i) {
		input[i] = (i == 0 ? _e() % RANGE : input[i - 1] + (_e() % RANGE));
		table.Insert(input[i]);
	}

	table.Print();
	cout << endl;
	for (auto k : input)
		cout << k << ' ';

	system("pause");
	return 0;
}
