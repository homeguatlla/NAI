#pragma once
#include "IPredicate.h"
#include <string>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class BasePredicate : public IPredicate
		{
		static int IDCounter;

		public:
			explicit BasePredicate(const std::string& text);
			~BasePredicate() = default;
			inline int GetID() const override { return mID; }
			bool IsEqualTo(const std::shared_ptr<IPredicate> predicate) override;
			
			inline std::string GetText() const override { return mText; }
			virtual inline std::string GetFullText() const override { return GetText(); }
		private:
			const int mID;
			std::string mText;
		};
	}
}
