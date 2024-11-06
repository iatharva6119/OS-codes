
#include <iostream>
#include <vector>

using namespace std;

int choice;
vector<int> finish(10);
vector<int> process_name(10);
vector<int> arrival_time(10);
vector<int> burst_time(10);
vector<int> waiting_time(10);
vector<int> turn_around_time(10);
int avg_wait_time;
int avg_turn_around_time;
int n, pending;
vector<int> remain_burst_time(10);
int count;
int time;

void input() {
    cout << "\nEnter number of processes: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        process_name[i] = i;
        cout << "\nEnter Burst time for process " << process_name[i] << ": ";
        cin >> burst_time[i];
        remain_burst_time[i] = burst_time[i];
        cout << "\nEnter arrival time for process " << process_name[i] << ": ";
        cin >> arrival_time[i];
    }
}

void round_robin() {
    int time_quantum;
    input();
    pending = n;

    cout << "\nEnter time quantum: ";
    cin >> time_quantum;
    cout << "\n\n\nGantt chart--> ";

    for (int i = 0; i < n; i++) {
        finish[i] = 0;
        waiting_time[i] = 0;
    }

    for (time = 0, count = 0; pending > 0;) {
        if (finish[count] != 1 && arrival_time[count] <= time && remain_burst_time[count] <= time_quantum) {
            time += remain_burst_time[count];
            pending--;
            finish[count] = 1;
            waiting_time[count] -= arrival_time[count];
            turn_around_time[count] = waiting_time[count] + burst_time[count];

            for (int i = 0; i < remain_burst_time[count]; i++) {
                cout << "P" << process_name[count] << " ";
            }

            for (int i = 0; i < n; i++) {
                if (i == count || finish[i] == 1) continue;
                waiting_time[i] += remain_burst_time[count];
            }
            remain_burst_time[count] = 0;
        }
        else if (finish[count] != 1 && arrival_time[count] <= time && remain_burst_time[count] >= time_quantum) {
            time += time_quantum;
            remain_burst_time[count] -= time_quantum;

            for (int i = 0; i < n; i++) {
                if (i == count || finish[i] == 1) continue;
                waiting_time[i] += time_quantum;
            }

            for (int i = 0; i < time_quantum; i++) {
                cout << "P" << process_name[count] << " ";
            }
        }
        count = (count + 1) % n;
    }
}

void sort_processes() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (remain_burst_time[i] < remain_burst_time[j]) {
                swap(burst_time[i], burst_time[j]);
                swap(remain_burst_time[i], remain_burst_time[j]);
                swap(arrival_time[i], arrival_time[j]);
                swap(waiting_time[i], waiting_time[j]);
                swap(process_name[i], process_name[j]);
                swap(finish[i], finish[j]);
            }
        }
    }
}

void sjf_preempt() {
    input();
    pending = n;

    cout << "\n\n\nGantt Chart--> ";
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
        waiting_time[i] = 0;
    }

    time = 0;
    while (pending > 0) {
        sort_processes();  // Sort processes by remaining burst time

        for (count = 0; count < n; count++) {
            if (finish[count] == 0 && arrival_time[count] <= time) {
                cout << "P" << process_name[count] << " ";

                // Simulate one unit time execution for the process
                remain_burst_time[count]--;
                time++;

                // Update waiting time for all other unfinished processes
                for (int i = 0; i < n; i++) {
                    if (i != count && finish[i] == 0 && arrival_time[i] <= time) {
                        waiting_time[i]++;
                    }
                }

                // If process has completed
                if (remain_burst_time[count] == 0) {
                    pending--;
                    finish[count] = 1;
                    turn_around_time[count] = time - arrival_time[count];  // Calculate turnaround time
                    waiting_time[count] = turn_around_time[count] - burst_time[count];  // Calculate waiting time
                }
                break;  // Preempt and check next process in sorted order
            }
        }
    }
}

void display_output() {
    cout << "\n\nProcess\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << process_name[i] << "\t\t" << arrival_time[i] << "\t\t" << burst_time[i] << "\t\t"
             << turn_around_time[i] << "\t\t" << waiting_time[i] << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\nScheduling Algorithms Menu:";
        cout << "\n1. Round Robin";
        cout << "\n2. Shortest Job First (SJF) Preemptive";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nExecuting Round Robin Algorithm...\n";
                round_robin();
                display_output();
                break;

            case 2:
                cout << "\nExecuting Shortest Job First (SJF) Preemptive Algorithm...\n";
                sjf_preempt();
                display_output();
                break;

            case 3:
                cout << "\nExiting the program...\n";
                return 0;

            default:
                cout << "\nInvalid choice! Please enter a valid option.\n";
        }
    }

    return 0;
}
