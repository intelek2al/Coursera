#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus
{
    NEW,         // новая
    IN_PROGRESS, // в разработке
    TESTING,     // на тестировании
    DONE         // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

// void PrintTasksInfo(TasksInfo tasks_info)
// {
//     cout << tasks_info[TaskStatus::NEW] << " new tasks"
//          << ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
//          << ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested"
//          << ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
// }

void PrintTasksInfo(const TasksInfo &tasks_info);

class TeamTasks
{
    map<string, TasksInfo> table;

public:
    const TasksInfo GetPersonTasksInfo(const string &person) const
    {
        TasksInfo answ(table.at(person));
        for (auto i = answ.begin();;)
        {
            if (i->second == 0)
                i = answ.erase(i);
            else
                i++;
            if (i == answ.end())
                break;
        }
        return answ;
    }

    void InitWorkspace(const string &person)
    {
        table[person][TaskStatus::NEW] = 0;
        table[person][TaskStatus::IN_PROGRESS] = 0;
        table[person][TaskStatus::TESTING] = 0;
        table[person][TaskStatus::DONE] = 0;
    }
    void AddNewTask(const string &person)
    {
        if (table.count(person) == 0)
            InitWorkspace(person);
        table[person][TaskStatus::NEW]++;
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count)
    {
        // cout << "\n++++++++++++++++++++++++++++++++\n";
        TasksInfo new_stat;
        TasksInfo old_stat;
        int change_task = 0;

        if (table.count(person) == 0)
            return make_tuple(new_stat, old_stat);
        for (auto &status : table[person])
        {
            int temp = status.second;
            if (change_task >= 0)
            {
                // cout << "::: @@@@@ added @@@@@ ::: " << change_task << endl;
                status.second += change_task;
                if (change_task != 0)
                    new_stat[status.first] = change_task;
                change_task = 0;
            }
            else
                break;
            // if (status.first == TaskStatus::TESTING)
            //     cout << "::: @@@@@  @@@@@ ::: " << change_task << " " << task_count << " " << status.second << " " << endl;
            if (task_count >= 0 && status.first != TaskStatus::DONE && temp != 0)
            {
                // int tmp = status.second;
                change_task = temp;
                status.second -= task_count;
                if (status.first == TaskStatus::TESTING)
                    cout << "::: @@@@@ DONE @@@@@ ::: " << change_task << " " << task_count << " " << status.second << " " << endl;
                if (status.second <= 0)
                {
                    task_count = -status.second;
                    status.second = 0;
                }
                else
                {
                    change_task = task_count;
                    task_count = 0;
                }
                // if (status.first == TaskStatus::TESTING)
                //     cout << ":::::::::::  " << change_task << " " << task_count << endl;
                // change_task = -task_count;
                // cout << "::::: NEW ::::: ";
                // PrintTasksInfo(new_stat);
                // cout << "::::: OLD ::::: ";
                // PrintTasksInfo(old_stat);
                // cout << "::: SWAP TO NEXT ::: " << change_task << endl;
            }

            if (status.first != TaskStatus::DONE)
                old_stat[status.first] = (status.second - new_stat[status.first]) < 0 ? 0 : status.second - new_stat[status.first];
        }
        for (auto i = new_stat.begin();;)
        {
            if (i->second == 0)
                i = new_stat.erase(i);
            else
                i++;
            if (i == new_stat.end())
                break;
        }
        for (auto i = old_stat.begin();;)
        {
            if (i->second == 0)
                i = old_stat.erase(i);
            else
                i++;
            if (i == old_stat.end())
                break;
        }

        // cout << "\n++++++++++++++++++++++++++++++++\n";
        return make_tuple(new_stat, old_stat);
    }
};

void PrintTasksInfo(const TasksInfo &tasks_info)
{
    if (tasks_info.count(TaskStatus::NEW))
    {
        std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
    }
    if (tasks_info.count(TaskStatus::IN_PROGRESS))
    {
        std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
    }
    if (tasks_info.count(TaskStatus::TESTING))
    {
        std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
    }
    if (tasks_info.count(TaskStatus::DONE))
    {
        std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
    }
}

void PrintTasksInfo(const TasksInfo &updated_tasks, const TasksInfo &untouched_tasks)
{
    std::cout << "Updated: [";
    PrintTasksInfo(updated_tasks);
    std::cout << "] ";

    std::cout << "Untouched: [";
    PrintTasksInfo(untouched_tasks);
    std::cout << "] ";

    std::cout << std::endl;
}

int main()
{
    TeamTasks tasks;
    TasksInfo updated_tasks;
    TasksInfo untouched_tasks;

    /* TEST 1 */
    std::cout << "Alice" << std::endl;

    for (auto i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"TESTING": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"DONE": 1}, {"TESTING": 4}]

    for (auto i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
                                                                   2); // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
    PrintTasksInfo(updated_tasks, untouched_tasks);

    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice")); // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice")); // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    std::cout << std::endl;

    /* TEST 2 */
    std::cout << "\nJack" << std::endl;

    tasks.AddNewTask("Jack");

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 1}, {}]

    tasks.AddNewTask("Jack");

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

    tasks.AddNewTask("Jack");

    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack")); // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack")); // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
    std::cout << std::endl;

    /* TEST 3 */
    std::cout << "\nLisa" << std::endl;

    for (auto i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Lisa");
    }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"TESTING": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"DONE": 1}, {"TESTING": 4}]

    for (auto i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Lisa");
    }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"TESTING": 8, "DONE": 2}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"DONE": 8}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"DONE": 10}
    std::cout << std::endl;

    tasks.AddNewTask("Lisa");

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"NEW": 1, "DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 1}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"IN_PROGRESS": 1, "DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks); // [{}, {}]

    return 0;
}
