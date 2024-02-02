#include <iostream>
using namespace std;
int main(){
int x, b, i, j, k;
// x is no of process and b is no of resources
x = 5; b = 3; 
int aloc_Matrix[5][3] ={ { 0, 1, 0 },  
					{ 2, 0, 0 },
					{ 3, 0, 2 },
					{ 2, 1, 1 }, 
					{ 0, 0, 2 } }; 
int max_Matrix[5][3] = { { 7, 5, 3 }, 
				{ 3, 2, 2 }, 
				{ 9, 0, 2 }, 
				{ 2, 2, 2 }, 
				{ 4, 3, 3 } };
int aval_Matrix[3] = { 3, 3, 2 }; 
int f[x], ans[x], ind = 0;
for(k = 0; k < x; k++){
	f[k] = 0;
}
int need_Matrix[x][b];
for(i = 0; i < x; i++){
	for(j = 0; j < b; j++)
	need_Matrix[i][j] = max_Matrix[i][j] - aloc_Matrix[i][j];
}
int y = 0;
for (k = 0; k < 5; k++) {
	for (i = 0; i < x; i++) {
	if (f[i] == 0) {
		int flag = 0;
		for (j = 0; j < b; j++) {
		if (need_Matrix[i][j] > aval_Matrix[j]){
			flag = 1;
			break;
		}
	}
		if (flag == 0) {
		ans[ind++] = i;
		for (y = 0; y < b; y++)
			aval_Matrix[y] += aloc_Matrix[i][y];
		f[i] = 1;
		}
	}
	}
}

int flag = 1;
// sequence is safe or not
for(int i = 0;i<x;i++){
		if(f[i]==0){
		flag = 0;
		cout << "sequence is not safe";
		break;
	}
}
if(flag==1){
	cout << " Sequence is safe" << endl;
	for (i = 0; i < x-1; i++)
	cout << " P" << ans[i] << " ->";
	cout << " P" << ans[x-1] <<endl;
}
	return (0);
}

#include <iostream>
#include<mutex>
using namespace std;
int mutx = 1;
int full = 0;
int emp = 10, x = 0;
void producer(){
	--mutx;
	++full;
    --emp;
	x++;
	cout<< "producer produces items: "<< x <<endl;
	++mutx;
}
void consumer(){
	--mutx;
	--full;
	++emp;
	cout<< "consumer consumes items: "<< x <<endl;
	x--;
	++mutx;
}
int main(){
    int n, i;
	cout<<"1. -> producer"<<endl;
	cout<<"2. -> consumer"<<endl;
	cout<<"3. -> exit"<<endl;
#pragma omp critical
	for (i = 1; i > 0; i++) {
		cout<<"enter choice: ";
		cin>>n;
    	switch (n) {
		case 1:
    		if ((mutx == 1)&& (emp != 0)) {
				producer();
			}
			else {
				cout<<"Buffer is full"<<endl;
			}
			break;
		case 2:
    		if ((mutx == 1)&& (full != 0)) {
				consumer();
			}
			else {
				cout<<"Buffer is empty"<<endl;
			}
			break;
		case 3:
			exit(0);
			break;
		}
	}
}

#include<bits/stdc++.h>
using namespace std;
int pageFaults(int arr[], int n, int x){
	unordered_set<int> s;
	queue<int> indx;
    int page_faults = 0;
	for (int i=0; i<n; i++){
		if (s.size() < x){
			if (s.find(arr[i])==s.end()){
				s.insert(arr[i]);
				page_faults++;
				indx.push(arr[i]);
			}
		}
    	else{
    		if (s.find(arr[i]) == s.end()){
				int val = indx.front();
				indx.pop();
				s.erase(val);
                s.insert(arr[i]);
				indx.push(arr[i]);
        		page_faults++;
			}
		}
	}
	return page_faults;
}
int main(){
	int arr[] = {7, 0, 1, 2, 0, 3, 0, 4,2, 3, 0, 3, 2};
	int n = sizeof(arr)/sizeof(arr[0]);
	int x = 4;
	cout <<"no. of page faults: "<< pageFaults(arr, n, x);
	return 0;
}








#include <bits/stdc++.h>

using namespace std;

