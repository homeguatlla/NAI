#pragma once

#include <list>
#include <memory>
#include <functional>

namespace NAI
{
	namespace Goap
	{
		template<class T>
		class Memory
		{		
		public:
			Memory();
			~Memory() = default;

			void Add(std::shared_ptr<T> data);
			void Add(std::shared_ptr<T> data, float time);
			void Update(float elapsedTime);
			void PerformActionForEach(std::function<void(std::shared_ptr<T> element)> action);
			
			//Test purposes
			bool IsEmpty() const { return permanentMemory.empty() && temporaryMemory.empty(); }

		private:
			std::list<std::shared_ptr<T>> permanentMemory;
			std::list<std::pair<std::shared_ptr<T>, float>> temporaryMemory;
		};

		template<class T>
		Memory<T>::Memory()
		{
		}

		template<class T>
		void Memory<T>::Add(std::shared_ptr<T> data)
		{
			permanentMemory.push_back(data);
		}

		template<class T>
		void Memory<T>::Add(std::shared_ptr<T> data, float time)
		{
			temporaryMemory.push_back(std::make_pair(data, time));
		}
		
		template<class T>
		void Memory<T>::Update(float elapsedTime)
		{
			for(auto it = temporaryMemory.begin(); it != temporaryMemory.end();)
			{
				auto& pair = *it;
				pair.second -= elapsedTime;
				if(pair.second <= 0.0f)
				{
					it = temporaryMemory.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		template<class T>
		void Memory<T>::PerformActionForEach(std::function<void(std::shared_ptr<T> element)> action)
		{
			for(auto&& element : permanentMemory)
			{
				action(element);
			}
			for(auto&& element : temporaryMemory)
			{
				action(element.first);
			}
		}
	}
}
