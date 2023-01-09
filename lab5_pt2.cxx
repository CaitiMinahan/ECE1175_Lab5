#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <string>

int main (){
while (1){
	std::ifstream myfile;
	myfile.open("/proc/stat");
	std::string myline;
	if (myfile.is_open() ) {
		std::getline (myfile, myline); //skip first line
		std::string name[4];
		//arrays of timing info
		int user[4], nice[4], system[4], idle[4], iowait[4], irq[4], softirq[4], steal[4], dummy1[4], dummy2[4];
		//reading into the arrays for each CPU core
		myfile >> name[0] >> user[0] >> nice[0] >> system[0] >> idle[0] >> iowait[0] >> irq[0] >> softirq[0] >> steal[0] >> dummy1[0] >> dummy2[0];
		myfile >> name[1] >> user[1] >> nice[1] >> system[1] >> idle[1] >> iowait[1] >> irq[1] >> softirq[1] >> steal[1] >> dummy1[1] >> dummy2[1];
		myfile >> name[2] >> user[2] >> nice[2] >> system[2] >> idle[2] >> iowait[2] >> irq[2] >> softirq[2] >> steal[2] >> dummy1[2] >> dummy2[2];
		myfile >> name[3] >> user[3] >> nice[3] >> system[3] >> idle[3] >> iowait[3] >> irq[3] >> softirq[3] >> steal[3] >> dummy1[3] >> dummy2[3];

		myfile.close();

		//calculating per-CPU utilization ratio in real time
		int Total_pre[4], Idle_pre[4], Usage_pre[4];
		int Total_post[4], Idle_post[4], Usage_post[4];
		for (int i = 0; i < 4; i++){
			Total_pre[i] = user[i] + nice[i] + system[i] + idle[i] + iowait[i] + irq[i] + softirq[i] + steal[i];
			Idle_pre[i] = idle[i] + iowait[i];
			Usage_pre[i] = Total_pre[i] - Idle_pre[i];
		}

		sleep(1); //wait to get delta

		//open file again for new values
		myfile.open("/proc/stat");
		std::getline (myfile, myline); //skip first line
		//reading into the arrays for each CPU core
		myfile >> name[0] >> user[0] >> nice[0] >> system[0] >> idle[0] >> iowait[0] >> irq[0] >> softirq[0] >> steal[0] >> dummy1[0] >> dummy2[0];
		myfile >> name[1] >> user[1] >> nice[1] >> system[1] >> idle[1] >> iowait[1] >> irq[1] >> softirq[1] >> steal[1] >> dummy1[1] >> dummy2[1];
		myfile >> name[2] >> user[2] >> nice[2] >> system[2] >> idle[2] >> iowait[2] >> irq[2] >> softirq[2] >> steal[2] >> dummy1[2] >> dummy2[2];
		myfile >> name[3] >> user[3] >> nice[3] >> system[3] >> idle[3] >> iowait[3] >> irq[3] >> softirq[3] >> steal[3] >> dummy1[3] >> dummy2[3];

		myfile.close();

		for (int i = 0; i < 4; i++){
			Total_post[i] = user[i] + nice[i] + system[i] + idle[i] + iowait[i] + irq[i] + softirq[i] + steal[i];
			Idle_post[i] = idle[i] + iowait[i];
			Usage_post[i] = Total_post[i] - Idle_post[i];
		}

		int Total_delta[4], Usage_delta[4], desired_freq, next_freq[4], freq_choice(50);
		float Util[4];

		//calculate the delta and util
		for (int i = 0; i<4; i++){
			Total_delta[i] = Total_post[i] - Total_pre[i];
			Usage_delta[i] = Usage_post[i] - Usage_pre[i];
			Util[i] = ((float)Usage_delta[i]/(float)Total_delta[i])*100;
			//display util of each CPU 
			std::cout << "CPU" << i << ":" << Util[i] << "%" << std::endl;
		}

		//find the max util
		float max_util=0;
		for(int i = 0; i < 4; i++){
			if (max_util < Util[i]){
				max_util = Util[i];
			}
		//std::cout << Util[i] << std::endl;
		}
		std::cout << std:: endl << "The Max Utilization is: " << max_util << "%" << std::endl;

		desired_freq = 1.25*15000*max_util;

		//std::cout << desired_freq << std::endl;
		int freq_options[4] = {600000, 750000, 1000000, 1500000};
		int index = 0;
		for (int i = 0; i < 4; i++){
			next_freq[i] = desired_freq/freq_options[i];
			//std::cout << next_freq[i] << std::endl;

		if(freq_choice > next_freq[i]){
			freq_choice = next_freq[i];
			index = i;
			}
		}
		std::cout << "The next frequency to be set is: " << desired_freq << std::endl;
		std::cout << std::endl;
		//write desired_freq to scaling_setspeed file
		std::ofstream outfile;
		outfile.open("/sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed");
		outfile << desired_freq;
		outfile.close();

		}
	else {
		std::cout << "Couldn't open file\n";
		}
	}
	return 0;      
}
