#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>

using namespace std;

/*
 * Thread t1, while sleeping, the main thread will aquire the unique lock.
 * When it sees that ready is false, it will then wait on the lock.
 * The wait first releases the lock, and allows the other threads to continue.
 * In this case the thread t1 will now attain the lock and will notify_one
 * after unlocking it. This will now release the wait on the condition and 
 * main thread will obtain the lock.
 */

int main()
{
    condition_variable condition;
    mutex mtx;
    bool ready = false;

    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(2000));
        unique_lock<mutex> lock(mtx);
        ready = true;
        lock.unlock();
        condition.notify_one();
    });

    unique_lock<mutex> lock(mtx);
    while(!ready)
    {
        cout << "Not ready" << endl;
        condition.wait(lock);
        cout << "It's ready" << endl;
    }

    cout << "Ready! " << ready << endl;

    t1.join();
    return 0;
}