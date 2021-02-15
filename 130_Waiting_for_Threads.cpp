#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    atomic<bool> ready = false;

    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(2000));
        ready = true;
    });

    while(!ready)
    {
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    t1.join();
    
    cout << "ready " << ready << endl;

    return 0;
}