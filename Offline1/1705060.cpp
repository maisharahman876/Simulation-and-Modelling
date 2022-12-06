#include<bits/stdc++.h>
#define BUSY 1 /* Mnemonics for server's being busy */
#define IDLE 0
using namespace std;
#include "lcgrand.h"
//single server queue simulation

int next_event_type, num_custs_delayed, num_delays_required, num_events,
 num_in_q, server_status;
float area_num_in_q, area_server_status, mean_interarrival, mean_service,
 sim_time,  time_last_event, next_arrival_time, next_departure_time,
 total_of_delays;
  ofstream outfile;
 //define a dynamic queue
queue<float> time_arrival;
//function prototypes
void initialize(void);
void timing(void);
void arrive(void);
void depart(void);
void report(void);
void update_time_avg_stats(void);
float expon(float mean);

void initialize()
{
    sim_time = 0.0;
    server_status = IDLE;
    num_in_q = 0;
    time_last_event = 0.0;
    num_custs_delayed = 0;
    total_of_delays = 0.0;
    area_num_in_q = 0.0;
    area_server_status = 0.0;

    next_arrival_time = sim_time + expon(mean_interarrival);
    next_departure_time = 1.0e+30;
}
float expon(float mean)
{
    return -mean * log(lcgrand(1));
}
void timing()
{
    int i;
    float min_time_next_event = 1.0e+29;
    next_event_type = 0;
    //determine the event type of the next event to occur
    if(next_arrival_time < min_time_next_event)
    {
        min_time_next_event = next_arrival_time;
        next_event_type = 1;
    }
    if(next_departure_time < min_time_next_event)
    {
        min_time_next_event = next_departure_time;
        next_event_type = 2;
    }
    if(next_event_type == 0)
    {
        cout<<"Event list empty at time"<<sim_time<<endl;
        exit(1);
    }
    sim_time = min_time_next_event;
}
void update_time_avg_stats()
{
    float time_since_last_event;
    time_since_last_event = sim_time - time_last_event;
    time_last_event = sim_time;
    area_num_in_q += num_in_q * time_since_last_event;
    area_server_status += server_status * time_since_last_event;
}
void arrive()
{
    float delay;
    next_arrival_time = sim_time + expon(mean_interarrival);
    if(server_status == BUSY)
    {
        num_in_q++;
        time_arrival.push(sim_time);
    }
    else
    {
        delay = 0.0;
        total_of_delays += delay;
        num_custs_delayed++;
        server_status = BUSY;
        next_departure_time = sim_time + expon(mean_service);
    }
}
void depart()
{
    float delay;
    if(num_in_q == 0)
    {
        server_status = IDLE;
        next_departure_time = 1.0e+30;
    }
    else
    {
        num_in_q--;
        delay = sim_time - time_arrival.front();
        time_arrival.pop();
        total_of_delays += delay;
        num_custs_delayed++;
        next_departure_time = sim_time + expon(mean_service);
    }
}
void report()
{
   
    outfile<<"Average delay in queue =  "<<total_of_delays/num_custs_delayed<<" minutes"<<endl<<endl;
    outfile<<"Average number in queue = "<<area_num_in_q/sim_time<<endl<<endl;
    outfile<<"Server utilization =  "<<area_server_status/sim_time<<endl<<endl;
    outfile<<"Time simulation ended =   "<<sim_time<<" minutes"<<endl<<endl;
}

int main()
{
    //take input from file
    ifstream infile;
    infile.open("mm1.in");
    infile>>mean_interarrival>>mean_service>>num_delays_required;

    //output file

    outfile.open("mm1.out");

    num_events = 2;
    //write report heading and input parameters
    outfile<<"Single-server queueing system"<<endl<<endl;
    outfile<<"Mean interarrival time = "<<mean_interarrival<<" minutes"<<endl<<endl;
    outfile<<"Mean service time = "<<mean_service<<" minutes"<<endl<<endl;
    outfile<<"Number of customers = "<<num_delays_required<<endl<<endl<<endl<<endl;


    //initialize the simulation
    initialize();
    //run the simulation while more delays are still needed
    while(num_custs_delayed < num_delays_required)
    {
        //determine the next event
        timing();
        //update time-average statistical accumulators
        update_time_avg_stats();
        //invoke the appropriate event function
        switch(next_event_type)
        {
            case 1:
                arrive();
                break;
            case 2:
                depart();
                break;
        }
    }
    //invoke the report generator and end the simulation
    report();
    outfile.close();
    infile.close();
    return 0;

}
