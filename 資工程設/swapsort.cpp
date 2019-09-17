#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
using namespace std;
using State = vector<int>;
class SwapSort
{
private:
    set<list<State>> _paths;
    set<list<State>> _solutions;
    set<State> _explored;
public:
    SwapSort(State init)
    {
        list<State> ls;
        ls.push_back(init);
        _paths.insert(ls);
    }

    void show_solutions()
    {
        if (_solutions.size()==0) {
            cout << "No solution.\n";
        } else {
            for (auto p : _solutions) {
                for (auto s : p) {
                    for (auto i : s) {
                        cout << i << " ";
                    }
                    cout << "-> ";
                }
                cout << ".\n";
            }
        }
    }

    set<State> extend(State s);
    void solve(int steps);
};
/*
int isSorted(State s) {
    int before = s.front();
    for(auto i : s)
        if(before > i)
            return 0;
        else
        	before = i;
    return 1;
}*/
int isSorted(State s){
    int before = s.front();
    for(auto i :s){
        if(before>i) return 0;
        else{
            before = i;
        }
    }
    return 1;
}

set<State> SwapSort::extend(State s)
{
    /*set<State> SS;
    State temp;
    temp = s;

    temp[0] = temp[0] + temp[1];
    temp[1] = temp[0] - temp[1];
    temp[0] = temp[0] - temp[1];

    s.front() = s.front() + s.back();
    s.back() = s.front() - s.back();
    s.front() = s.front() - s.back();

    SS.insert(temp);
    SS.insert(s);
    // your code here

    return SS;*/
    set<State> SS;
    State tmp;
    tmp = s;

    tmp[0] = tmp[0] + tmp[1];
    tmp[1] = tmp[0] - tmp[1];
    tmp[0] = tmp[0] - tmp[1];

    s.front() = s.front() + s.back();
    s.back() = s.front() - s.back();
    s.front() = s.front() - s.back();
    SS.insert(tmp);
    SS.insert(s);
    return SS;
}

void SwapSort::solve(int steps)
{
    while (steps>0) {
        set<list<State>> oldPaths;
        set<list<State>> newPaths;

        for (auto p : _paths) {
            _explored.insert(p.back());
            auto nextstates = extend(p.back());
            for(auto s : nextstates){
                if(isSorted(s)){
                    auto np = p;
                    np.push_back(s);
                    _solutions.insert(np);
                }
                else{
                    auto search = _explored.find(s);
                    if(search == _explored.cend()){
                        auto np = p;
                        np.push_back(s);
                        newPaths.insert(np);
                    }
                }
            }
            oldPaths.insert(p);
            /*_explored.insert(p.back());
            auto nextstates = extend(p.back());
            for(auto s : nextstates){
                if(isSorted(s)){
                    auto np = p;
                    np.push_back(s);
                    _solutions.insert(np);
                }
                else{
                    auto search = _explored.find(s);
                    if(search == _explored.cend()){
                        auto np = p;
                        np.push_back(s);
                        newPaths.insert(np);
                    }
                }
            }
            oldPaths.insert(p);
            // your code here*/

        }

        for (auto p : oldPaths) {
            _paths.erase(p);
        }
        for (auto p : newPaths) {
            _paths.insert(p);
        }
        --steps;
    }
}


int main()
{
    State s;// = {2, 1, 3};
    int e;
    while (cin >> e) { // press Ctrl + Z to end the input
        s.push_back(e);
    }
    SwapSort prob1(s);
    prob1.solve(4);
    prob1.show_solutions();
    cout << "\n";
}