class Process {
public:
    string name;
    int priority;
    int burst_time;
    int waiting_time;
    int turnaround_time;

    Process(string name, int priority, int burst_time) {
        this->name = name;
        this->priority = priority;
        this->burst_time = burst_time;
        this->waiting_time = 0;
        this->turnaround_time = 0;
    }
};

int main() {
    vector<queue<Process*>> queues(3);
    queues[0] = queue<Process*>(); 
    queues[1] = queue<Process*>(); 
    queues[2] = queue<Process*>(); 

    Process* p1 = new Process("P1", 2, 8);
    Process* p2 = new Process("P2", 1, 5);
    Process* p3 = new Process("P3", 3, 12);
    Process* p4 = new Process("P4", 1, 7);
    Process* p5 = new Process("P5", 2, 10);

    
    queues[p1->priority - 1].push(p1);
    queues[p2->priority - 1].push(p2);
    queues[p3->priority - 1].push(p3);
    queues[p4->priority - 1].push(p4);
    queues[p5->priority - 1].push(p5);

    
    int time = 0;
    while (true) {
        
        if (queues[0].empty() && queues[1].empty() && queues[2].empty()) {
            break;
        }

        Process* current_process = nullptr;
        if (!queues[0].empty()) {
            current_process = queues[0].front();
            queues[0].pop();
        } else if (!queues[1].empty()) {
            current_process = queues[1].front();
            queues[1].pop();
        } else {
            current_process = queues[2].front();
            queues[2].pop();
        }

        current_process->burst_time -= 1;
        time += 1;

        if (current_process->burst_time == 0) {
            current_process->turnaround_time = time;
            current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
            cout << "Process " << current_process->name << " finished at time " << current_process->turnaround_time << endl;
            delete current_process;
        } else {
            queues[current_process->priority - 1].push(current_process);
        }
    }

    return 0;
}







#include <bits/stdc++.h>
using namespace std;
class Process {
    int id;
    int priority;
    int burstTime;
};
class ComparePriority {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.priority < p2.priority;
    }
};
int main() {
    vector<Process> processes = {
        {3, 2, 10},
        {2, 1, 5},
        {4, 0, 1},
        {7., 3, 8},
        {5, 2, 4},
        {6, 1, 3}
    };
    priority_queue<Process, vector<Process>, ComparePriority> level0;
    priority_queue<Process, vector<Process>, ComparePriority> level1;
    priority_queue<Process, vector<Process>, ComparePriority> level2;
    for (Process& p : processes) {
        if (p.priority == 0) {
            level0.push(p);
        }
        else if (p.priority == 1) {
            level1.push(p);
        }
        else if (p.priority == 2) {
            level2.push(p);
        }
    }
    int currentTime = 0;
    Process currentProcess = {-1, -1, -1};
    while (!level0.empty() || !level1.empty() || !level2.empty() || currentProcess.id != -1) {
        if (currentProcess.id != -1 && currentProcess.burstTime == 0) {
            cout << "Process " << currentProcess.id << " finished at time " << currentTime << endl;
            currentProcess = {-1, -1, -1};
        }
        if (currentProcess.id == -1 && !level0.empty()) {
            currentProcess = level0.top();
            level0.pop();
        }
        else if (currentProcess.id == -1 && !level1.empty()) {
            currentProcess = level1.top();
            level1.pop();
        }
        else if (currentProcess.id == -1 && !level2.empty()) {
            currentProcess = level2.top();
            level2.pop();
        }
        if (currentProcess.id != -1) {
            cout << "Running process " << currentProcess.id << " at time " << currentTime << endl;
            currentProcess.burstTime--;
        }
        for (Process& p : processes) {
            if (p.burstTime > 0 && p.priority == 0 && p.id != currentProcess.id) {
                level0.push(p);
            }
            else if (p.burstTime > 0 && p.priority == 1 && p.id != currentProcess.id) {
                level1.push(p);
            }
            else if (p.burstTime > 0 && p.priority == 2 && p.id != currentProcess.id) {
                level2.push(p);
            }
        }
        currentTime++;
    }
    return 0;
}



