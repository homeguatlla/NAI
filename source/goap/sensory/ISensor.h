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

			//TODO este m�todo no hace falta realmente. En alg�n momento el sensor tiene
			//que recorrer todos sus suscriptores y ejecutar el notify. No hace falta especificar un m�todo
			//para ello. Quiz� hay que crear un SensorBase con ese c�digo.
			virtual void Update(float elapsedTime) = 0;
		};
	}
}
