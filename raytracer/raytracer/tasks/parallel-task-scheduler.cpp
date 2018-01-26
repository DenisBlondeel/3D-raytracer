#include "tasks/parallel-task-scheduler.h"
#include <thread>
#include <atomic>
#include <iostream>
#include "tasks/ctpl/ctpl.h"
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
			// Zodat threads niet undefined gedrag kunnen veroorzaken
			std::atomic<int> atomic = 0;
			std::vector<std::thread> threads;
			for (int threadCount = 0; threadCount < 10; threadCount++)
			{ 
				auto perform = [&tasks, &atomic]
				{
					while (atomic < tasks.size())
					{
						tasks[atomic]->perform();
						atomic++;
					}
				};
				threads.push_back(std::move(std::thread(perform)));
			}
			for (auto& thread : threads)
			{
				thread.join();
			}
			
		}

	};

}

tasks::TaskScheduler tasks::schedulers::parallel()
{
	return TaskScheduler(std::make_shared<ParallelTaskScheduler>());
}