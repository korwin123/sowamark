#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>
#include <ctime>
#include <ratio>
#include <conio.h>
#include <windows.h>
#include "BigInt.cpp"
using namespace std;
int threadCount=1;
BigInt returns[64];
unsigned long SilniaR(int n)
{
	return n <= 0 ? 1 : n*SilniaR(n-1); //ta funkcja to gunwo
}
//rekurencja to szyt
uint64_t Silnia(int n)
{
	uint64_t val=1;
	for(;n>0;n--){
		val*=n;
	}
	return val;
}
void SilniaB(int n,int tid)
{
	BigInt val(1);
	for(;n>0;n--){
		val=val*BigInt(n);
	}
	returns[tid]=val;
}
void gotoxy( int x, int y )
{
	COORD p = { x, y };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}
void ThreadedSilnia(int n){
	
	thread threads[threadCount];
	for(int i=0;i<threadCount;i++){
		threads[i]=thread(SilniaB,n+i,i);
	}
	for(int i=0;i<threadCount;i++){
		threads[i].join();
	}
}

int main(){
	cout<< "SowaMark -2"<<endl;
	if(thread::hardware_concurrency()){
		threadCount=thread::hardware_concurrency();
	}
	cout<< "Starting with "<<threadCount<<" threads"<<endl<<endl;
	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
	for(int i=1;i<=192;i+=threadCount){
		ThreadedSilnia(i);
		if((i%16)==1){
			gotoxy(0,3);
			cout<<(int)(((i-1)/192.0)*100)<<"%"<<endl;
		}
	}
	gotoxy(0,3);
	cout<<"100%"<<endl;
	
	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);
	cout << "Score " <<(int)(10000/ time_span.count() )<< endl;
	cout<<"Press any key to end"<<endl;
	getch();
	
	return 0;
}

