#include "RoundRobin.h"

/*
This is a constructor for RoundRobin Scheduler, you should use the extractProcessInfo function first
to load process information to process_info and then sort process by arrival time;

Also initialize time_quantum
*/
RoundRobin::RoundRobin(string file, int time_quantum) : time_quantum(time_quantum) {
	extractProcessInfo(file);
	sort(processVec.begin(), processVec.end(), [](Process& a, Process& b){
		return a.get_arrival_time() < b.get_arrival_time();
	});
}

// Schedule tasks based on RoundRobin Rule
// the jobs are put in the order the arrived
// Make sure you print out the information like we put in the document
// void RoundRobin::schedule_tasks() {
// /* uncomment these two lines; commented to allow compilation */
// //	int timestep = 0;
// //	int quantum_remaining = time_quantum;
// 	while(processVec.size() || processQ.size()) {
//         /* Task 1 */
// 		// get new tasks
//         // Go through the processVec
//         // if the arrival time is less than the timestep
//         // push the process into the processQ vector
//         // else go to the next process


//         /* Task 2 */
// 		// is there a task to do?
//         // print timestep and set appropriate process not completed flag
//         // increase timestep
//         // set quantum_remaining to correct value
//         if(false/* condition */) {
//             continue;
//         }

//         /* Task 3 */
// 		// get current task from processQ

//         /* Task 4 */
//         // special condition: is the process critical?
//             // print a new process running with appropriate flag
//             // update timestep appropriately
//             // Run the process
//             // reset quantum_remaining

//         /* Task 5 */
// 		// is it done? Check if remaining time is 0
//             // print a new process running with appropriate flag
//             // remove from processQ
//             // set quantum_remaining to correct value
//         if(false/* condition */) {
//             continue;
//         }

//         /* Task 6 */
// 		//has the quantum expired?
//             // pop the process from processQ and push it to the back
//             // set quantum_remaining to correct value
//         if(false/* condition */) {
//             continue;
//         }

//         /* Task 7 */
// 		// otherwise...
//         // print timestep of an incomplete process
//         // run the process for one count
//         // decrement quantum remaining
//         // increment timestep
// 	}
// }

// void RoundRobin::schedule_tasks() {
//     int timestep = 0;
//     int quantum_remaining = time_quantum;
//     auto it = processVec.begin();

//     while(it != processVec.end() || !processQ.empty()) {
//         // Task 1: Load new tasks into the queue
//         while(it != processVec.end() && it->get_arrival_time() <= timestep) {
//             processQ.push(*it);
//             it++;
//         }

//         // Task 2: Check if there's a task to do
//         if(processQ.empty()) {
//             print(timestep, -1, false); // NOP
//             timestep++;
//             continue;
//         }

//         Process& current_task = processQ.front();

//         // Task 4: Check if the process is critical
//         if(current_task.is_Proc_Critical()) {
//             print(timestep, current_task.getPid(), false);
//             current_task.Run(current_task.get_remaining_time());
//             timestep += current_task.get_cpu_burst_time(); // Assuming Run updates the remaining time correctly
//             print(timestep, current_task.getPid(), true);
//             processQ.pop();
//             quantum_remaining = time_quantum; // Reset quantum
//             continue;
//         }

//         // Task 7: Run the process for one time unit or until completion
//         if(quantum_remaining > 0 && current_task.get_remaining_time() > 0) {
//             print(timestep, current_task.getPid(), false);
//             current_task.Run(1); // Run for 1 time unit
//             quantum_remaining--;
//             timestep++;
//         }

//         // Task 5: Check if the current task is done
//         if(current_task.get_remaining_time() <= 0) {
//             print(timestep, current_task.getPid(), true);
//             processQ.pop();
//             quantum_remaining = time_quantum; // Reset quantum for the next process
//             continue;
//         }

//         // Task 6: Quantum expired, move the current task to the back of the queue
//         if(quantum_remaining <= 0) {
//             processQ.push(current_task);
//             processQ.pop();
//             quantum_remaining = time_quantum; // Reset quantum
//         }
//     }
// }


// void RoundRobin::schedule_tasks() {
//     int timestep = 0;
//     int quantum_remaining = time_quantum;
//     auto it = processVec.begin();

//     while(it != processVec.end() || !processQ.empty()) {
//         // Load new tasks into the queue
//         while(it != processVec.end() && it->get_arrival_time() <= timestep) {
//             processQ.push(*it);
//             it++;
//         }

//         if(processQ.empty()) {
//             print(timestep, -1, false); // NOP
//             timestep++;
//             continue;
//         }

//         Process& current_task = processQ.front();

