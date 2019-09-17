#include<bits/stdc++.h>
#include<stdio.h>
#include<iostream>

using namespace std;
int step[11];

int gcd(int a,int b)
{
    if(b==0)return a;
    else return gcd(b,a%b);
}
int check(int typeName , int target)
{
    int x = step[0];
    for(int i=1;i<typeName;i++){
        x = gcd(step[i],x);
    }
    return target%x==0;
}
int solve(int typeName , int target)
{
    queue<pair<int,int>> myQueue;
    myQueue.push(make_pair(0,0));
    set<int> passed;
    bool find=false;
    while(!myQueue.empty()){
        if(find) break;
        pair<int,int> frontpair = myQueue.front();
        int loc = frontpair.first;
        int num = frontpair.second;
        if(passed.find(loc)!=passed.end()) continue;
        passed.insert(loc);
        for(int i=0;i<typeName;i++){
            if(loc+step[i]==target||loc-step[i]==target){
                cout<<num+1<<endl;
                find = true;
                break;
            }
            myQueue.push(make_pair(loc+step[i],num+1));
            myQueue.push(make_pair(loc-step[i],num+1));
        }
    }
}
int main() {
    int testNum;
    cin >> testNum;


    for (int i=0; i<testNum; i++) {
        int typeNum, target;
        cin >> typeNum >> target;
        for (int j=0; j<typeNum; j++) {
            cin >> steps[j];
        }
        if (check(typeNum, target)) solve(typeNum, target);
        else cout << "-1" << endl;
    }
}
