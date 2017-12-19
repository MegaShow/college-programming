// MegaShow 2017.2.6

#include <cstdio>
#include <vector>
using namespace std;

int main(){
    vector <char> s;
    char c;
    while(~scanf("%c", &c)){
        if(s.empty() || s[s.size()-1] != c)
            s.push_back(c);
        else
            s.pop_back();
    }
    if(s.empty())
        printf("Empty String\n");
    else{
        for(int i = 0; i < s.size(); i++)
            printf("%c", s[i]);
        printf("\n");
    }
}
