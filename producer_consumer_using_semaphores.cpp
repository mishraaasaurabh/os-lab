#include <bits/stdc++.h>
#include<semaphore.h>


#define BUFFER_SIZE 5

using namespace std;

queue<int> buffer;
sem_t emptySlots;
sem_t filledSlots;
mutex mtx;

void producer(int id) {
    int item = 1;
    while (true) {
        sem_wait(&emptySlots);
        {
            lock_guard<mutex> lock(mtx);
            buffer.push(item);
            cout << "Producer " << id << " produced item: " << item << "\n";
            item++;
        }
        sem_post(&filledSlots);
        sleep(1);
    }
}

void consumer(int id) {
    while (true) {
        sem_wait(&filledSlots);
        {
            lock_guard<mutex> lock(mtx);
            int item = buffer.front();
            buffer.pop();
            cout << "Consumer " << id << " consumed item: " << item << "\n";
        }
        sem_post(&emptySlots);
        sleep(2);
    }
}

int main() {
    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&filledSlots, 0, 0);

    vector<thread> producers, consumers;
    for (int i = 1; i <= 2; ++i) {
        producers.emplace_back(producer, i);
    }
    for (int i = 1; i <= 2; ++i) {
        consumers.emplace_back(consumer, i);
    }

    for (auto& t : producers) t.join();
    for (auto& t : consumers) t.join();

    sem_destroy(&emptySlots);
    sem_destroy(&filledSlots);

    return 0;
}
