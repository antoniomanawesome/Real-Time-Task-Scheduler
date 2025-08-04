#ifndef TASK_H
#define TASK_H
struct Task{
            int ID;             // Task ID
            int priority;       // Task priority
            int period;         // Period of task (0 is aperiodic, >0 is periodic)
            int next_run_time;  // When the task is scheduled to run next

            Task() : ID(0), priority(0), period(0), next_run_time(0) {}     // Default task constructor
            Task(int ID, int priority, int period, int run_time): ID(ID),   // Parameterized task constructor
            priority(priority), period(period), next_run_time(run_time)  {}
        };

#endif
