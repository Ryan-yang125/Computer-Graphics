#include<bits/stdc++.h>
using namespace std;
int main() {
    // std::string s = "f -129/-129/-129 -117/-117/-117 -18/-18/-18";
    // std::string delimiter = "/";
    // string s1 = "";
    // size_t pos = 0;
    // std::string token;
    // while ((pos = s.find(delimiter)) != std::string::npos) {
        // token = s.substr(0, pos);
        // s1.append(token);
        // s.erase(0, pos + delimiter.length());
    // }
    // cout << s1 << endl;
    // pos = 0;
    // delimiter = " ";
    // std::string s2 = "";
    // while ((pos = s1.find(delimiter)) != std::string::npos) {
        // token = s1.substr(0, pos);
        // cout << token << endl;
        // s2.append(token);
        // s1.erase(0, pos + delimiter.length());
    // }
    
    // std::cout << s2 << std::endl;
std::string line = "f -129/-129/-129 -117/-117/-117 -18/-18/-18";
            int u, v, w;
            string delimiter = "/";
            line = line.substr(2);
            int index = 0;
            string token1 = line.substr(0, line.find(delimiter));
            u = abs(stoi(token1));
            index = token1.size() * 3 + 3;
            line = line.substr(index);
            string token2 = line.substr(0, line.find(delimiter));
            v = abs(stoi(token2));
            index = token2.size() * 3 + 3;
            line = line.substr(index);
            string token3 = line.substr(0, line.find(delimiter));
            w = abs(stoi(token3));
            cout << token1 << endl << token2 << endl << token3 << endl;
            // cout << u << endl << v << endl << w;
}