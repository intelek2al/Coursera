#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus
{
	NEW,		 // новая
	IN_PROGRESS, // в разработке
	TESTING,	 // на тестировании
	DONE		 // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// // позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

void PrintTasksInfo(TasksInfo tasks_info)
{
	cout << tasks_info[TaskStatus::NEW] << " new tasks"
		 << ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
		 << ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested"
		 << ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

// void PrintTasksInfo(const TasksInfo &tasks_info);

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
			// if (status.first == TaskStatus::TESTING)
			//     cout << "::: @@@@@  @@@@@ ::: " << change_task << " " << task_count << " " << status.second << " " << endl;
			int new_change_task = change_task;
			if (status.first != TaskStatus::DONE)
			{
				if (status.second >= task_count)
				{
					change_task = task_count;
					status.second -= task_count;
					task_count = 0;
				}
				else if (status.second < task_count)
				{
					change_task = status.second;
					task_count -= status.second;
					status.second = 0;
				}
			}
			if (new_change_task >= 0)
			{
				// cout << "::: @@@@@ added @@@@@ ::: " << change_task << endl;
				status.second += new_change_task;
				if (new_change_task != 0)
					new_stat[status.first] = new_change_task;
				new_change_task = 0;
			}
			else
				break;

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

// void PrintTasksInfo(const TasksInfo &tasks_info)
// {
// 	if (tasks_info.count(TaskStatus::NEW))
// 	{
// 		std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
// 	}
// 	if (tasks_info.count(TaskStatus::IN_PROGRESS))
// 	{
// 		std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
// 	}
// 	if (tasks_info.count(TaskStatus::TESTING))
// 	{
// 		std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
// 	}
// 	if (tasks_info.count(TaskStatus::DONE))
// 	{
// 		std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
// 	}
// }

// void PrintTasksInfo(const TasksInfo &updated_tasks, const TasksInfo &untouched_tasks)
// {
// 	std::cout << "Updated: [";
// 	PrintTasksInfo(updated_tasks);
// 	std::cout << "] ";

// 	std::cout << "Untouched: [";
// 	PrintTasksInfo(untouched_tasks);
// 	std::cout << "] ";

// 	std::cout << std::endl;
// }

int main()
{
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i)
	{
		tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	return 0;
}
