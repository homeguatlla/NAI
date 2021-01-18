#pragma once

#include <list>
#include <memory>
#include <functional>

namespace NAI
{
	namespace Goap
	{
		template<class T>
		class ShortTermMemory
		{
		public:
			ShortTermMemory();
			~ShortTermMemory() = default;

			void Add(std::shared_ptr<T> data, float time);
			void AddOrReplace(std::shared_ptr<T> data, float time);
			
			void Update(float elapsedTime);
			void PerformActionForEach(std::function<bool(std::shared_ptr<T> element)> action) const;
			size_t GetSize() const { return mMemory.size(); }
			bool IsEmpty() const { return mMemory.empty(); }
		
		private:
			void UpdateTemporaryMemory(float elapsedTime);
			
		private:
			std::list<std::pair<std::shared_ptr<T>, float>> mMemory;
		};

		template<class T>
		ShortTermMemory<T>::ShortTermMemory()
		{
		}

		template<class T>
		void ShortTermMemory<T>::Add(std::shared_ptr<T> data, float time)
		{
			mMemory.push_back(std::make_pair(data, time));
		}

		template <class T>
		void ShortTermMemory<T>::AddOrReplace(std::shared_ptr<T> data, float time)
		{
			auto it = std::find_if(mMemory.begin(), mMemory.end(),
				[data](const std::pair<std::shared_ptr<T>, float> element)
				{
					return data->GetId() == element.first->GetId();
				});

			if(it != mMemory.end())
			{
				it->first = data;
				it->second = time; //the time is renoved
			}
			else
			{
				Add(data, time);
			}
		}

		template<class T>
		void ShortTermMemory<T>::Update(float elapsedTime)
		{
			UpdateTemporaryMemory(elapsedTime);
		}
		
		template<class T>
		void ShortTermMemory<T>::PerformActionForEach(std::function<bool(std::shared_ptr<T> element)> action) const
		{
			//TODO o borrar el bool, pues no lo estamos usando
			//o, cuando action devuelva true, interrumpir el bucle
			for(auto&& element : mMemory)
			{
				action(element.first);
			}
		}

		template <class T>
        void ShortTermMemory<T>::UpdateTemporaryMemory(float elapsedTime)
		{
			for(auto it = mMemory.begin(); it != mMemory.end();)
			{
				auto& pair = *it;
				pair.second -= elapsedTime;
				if(pair.second <= 0.0f)
				{
					it = mMemory.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
	}
}
