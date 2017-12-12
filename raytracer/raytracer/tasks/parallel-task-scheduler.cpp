#include "tasks/parallel-task-scheduler.h"
#include <thread>
#include <atomic>
#include <iostream>
using namespace tasks;
using namespace std;

namespace
{
	/// <summary>
	/// Performs tasks one after the other (i.e. not in parallel).
	/// </summary>
	class ParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
	{
	public:
		void perform(std::vector<std::shared_ptr<Task>> tasks) const
		{
			atomic<int> inte;
		}
	};
}

TaskScheduler tasks::schedulers::parallel()
{
	return TaskScheduler(std::make_shared<ParallelTaskScheduler>());
}