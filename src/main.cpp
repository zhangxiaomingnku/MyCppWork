#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>


using namespace::std;

int egg_drop0(std::vector<std::vector<int>> &T, int k, int n) {
    // k eggs, n floors
    // eggs and floors, 1-base; index 0-base
    int m = n;
    int p, q;
    int candidate;
    if(k==1) {
        return n;
    }
    if(n==1) {
        return 1;
    }
    else{
        for(int i=1; i<n+1; ++i) {
            // if it breaks
            if(i==1) {
                p = 0;
                if(T[k-1][n-i-1]==0){
                    T[k-1][n-i-1] = egg_drop0(T, k, n-i);
                }
                q = T[k-1][n-i-1];
            }else if(i==n) {
                if(T[k-2][i-1-1]==0){
                    T[k-2][i-1-1] = egg_drop0(T, k-1, i-1);
                }
                p = T[k-2][i-1-1];
                q = 0;
            }else {
                if(T[k-2][i-1-1]==0){
                    T[k-2][i-1-1] = egg_drop0(T, k-1, i-1);
                }
                p = T[k-2][i-1-1];
                if(T[k-1][n-i-1]==0){
                    T[k-1][n-i-1] = egg_drop0(T, k, n-i);
                }
                q = T[k-1][n-i-1];
            }

            if(p>q) {
                candidate = p;
            }else {
                candidate = q;
            }
            if(candidate+1<m){
                m = candidate+1;
            }
        }
        return m;
    }
}

int solution0(int k, int n) {
    int answer;
    std::vector<std::vector<int>> T;
    for(int i = 0; i < k; ++i) {
        std::vector<int> t(n);
        T.push_back(t);
    }
    answer = egg_drop0(T, k, n);
    return answer;
}

int egg_drop1(const int K, const int N) {
    std::vector<std::vector<int>> F;
    for(int i=0; i<K; ++i) {
        std::vector<int> f(N);
        F.push_back(f);
    }
    for(int i=0; i<N; ++i) {
        F[0][i] = i+1;
    }
    for(int i=0; i<K; ++i){
        F[i][0] = 1;
    }

    int max;
    for(int i=1; i<K; ++i) {
        for(int j=1; j<N; ++j){
            max = 1+F[i-1][j-1]+F[i][j-1];
            F[i][j] = max;
            if(max>=N) {
                break;
            }
        }
    }

    int min;
    for(int i=0; i<N; ++i) {
        if(F[K-1][i]>=N) {
            min = i+1;
            break;
        }
    }
    return min;
}

int solution1(int k, int n) {
    int answer;
    answer = egg_drop1(k, n-1);
    return answer;
}

void rec(int m, int n, int& a) {
    if (m==0 || n == 0) {
        return;
    }
    a++;
    rec(m-1,n,a);
    rec(m,n-1,a);

}

class testptr {
public:
    int a = 0;
    testptr(int  x) {
        this->a = x;
    }

};

class A
{
public:
    A(){cout<<"A constructor"<<endl;}
    virtual ~A(){cout<<"A destructor"<<endl;}//输出改为virtual
};

class B
{
public:
    B(){cout<<"B constructor"<<endl;}
    ~B(){cout<<"B destructor"<<endl;}
};

class C:public A,public B
{
public:
    C(){cout<<"C constructor"<<endl;}
    ~C(){cout<<"C destructor"<<endl;}
};

class D:public B,public A
{
public:
    D(){cout<<"D constructor"<<endl;}
    ~D(){cout<<"D destructor"<<endl;}
};



class Solution {
public:
    string minInteger(string num, int k) {

        for (int i = 0; i <num.size() ; ++i) {

        }
    }
};

int main(int argc, char* argv[])
{
    std::set<int> test{1,18,31,4,5,60,7};
    std::set<int> test1{31,18,5,7};
    std::set<int> test2;

    std::set_intersection(test.begin(), test.end(), test1.begin(),
                          test1.end(), std::inserter(test2, test2.begin()));
//    cout << test2.size() << endl;
    for (auto it : test) {
        cout<<it<<endl;
    }
    cout << "*****************" << endl;
    for (auto it : test1) {
        cout<<it<<endl;
    }
    cout << "*****************" << endl;
    for (auto it : test2) {
        cout<<it<<endl;
    }
    float ss = std::numeric_limits<float>::lowest();
    cout << ss << endl;
    std::string xx = "default";
    {
        std::string tmp = "tmp str.";
        cout<<tmp<<endl;
        xx = &tmp;
    }
    cout<<xx<<endl;


    return 0;
}