#include <bits/stdc++.h>
using namespace std;
class Process {
	public:
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
};
class ComparePriority {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.priority > p2.priority;
    }
};
int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    cout << "Enter the arrival time, burst time, and priority of each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime;
    }
    vector<queue<Process>> queues(3);  
    int currentTime = 0;
    int quantum[3] = { 8, 16, 32 };    
    int priorityLevel = 0;
    while (true) {
    for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime == currentTime) {
                queues[0].push(processes[i]);
            }
        }
    if (!queues[priorityLevel].empty()) {
            Process currentProcess = queues[priorityLevel].front();
            queues[priorityLevel].pop();
            cout << "Running process " << currentProcess.pid << " at time " << currentTime << "\n";
            currentProcess.remainingTime -= quantum[priorityLevel];
            if (currentProcess.remainingTime > 0) {
                if (priorityLevel < 2) {
                    priorityLevel++;
                }
                queues[priorityLevel].push(currentProcess);
            } else {
                cout << "Process " << currentProcess.pid << " finished at time " << currentTime + quantum[priorityLevel] << "\n";
            }
        }
        bool allEmpty = true;
        for (int i = 0; i < 3; i++) {
            if (!queues[i].empty()) {
                allEmpty = false;
                break;
            }
        }
        if (allEmpty) {
            break;
        }
        currentTime += quantum[priorityLevel];
        if (priorityLevel == 2) {
            priorityLevel = 0;
        }
    }
    return 0;
}


#include <iostream>
#include <unordered_map>
using namespace std;
class LRUCache {
private:
    int capacity;
    unordered_map<int, int> cache; 
    unordered_map<int, int> usage; 
    int count; 
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        count = 0;
    }
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            usage[key] = ++count;
            return cache[key];
        }
        return -1; 
    }
    void put(int key, int value) {
        if (cache.find(key) == cache.end()) {
            if (count >= capacity) {
                int lruKey = getLRUKey();
                cache.erase(lruKey);
                usage.erase(lruKey);
            }
            count++;
        }
        cache[key] = value;
        usage[key] = ++count;
    }
private:
    int getLRUKey() {
        int lruKey = usage.begin()->first;
        int lruCount = usage.begin()->second;
        for (auto it = usage.begin(); it != usage.end(); ++it) {
            if (it->second < lruCount) {
                lruKey = it->first;
                lruCount = it->second;
            }
        }
        return lruKey;
    }
};
int main() {
    LRUCache cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.put(4, 40); 

    cout << cache.get(1) << endl; 
    cout << cache.get(2) << endl; 
    cout << cache.get(3) << endl; 
    cout << cache.get(4) << endl; 

    cache.put(3, 35);
    cout << cache.get(3) << endl; 
    return 0;
}


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;
mutex mtx;
condition_variable cv_read, cv_write; 
int read_count = 0; 
int data = 0; 
void reader() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        while (read_count == -1) {
            cv_read.wait(lock);
        }     
        cout << "Reader " << this_thread::get_id() << " reads: " << data << endl;
        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}
void writer() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        while (read_count != 0) {
            cv_write.wait(lock);
        }     
        data++;
        cout << "Writer " << this_thread::get_id() << " writes: " << data << endl;
        cv_read.notify_all();
        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}
int main() {
    const int NUM_READERS = 3;
    const int NUM_WRITERS = 2;

    thread readers[NUM_READERS];
    for (int i = 0; i < NUM_READERS; i++) {
        readers[i] = thread(reader);
    }
    thread writers[NUM_WRITERS];
    for (int i = 0; i < NUM_WRITERS; i++) {
        writers[i] = thread(writer);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        readers[i].join();
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        writers[i].join();
    }
    return 0;
}


#include <iostream>
#include <vector>
using namespace std;
int calculateTotalHeadMovements(const vector<int>& requests, int headStart) {
    int totalHeadMovements = 0;
    int currentHeadPosition = headStart;
    for (int i = 0; i < requests.size(); i++) {
        int headMovement = abs(currentHeadPosition - requests[i]);
        totalHeadMovements += headMovement;
        currentHeadPosition = requests[i];
    }
    return totalHeadMovements;
}
int main() {
    int numRequests;
    int headStart;
    vector<int> requests;
    cout << "Enter the number of requests: ";
    cin >> numRequests;
    cout << "Enter the head start position: ";
    cin >> headStart;
    cout << "Enter the requests: ";
    for (int i = 0; i < numRequests; i++) {
        int request;
        cin >> request;
        requests.push_back(request);
    }
    int totalHeadMovements = calculateTotalHeadMovements(requests, headStart);
    cout << "Total Head Movements: " << totalHeadMovements << endl;
    return 0;
}


