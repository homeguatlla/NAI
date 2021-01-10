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
			void PerformActionForEach(std::function<bool(std::shared_ptr<T> element)> action);
			
			//Test purposes
			bool IsEmpty() const { return mPermanentMemory.empty() && mTemporaryMemory.empty(); }

		private:
			std::list<std::shared_ptr<T>> mPermanentMemory;
			std::list<std::pair<std::shared_ptr<T>, float>> mTemporaryMemory;
		};

		template<class T>
		Memory<T>::Memory()
		{
		}

		template<class T>
		void Memory<T>::Add(std::shared_ptr<T> data)
		{
			mPermanentMemory.push_back(data);
		}

		template<class T>
		void Memory<T>::Add(std::shared_ptr<T> data, float time)
		{
			mTemporaryMemory.push_back(std::make_pair(data, time));
		}
		
		template<class T>
		void Memory<T>::Update(float elapsedTime)
		{
			for(auto it = mTemporaryMemory.begin(); it != mTemporaryMemory.end();)
			{
				auto& pair = *it;
				pair.second -= elapsedTime;
				if(pair.second <= 0.0f)
				{
					it = mTemporaryMemory.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		template<class T>
		void Memory<T>::PerformActionForEach(std::function<bool(std::shared_ptr<T> element)> action)
		{
			for(auto element = mPermanentMemory.begin(); element != mPermanentMemory.end();)
			{
				const auto used = action(*element);
				if(used)
				{
					//if used removed from memory because we have generated a predicate instead.
					element = mPermanentMemory.erase(element);
				}
				else
				{
					++element;
				}
			}
			
			for(auto&& element : mTemporaryMemory)
			{
				const auto used = action(element.first);
				if(used)
				{
					//to be removed later because we have generated a predicate instead.
					element.second = 0.0f;
				}
			}
		}
	}
}
