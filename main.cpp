#include<iostream>
#include<conio.h>
#include<time.h>
#include<math.h>
#include<list>
#include<vector>
#include<stdlib.h>
using namespace std;

#define sim_time 72000

int waiting_time_calculation ();
int inter_arrival_time_calculation();
int determine_next_event(int *, int &);

//1 is for arrival
//2 and 3 will determine burst or not

int main()
{
	//srand(time(NULL));
	int Event_identifier[3], burst,time_s,count=0,next_iteration,inter_arrival_time;
	int gender;
	int burst_length = 0;
	int waiting_time = 0;
	int next_event_time = 0;
	int smallest_identifier;
	list<int>::iterator j;
	list<int> counter_boys;
	list<int> counter_girls;
	list<int> wait_boys;
	list<int> wait_girls;
	vector<int> counter_boys_dep;
	vector<int> counter_girls_dep;
	int event_times[3];

	Event_identifier[0] = 1;
	Event_identifier[1] = 0;
	Event_identifier[2] = 0;

	for (int i = 0; i < sim_time; i++)
	{
	    // Arrival of a student.
		if (i == next_event_time && Event_identifier[0] == 1)
		{
			burst = rand() % 2 + 2;

			//When there is no burst.
			if (burst == 3)
			{
			    gender = rand()%2;
				time_s = i;
				if (gender == 0)
                {
				if(counter_girls.size()<30)
                {
                    if (wait_girls.size()==0)
                    {
                        counter_girls.push_back(time_s);
                    }

                    else
                    {
                        wait_girls.push_back(time_s);
                    }
                }
                else
                {
                    wait_girls.push_back(time_s);
                }

                waiting_time = waiting_time_calculation ();

                counter_girls_dep.push_back(time_s+waiting_time);

                count++;
			}
			else
            {
              if(counter_boys.size()<30)
                {
                    if (wait_boys.size()==0)
                    counter_boys.push_back(time_s);

                    else
                    {
                        wait_boys.push_back(time_s);
                    }
                }
                else
                {
                    wait_boys.push_back(time_s);
                }

                count++;

                waiting_time = waiting_time_calculation ();

                counter_boys_dep.push_back(time_s+waiting_time);
			}
			}

			// Burst occurs at this point.
			else
			{
				burst_length = rand() % 10 + 1;

				time_s = i;

				for (int k = 0; k < burst_length; k++)
				{
				    gender = rand()%2;
				    // Condition to check the size of the student queue
					if(gender == 0)
                    {
					if (counter_girls.size()<30)
                    {
                        // insertion in the student queue
                        if(wait_girls.size()==0)
                        counter_girls.push_back(time_s);


                        //Insertion in waiting queue
                        else
                        wait_girls.push_back(time_s);
                    }

                    // insertion in waiting queue
                    else
                    {
                        wait_girls.push_back(time_s);
                    }

                    waiting_time = waiting_time_calculation ();

                    counter_girls_dep.push_back(time_s+waiting_time);

                    count++;
				}
				else
                {
                    if (counter_boys.size()<30)
                    {
                        // insertion in the student queue
                        if(wait_boys.size()==0)
                        counter_boys.push_back(time_s);


                        //Insertion in waiting queue
                        else
                        wait_boys.push_back(time_s);
                    }

                    // insertion in waiting queue
                    else
                    {
                        wait_boys.push_back(time_s);
                    }

                    waiting_time = waiting_time_calculation ();

                    counter_boys_dep.push_back(time_s+waiting_time);

                    count++;
                }

				}
			}
		}

		if (i == next_event_time && Event_identifier[1] == 1)
        {
            counter_boys.pop_front();
        }

        if (i == next_event_time && Event_identifier[2] == 1)
        {
            counter_girls.pop_front();
        }

        if (i == next_event_time)
        {
            Event_identifier[0] = 1;
        }
        else
            Event_identifier[0] = 0;

        if (event_times[1] == next_event_time)
        {
            Event_identifier[1] = 1;
        }
        else
            Event_identifier[1] = 0;

        if (event_times[2] == next_event_time)
        {
            Event_identifier[2] = 1;
        }
        else
            Event_identifier[2] = 1;

        inter_arrival_time = inter_arrival_time_calculation();
        next_arrival_time = time_s + inter_arrival_time;
        event_times[0] = next_arrival_time;

        next_departure_time_boys = counter_boys_dep.pop_back();
        next_departure_time_girls = counter_girls_dep.pop_back();
        event_times[1] = next_departure_time_boys;
        event_times[2] = next_departure_time_girls;

        next_event_time = determine_next_event(event_times,smallest_identifier);

        if (smallest_identifier == 4)
        {
            Event_identifier[0] = 1;
            Event_identifier[1] = 1;
            Event_identifier[2] = 1;
        }

        else
        {
            Event_identifier[smallest_identifier] = 1;
        }
	}

	/* for (j = Student.begin(); j != Student.end(); j++)
		cout << *j << endl; */


	cout << count;
return 0;
}



int waiting_time_calculation()
{
        //Finding the gaussian distributed waiting time using z-score table through file handling
        int waiting_time = wait_time_departure - wait_time_arrival;
        return waiting_time;
}


int inter_arrival_time_calculation()
{
    //Finding the guassian distributed inter arrival time using the z-score table through file handling
}


int determine_next_event(int *ptr, int &smallest_identifier)
{
    int smallest = 73000;
    int counter = 0;

    for (int i=0; i<3; i++)
    {
        if (*(ptr+i)<smallest)
        {
            smallest = *(ptr+i);
            smallest_identifier = i;
        }
        else if (*(ptr+i) == smallest)

            counter ++;
    }

    if (counter == 3)
    {
        smallest_identifier = counter+1;
    }

    return smallest;
}
