#pragma once
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class ISensorSubscriber;
		
		class ISensor
		{		
		public:
			virtual ~ISensor() = default;
			virtual void Subscribe(const std::shared_ptr<ISensorSubscriber> subscriber) = 0;

			//TODO este método no hace falta realmente. En algún momento el sensor tiene
			//que recorrer todos sus suscriptores y ejecutar el notify. No hace falta especificar un método
			//para ello. Quizá hay que crear un SensorBase con ese código.
			virtual void Update(float elapsedTime) = 0;
		};
	}
}
