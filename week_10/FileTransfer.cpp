/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 FileTransfer.cpp
* @version:
* @Time: 		 2015-11-27 13:10:53
* @Description:  use find-union set to implement sets
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

using namespace std;

class Networks
{
private:
	vector<int> _networks;
	int _numberOfNetworks;
public:
	Networks(int numberOfNetworks): _networks(numberOfNetworks, -1), _numberOfNetworks{numberOfNetworks} {}
	~Networks() {}
	void setUpConnection();//union
	void checkConnection();
	void terminateAndCheckNetworkConnection();
	int findBelongingNetwork(int computer);//find
};

void Networks::setUpConnection() {
	int computer1, computer2;
	cin >> computer1 >> computer2;
	int network1 = findBelongingNetwork(computer1);
	int network2 = findBelongingNetwork(computer2);
	if (network1 != network2) {
		if (_networks[network1] <= _networks[network2]) {
			_networks[network1] += _networks[network2];
			_networks[network2] = network1;
		} else {
			_networks[network2] += _networks[network1];
			_networks[network1] = network2;
		}
		--_numberOfNetworks;
	}
}
void Networks::checkConnection() {
	int computer1, computer2;
	cin >> computer1 >> computer2;
	int network1 = findBelongingNetwork(computer1);
	int network2 = findBelongingNetwork(computer2);
	if (network1 == network2)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
}
void Networks::terminateAndCheckNetworkConnection() {
	if (_numberOfNetworks == 1)
		cout << "The network is connected." << endl;
	else
		cout << "There are " << _numberOfNetworks << " components." << endl;
}
int Networks::findBelongingNetwork(int computer) {
	if (_networks[computer] < 0)
		return computer;
	else
		return _networks[computer] = findBelongingNetwork(_networks[computer]);
}

int main() {
	// freopen("test.in", "r", stdin);
	// freopen("test.out", "w", stdout);
	int numberOfNetworks;
	cin >> numberOfNetworks;
	Networks networks(numberOfNetworks);

	char cmd;
	bool terminated = false;

	while (!terminated) {
		cin >> cmd;
		switch (cmd) {
		case 'I' : networks.setUpConnection() ; break;
		case 'C' : networks.checkConnection() ; break;
		case 'S' : networks.terminateAndCheckNetworkConnection(); terminated = true ; break;
		}
	}

	// cout << endl;
	// system("pause");
	return 0;
}
