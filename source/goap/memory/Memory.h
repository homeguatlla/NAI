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
			void PerformActionForEach(std::function<bool(std::shared_ptr<T> element)> action) const;
			
			//Test purposes
			bool IsEmpty() const { return mInstantMemory.empty() && mTemporaryMemory.empty(); }
		private:
			void UpdateTemporaryMemory(float elapsedTime);
			
		private:
			std::list<std::shared_ptr<T>> mInstantMemory;
			std::list<std::pair<std::shared_ptr<T>, float>> mTemporaryMemory;
		};

		template<class T>
		Memory<T>::Memory()
		{
		}

		template<class T>
		void Memory<T>::Add(std::shared_ptr<T> data)
		{
			mInstantMemory.push_back(data);
		}

		template<class T>
		void Memory<T>::Add(std::shared_ptr<T> data, float time)
		{
			mTemporaryMemory.push_back(std::make_pair(data, time));
		}

		template<class T>
		void Memory<T>::Update(float elapsedTime)
		{
			UpdateTemporaryMemory(elapsedTime);
			mInstantMemory.clear();
		}
		
		template<class T>
		void Memory<T>::PerformActionForEach(std::function<bool(std::shared_ptr<T> element)> action) const
		{
			for(auto&& element : mInstantMemory)
			{
				action(element);
			}
			
			for(auto&& element : mTemporaryMemory)
			{
				action(element.first);
			}
		}

		template <class T>
        void Memory<T>::UpdateTemporaryMemory(float elapsedTime)
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
	}
}
