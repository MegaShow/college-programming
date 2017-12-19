// MegaShow

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
using namespace std;

int main() {
    int n;
    string qq;
    string ip;
    cin >> n;
    map<string, set<string> > ip_qq;
    map<string, set<string> > qq_ip;
    for (int i = 0; i < n; i++) {
        cin >> qq >> ip;
        ip_qq[ip].insert(qq);
        qq_ip[qq].insert(ip);
    }
    cin >> ip >> qq;
    set<string>::iterator it = ip_qq[ip].begin();
    set<string>::iterator it_end = ip_qq[ip].end();
    if (it == it_end) {
        cout << "no qq" << endl;
    } else {
        cout << ip << " ==> [ ";
        while (it != it_end) {
            cout << *it << ' ';
            it++;
        }
        cout << ']' << endl;
    }
    it = qq_ip[qq].begin();
    it_end = qq_ip[qq].end();
    if (it == it_end) {
        cout << "no ip" << endl;
    } else {
        cout << qq << " ==> [ ";
        while (it != it_end) {
            cout << *it << ' ';
            it++;
        }
        cout << ']' << endl;
    }
}