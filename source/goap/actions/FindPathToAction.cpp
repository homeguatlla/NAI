#include "pch.h"
#include "FindPathToAction.h"

namespace NAI
{
	namespace Goap
	{
		FindPathToAction::FindPathToAction(
			const std::vector<std::shared_ptr<IPredicate>>& preConditions,
			const std::vector<std::shared_ptr<IPredicate>>& postConditions) :
			BaseAction(preConditions, postConditions, 0)
		{
			mHasAccomplished = false;
		}

		void FindPathToAction::Process(float elapsedTime)
		{
			//obtener el predicado GoToX, 
			//obtener el lugar dado el predicado X lo puede tener el mismo predicado
			//pedir al navigation planner si puede obtener camino hasta el lugar X
			//usar tantos frames como haga falta
			//terminar con la lista de nodos del camino.
		}
	}
}
