#include<iostream>
#include<algorithm>
using namespace std;
bool x[1000];

void timsnt(int a, int b){
    for(int i = 0; i < 1000; i++)
    	x[i] = true;
    x[0] = false;
    x[1] = false;
    int i = 2;
    	for(int j = 2; j <= b / i; j++){
    		x[i * j] = false;
		}
		i++;
	}

void out(int a, int b){
	bool check = false;
	for(int i = a; i <= b; i++){
		if(x[i] == true) cout<<i<<" ";
		check = true;
	}
	if(check == true){
		cout<<endl<<"La so nguyen to trong doan "<<a<<" - "<<b;
	}
	else cout<<"Tren doan "<<a<<" - "<<b<<" khong chua so nguyen to";
}
int main(){
	cout<<"Chuong trinh liet ke so nguyen to trong khoang a - b \n";
    int a, b;
    cout << "Tim so nguyen to trong khoang(a - b): ";
    cin >> a >> b;
    timsnt(a, b);
    out(a, b);
    return 0;
}