//         // Handle critical process immediately
//         if(current_task.is_Proc_Critical()) {
//             int runTime = current_task.get_remaining_time();
//             print(timestep, current_task.getPid(), false);
//             current_task.Run(runTime);
//             timestep += runTime; // Advance timestep by the process's burst time
//             print(timestep, current_task.getPid(), true);
//             processQ.pop(); // Remove the process from the queue
//             quantum_remaining = time_quantum; // Reset quantum
//             continue;
//         }

//         // Run the process for one time unit or until completion
//         if(quantum_remaining > 0 && current_task.get_remaining_time() > 0) {
//             print(timestep, current_task.getPid(), false);
//             current_task.Run(1); // Run for 1 time unit
//             quantum_remaining--;
//             timestep++;
//         }

//         // Check if the current task is done
//         if(current_task.get_remaining_time() <= 0) {
//             print(timestep, current_task.getPid(), true);
//             processQ.pop();
//             quantum_remaining = time_quantum; // Reset quantum for the next process
//             continue;
//         }

//         // Quantum expired, move the current task to the back of the queue
//         if(quantum_remaining <= 0) {
//             processQ.push(current_task);
//             processQ.pop();
//             quantum_remaining = time_quantum; // Reset quantum
//         }
//     }
// }

void RoundRobin::schedule_tasks() {
    int timestep = 0;
    int quantum_remaining = time_quantum;
    auto it = processVec.begin();

    while(it != processVec.end() || !processQ.empty()) {
        while(it != processVec.end() && it->get_arrival_time() <= timestep) {
            processQ.push(*it);
            it++;
        }

        if(processQ.empty()) {
            print(timestep, -1, false);
            timestep++;
            continue;
        }

        Process& current_task = processQ.front();

        if(current_task.is_Proc_Critical()) {
            print(timestep, current_task.getPid(), false);
            current_task.Run(current_task.get_remaining_time()); 
            timestep += current_task.get_cpu_burst_time();
            print(timestep, current_task.getPid(), true); 
            processQ.pop();
            quantum_remaining = time_quantum; 
            continue;
        }

        if(quantum_remaining > 0 && current_task.get_remaining_time() > 0) {
            print(timestep, current_task.getPid(), false); 
            current_task.Run(1);
            quantum_remaining--;
            timestep++;
        }

        if(current_task.get_remaining_time() <= 0 || quantum_remaining <= 0) {
            if(current_task.get_remaining_time() > 0) {
                processQ.push(current_task);
            } else {
                print(timestep, current_task.getPid(), true);
            }
            processQ.pop();
            quantum_remaining = time_quantum; 
        }
        // if  process is not completed and  quantum has not expired, continue in the next iteration
    }
}



/*************************** 
ALL FUNCTIONS UNDER THIS LINE ARE COMPLETED FOR YOU
You can modify them if you'd like, though :)
***************************/


// Default constructor
RoundRobin::RoundRobin() {
	time_quantum = 0;
}

// Time quantum setter
void RoundRobin::set_time_quantum(int quantum) {
	this->time_quantum = quantum;
}

// Time quantum getter
int RoundRobin::get_time_quantum() {
	return time_quantum;
}

// Print function for outputting system time as part of the schedule tasks function
void RoundRobin::print(int system_time, int pid, bool isComplete){
	string s_pid = pid == -1 ? "NOP" : to_string(pid);
	cout << "System Time [" << system_time << "].........Process[PID=" << s_pid << "] ";
	if (isComplete)
		cout << "finished its job!" << endl;
	else
		cout << "is Running" << endl;
}

bool
string2bool (const std::string &v)
{
    return !v.empty () &&
        (strcasecmp (v.c_str (), "true") == 0 ||
         atoi (v.c_str ()) != 0);
}

// Read a process file to extract process information
// All content goes to proces_info vector
void RoundRobin::extractProcessInfo(string file){
	// open file
	ifstream processFile (file);
	if (!processFile.is_open()) {
		perror("could not open file");
		exit(1);
	}

	// read contents and populate process_info vector
	string curr_line, temp_num;
	int curr_pid, curr_arrival_time, curr_burst_time;
    bool isCritical;
	while (getline(processFile, curr_line)) {
		// use string stream to seperate by comma
		stringstream ss(curr_line);
		getline(ss, temp_num, ',');
		curr_pid = stoi(temp_num);
		getline(ss, temp_num, ',');
		curr_arrival_time = stoi(temp_num);
		getline(ss, temp_num, ',');
		curr_burst_time = stoi(temp_num);
		getline(ss, temp_num, ',');
        isCritical = string2bool(temp_num);
		Process p(curr_pid, curr_arrival_time, curr_burst_time, isCritical);

		processVec.push_back(p);
	}

	// close file
	processFile.close();
}
