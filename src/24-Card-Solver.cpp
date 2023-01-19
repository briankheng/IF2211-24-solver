#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

bool valid;
set<string>ans;
vector<string>cards;
string ops[4]={"+","-","*","/"},validCards[13]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"},choice,inp;

double operation(double card1,double card2,string op){
    if(op=="+")return card1+card2;
    else if(op=="-")return card1-card2;
    else if(op=="*")return card1*card2;
    else if(op=="/")return card1/card2;
}

void solve(vector<string>eq){
    // Case 1: ((1 op 2) op 3) op 4
    if(abs(operation(operation(operation(stod(eq[0]),stod(eq[2]),eq[1]),stod(eq[4]),eq[3]),stod(eq[6]),eq[5])-24)<=1e-7){
        ans.insert("(("+eq[0]+" "+eq[1]+" "+eq[2]+") "+eq[3]+" "+eq[4]+") "+eq[5]+" "+eq[6]);
    }
    // Case 2: (1 op 2) op (3 op 4)
    if(abs(operation(operation(stod(eq[0]),stod(eq[2]),eq[1]),operation(stod(eq[4]),stod(eq[6]),eq[5]),eq[3])-24)<=1e-7){
        ans.insert("("+eq[0]+" "+eq[1]+" "+eq[2]+") "+eq[3]+" ("+eq[4]+" "+eq[5]+" "+eq[6]+")");
    }
    // Case 3: (1 op (2 op 3)) op 4
    if(abs(operation(operation(stod(eq[0]),operation(stod(eq[2]),stod(eq[4]),eq[3]),eq[1]),stod(eq[6]),eq[5])-24)<=1e-7){
        ans.insert("("+eq[0]+" "+eq[1]+" ("+eq[2]+" "+eq[3]+" "+eq[4]+")) "+eq[5]+" "+eq[6]);
    }
    // Case 4: 1 op ((2 op 3) op 4)
    if(abs(operation(stod(eq[0]),operation(operation(stod(eq[2]),stod(eq[4]),eq[3]),stod(eq[6]),eq[5]),eq[1])-24)<=1e-7){
        ans.insert(eq[0]+" "+eq[1]+" (("+eq[2]+" "+eq[3]+" "+eq[4]+") "+eq[5]+" "+eq[6]+")");
    }
}

void backtrack(vector<string>eq,int idx){
    if(idx==4){
        solve(eq);
        return;
    }
    for(auto op:ops){
        eq.push_back(op);eq.push_back(cards[idx]);
        backtrack(eq,idx+1);
        eq.pop_back();eq.pop_back();
    }
}

vector<string>tokenize(string s){
    vector<string>tokens;
    string cur="";
    for(auto it:s){
        if(it==' '){
            tokens.push_back(cur);
            cur="";
        }
        else cur+=it;
    }
    tokens.push_back(cur);
    return tokens;
}

int main()
{
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    // INPUT
    cout<<"~~~ Selamat Datang Di Permainan Kartu 24! ~~~\n\n";

    cout<<"1. Input dari pengguna\n2. Input auto-generate\n\nMasukan pilihan: ";
    getline(cin,choice);

    while(choice!="1"&&choice!="2"){
        cout<<"\nMasukkan tidak sesuai!\nMasukan pilihan: ";
        getline(cin,choice);
    }

    // TAKE CARD
    if(choice=="1"){
        do{
            valid=true;
            cout<<"\nPilihan Kartu:\n";
            getline(cin,inp);
            cards=tokenize(inp);
            if(cards.size()==4){
                for(int i=0;i<4;i++){
                    if(cards[i]=="2"||cards[i]=="3"||cards[i]=="4"||cards[i]=="5"||cards[i]=="6"||
                       cards[i]=="7"||cards[i]=="8"||cards[i]=="9"||cards[i]=="10")continue;
                    else if(cards[i]=="A")cards[i]="1";
                    else if(cards[i]=="J")cards[i]="11";
                    else if(cards[i]=="Q")cards[i]="12";
                    else if(cards[i]=="K")cards[i]="13";
                    else valid=false;
                }
            }
            else valid=false;
            if(!valid){
                cout<<"\nMasukkan tidak sesuai!"<<endl;
            }
        }while(!valid);
    }
    else{
        cout<<"\nPilihan Kartu:\n";
        for(int i=0;i<4;i++){
            cards[i]=validCards[rnd()%13];
            cout<<cards[i]<<' ';
            if(cards[i]=="A")cards[i]="1";
            else if(cards[i]=="J")cards[i]="11";
            else if(cards[i]=="Q")cards[i]="12";
            else if(cards[i]=="K")cards[i]="13";
        }
        cout<<endl;
    }

    // FIND SOLUTION
    sort(cards.begin(),cards.end());

    do{
        backtrack({cards[0]},1);
    }while(next_permutation(cards.begin(),cards.end()));

    if(ans.empty()){
        cout<<"\nTidak ada jawaban!"<<endl;
    }
    else{
        cout<<"\n"<<ans.size()<<' '<<"Solutions found!"<<endl<<endl;
        for(auto it:ans)cout<<it<<endl;
    }
    return 0;
}