#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
int getPageToBeReplaced(const vector<int>& pages, const unordered_set<int>& pageSet, const vector<int>& futurePages, int currentIndex) {
    int pageToBeReplaced = -1;
    int farthestFutureUse = -1;
    for (auto it = pageSet.begin(); it != pageSet.end(); ++it) {
        int currentPage = *it;
        if (find(futurePages.begin() + currentIndex, futurePages.end(), currentPage) == futurePages.end()) {
            return currentPage;
        }
        int futureUse = distance(futurePages.begin() + currentIndex, find(futurePages.begin() + currentIndex, futurePages.end(), currentPage));
        if (futureUse > farthestFutureUse) {
            farthestFutureUse = futureUse;
            pageToBeReplaced = currentPage;
        }
    }
    return pageToBeReplaced;
}
int getOptimalPageFaults(const vector<int>& pages, int numFrames) {
    int numPageFaults = 0;
    unordered_set<int> pageSet;
    vector<int> futurePages(pages.size());
    for (int i = 0; i < pages.size(); i++) {
        int currentPage = pages[i];
        futurePages[i] = -1;
        for (int j = i + 1; j < pages.size(); j++) {
            if (pages[j] == currentPage) {
                futurePages[i] = j;
                break;
            }
        }
    }
    for (int i = 0; i < pages.size(); i++) {
        int currentPage = pages[i];
        if (pageSet.find(currentPage) == pageSet.end()) {
            if (pageSet.size() == numFrames) {
                int pageToBeReplaced = getPageToBeReplaced(pages, pageSet, futurePages, i);
                pageSet.erase(pageToBeReplaced);
            }
            pageSet.insert(currentPage);
            numPageFaults++;
        }
    }
    return numPageFaults;
}
int main() {
    int numFrames, numPages;
    cout << "Enter the number of frames: ";
    cin >> numFrames;
    cout << "Enter the number of pages: ";
    cin >> numPages;
    vector<int> pages(numPages);
    cout << "Enter the pages: ";
    for (int i = 0; i < numPages; i++) {
        cin >> pages[i];
    }
    int numPageFaults = getOptimalPageFaults(pages, numFrames);
    cout << "Number of Page Faults: " << numPageFaults << endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int getShortestSeekTime(const vector<int>& requests, int currentHead) {
    int shortestSeekTime = INT_MAX;
    int shortestSeekTimeIndex = -1;
    for (int i = 0; i < requests.size(); i++) {
        int seekTime = abs(requests[i] - currentHead);
        if (seekTime < shortestSeekTime) {
            shortestSeekTime = seekTime;
            shortestSeekTimeIndex = i;
        }
    }
    return shortestSeekTimeIndex;
}
int getSSTFSeekCount(const vector<int>& requests, int initialHead) {
    int totalSeekCount = 0;
    int currentHead = initialHead;
    vector<int> remainingRequests = requests;
    while (!remainingRequests.empty()) {
        int shortestSeekTimeIndex = getShortestSeekTime(remainingRequests, currentHead);
        int nextRequest = remainingRequests[shortestSeekTimeIndex];
        totalSeekCount += abs(nextRequest - currentHead);
        currentHead = nextRequest;
        remainingRequests.erase(remainingRequests.begin() + shortestSeekTimeIndex);
    }
    return totalSeekCount;
}
int main() {
    int numRequests, initialHead;
    cout << "Enter the number of requests: ";
    cin >> numRequests;
    vector<int> requests(numRequests);
    cout << "Enter the requests: ";
    for (int i = 0; i < numRequests; i++) {
        cin >> requests[i];
    }
    cout << "Enter the initial head position: ";
    cin >> initialHead;
    int totalSeekCount = getSSTFSeekCount(requests, initialHead);
    cout << "Total Seek Count: " << totalSeekCount << endl;
    return 0;
}
