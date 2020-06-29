#include<bits/stdc++.h>
using namespace std;
string line = "f 20869/24852/3707 20870/33647/3707 20871/29687/3708 ";
int main() {
    // std::string s = "-20869/-24852/-3707 -20870/-33647/-3707 -20871/-29687/-3708";
    // std::string delimiter = " ";
    // for (auto x : s) {
        
    // }
    // size_t pos = 0;
    // std::string token;
    // string s1 = "";
    // while ((pos = s.find(delimiter)) != std::string::npos) {
        // token = s.substr(0, pos);
        // std::cout << token << std::endl;
        // s.erase(0, pos + delimiter.length());
    // }
    // std::cout << s << std::endl;
        
            vector<int> vIndexSets;
            int vertexindex[3];
            string s = line.substr(2);
            std::string delimiter = " ";

            size_t pos = 0;
            std::string token;
            vector<string> pis;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                pis.push_back(token);
                s.erase(0, pos + delimiter.length());
            }
            pis.push_back(s);
            for (int i = 0; i < 3; ++i) {
               
                string tmp = pis[i].substr(0, pis[i].find('/'));
                vertexindex[i] = stoi(tmp);
                cout << vertexindex[i] << endl;
            }
}