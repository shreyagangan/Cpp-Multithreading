#include <iostream>
#include <thread>
#include <chrono>


using namespace std;

int main()
{
    bool ready = false;

    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(2000));
        ready = true;
    });

    //t1.join();

    while(!ready)
    {
        cout << "Not ready" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    t1.join();
    cout << "Ready!" << endl;

    return 0;
}