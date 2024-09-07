#include<iostream>
#include<string>
#include<vector>
using namespace std;

void replaceKey(string& str,const string& a,const string& b) {
    for(int p=str.find(a); ~p; p=str.find(a,p)){
        str.erase(p,a.size());
        str.insert(p,b);
        p+=b.size();
    }
}



int main() {
    string str;
    vector<string> que;
    while(getline(cin,str)){
        replaceKey(str,"\t","    ");
        replaceKey(str,"\\","\\\\");
        replaceKey(str,"\"","\\\"");
        que.push_back(str);
    }
    for(auto str:que){
        cout<<"\t\t\t\""<<str<<"\",\n";
    }
    // cout.flush();
    // system("pause");
    return 0;
}
/*




 */
