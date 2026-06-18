#include <iostream>
#include<struct.h>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<thread>
using namespace std;

typedef long long ll;

// structure of a message
struct Message
{
    int message_type;
    string paylaod;
};

// message queue
class MessageQueue{
    private:
    queue<Message> q;
    mutex mutex_;
    condition_variable condition;
    public:
    void enqueue(const Message& message){
        unique_lock<mutex> lock(mutex_);
        q.push(message);
        lock.unlock();
        condition.notify_one();
    }
    Message dequeue(){
        unique_lock<mutex> lock(mutex_);
        condition.wait(lock, [this] { return !q.empty(); });
        Message message = q.front();
        q.pop();
        return message;
    }
};

void producer (MessageQueue& mq, int messageType, const string& payload){
    Message message;
    message.message_type = messageType;
    message.paylaod = payload;
    mq.enqueue(message);
    cout<<"producer sent the msg: " <<message.paylaod<<"\n";
}

void consumer(MessageQueue& mq){
    Message message;
    while(true){
        message = mq.dequeue();
        // process the message
        break;
    }
    cout<<"consumer received msg: " << message.paylaod<<"\n";
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    MessageQueue mq;
    thread producerThread(producer, ref(mq), 1, "Hello, World!");
    thread consumerThread(consumer, ref(mq));

    producerThread.join();
    consumerThread.join();

    return 0;
}

