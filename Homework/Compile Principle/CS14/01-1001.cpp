// 01-1001 MegaShow
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

//struct { int number; string str[10]; } keywords={3,"int","main","return"} ; //关键词
//struct { int number; string str[10]; } operators ={5,"+","*","=","+=","*="}; //运算符
//struct { int number; string str[10]; } boundaries ={6,"(",")","{","}",",",";"} ; //分界符
//struct { int number; string str[100];} identifieres={0}; //标识符
//struct { int number; string str[100];} Unsigned_integer={0}; //无符号整数

int expression(){
    std::vector < std::pair<int,int> > expr;
    std::vector <std::string> idname;
    std::vector <unsigned int> var;
    std::string str;
    bool flag_end = false;
    while(std::getline(std::cin, str) && flag_end == false){
        int index = 0;
        while(str[index] && flag_end == false){
            if(str[index] == '('){ expr.push_back(std::make_pair<int,int>(3,0)); index++; }
            else if(str[index]==')'){ expr.push_back(std::make_pair<int,int>(3,1)); index++; }
            else if(str[index]=='{'){ expr.push_back(std::make_pair<int,int>(3,2)); index++; }
            else if(str[index]=='}'){ expr.push_back(std::make_pair<int,int>(3,3)); index++; }
            else if(str[index]==','){ expr.push_back(std::make_pair<int,int>(3,4)); index++; }
            else if(str[index]==';'){ expr.push_back(std::make_pair<int,int>(3,5)); index++; }
            else if(str[index]=='+' && str[index+1]=='='){ expr.push_back(std::make_pair<int,int>(2,3)); index+=2; }
            else if(str[index]=='*' && str[index+1]=='='){ expr.push_back(std::make_pair<int,int>(2,4)); index+=2; }
            else if(str[index]=='+'){ expr.push_back(std::make_pair<int,int>(2,0)); index++; }
            else if(str[index]=='*'){ expr.push_back(std::make_pair<int,int>(2,1)); index++; }
            else if(str[index]=='='){ expr.push_back(std::make_pair<int,int>(2,2)); index++; }
            else if(str.compare(index,3,"int")==0){ expr.push_back(std::make_pair<int,int>(1,0)); index+=3; }
            else if(str.compare(index,4,"main")==0){ expr.push_back(std::make_pair<int,int>(1,1)); index+=4; }
            else if(str.compare(index,6,"return")==0){ expr.push_back(std::make_pair<int,int>(1,2)); index+=6; }
            else if(isalpha(str[index]) || str[index] == '_'){
                expr.push_back(std::make_pair<int,int>(4,idname.size()));
                idname.push_back(std::string(1,str[index++]));
                while(isalpha(str[index]) || isdigit(str[index]) || str[index] == '_')
                    idname[idname.size()-1] += str[index++];
                for(int i = 0; i < idname.size() - 1; i++){
                    if(idname[idname.size()-1].compare(idname[i]) == 0){
                        expr[expr.size()-1].second = i;
                        idname.pop_back();
                        break;
                    }
                }
            }
            else if(isdigit(str[index])){
                expr.push_back(std::make_pair<int,int>(5,var.size()));
                var.push_back((int)(str[index++]-'0'));
                while(isdigit(str[index]))
                    var[var.size()-1] = var[var.size()-1] * 10 + str[index++] - '0';
                for(int i = 0; i < var.size() - 1; i++){
                    if(var[var.size()-1] == var[i]){
                        expr[expr.size()-1].second = i;
                        var.pop_back();
                        break;
                    }
                }
            }
            else if(str[index] == '#')
                flag_end = true;
            else
                index++;
        }
    }
    for(int i = 0; i < expr.size(); i++){
        std::cout << "<" << expr[i].first << "," << expr[i].second << ">";
    }
    std::cout << std::endl << "identifieres:";
    for(int i = 0; i < idname.size()-1; i++)
        std::cout << idname[i] << " ";
    if(idname.size())
        std::cout << idname[idname.size()-1] << std::endl;
    std::cout << "Unsigned_integer:";
    for(int i = 0; i < var.size()-1; i++)
        std::cout << var[i] << " ";
    if(var.size())
        std::cout << var[var.size()-1] << std::endl;
}

int main(){
    expression();
}
