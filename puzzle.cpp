#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
void printMatrix(vector<string>& matrix, int n)
{
    for (int i = 0; i < n; i++)
        cout << matrix[i] << endl;
}
vector<string>checkvertical(int x,int y,vector<string>crossword,string word){
    int n=word.size();
    for(int i=0;i<n;i++){
        if(crossword[x+i][y]=='-' || crossword[x+i][y]==word[i])
            crossword[x+i][y]==word[i]  ;
        else{
            crossword[0][0]='@';
            return crossword;

        }

    }
    return crossword;

}
vector<string>checkHoriz(int x,int y,vector<string>crossword,string word){
    int n=word.size();
    for(int i=0;i<n;i++){
        if(crossword[x][y+i]=='-' || crossword[x][y+i]==word[i])
            crossword[x][y+i]==word[i]  ;
        else{
            crossword[0][0]='@';
            return crossword;

        }

    }
    return crossword;

}

vector<string> solve(vector<string>crossword,vector<string>&word,int n,int index){
    if(index<word.size()){
        int maxL=n-word[index].length();
        string current=word[index];
        for(int i=0;i<n;i++){
            for(int j=0;j<maxL;j++){
                    vector<string>temp=checkvertical(j,i,crossword,current);
                    if(temp[0][0]!='@')
                        solve(temp,word,n,index+1);
            }
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<maxL;j++){
                    vector<string>temp=checkHoriz(i,j,crossword,current);
                    if(temp[0][0]!='@')
                        solve(temp,word,n,index+1);
            }
        }

    }
    else{
        return crossword;

    }

}
vector<string> crosswordPuzzle(vector<string> crossword, string words) {
   vector<string>word;
    string s="";
    for(int i=0;i<words.size();i++){
        if(words[i]==";"){
            word.push_back(s);
            s="";
        }
        else{
            s+=words[i];
        }

    }


   return solve(crossword,word,crossword.size(),0);

}
int main(){

    int n1 = 10;
    vector<string> matrix;
    matrix.push_back("*#********");
    matrix.push_back("*#********");
    matrix.push_back("*#****#***");
    matrix.push_back("*##***##**");
    matrix.push_back("*#****#***");
    matrix.push_back("*#****#***");
    matrix.push_back("*#****#***");
    matrix.push_back("*#*######*");
    matrix.push_back("*#********");
    matrix.push_back("***#######");
    string words="PUNJAB;JHARKHAND,MIZORAM,MUMBAI";
    vector<string>ans=crosswordPuzzle(matrix,words);
    printMatrix(ans,n1);


    return 0;
}
