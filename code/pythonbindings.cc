
#include "application/stdneb.h"
#include "pythonbindings.h"
#include "pybind11/pybind11.h"
#include "pybind11/operators.h"
#include "pybind11/cast.h"
#include "pybind11/embed.h"
#include "io/console.h"
#include "math/mat4.h"
#include "camera.h"
#include "basegamefeature/managers/entitymanager.h"
#include "basegamefeature/properties/transform.h"
#include "graphicsfeature/graphicsfeatureunit.h"
#include "managers/playermanager.h"

namespace Python
{
	namespace py = pybind11;

	PYBIND11_EMBEDDED_MODULE(cmds, m)
	{
		m.def("SetCameraPos",
			[](Math::point pos)->void
			{
				Demo::PlayerManager::Instance()->GetCamera()->MoveTo(pos);
				IO::Console::Instance()->Print("YO");
			}
		);

		m.def("ChangeFOV",
			[](float newFOV)->void
			{
				if (newFOV <= 0 || newFOV >= 180) {
					IO::Console::Instance()->Print("ERROR: FOV value out of bounds");
					return;
				}
				GraphicsFeature::Camera temp = Game::GetProperty<GraphicsFeature::Camera>(Demo::PlayerManager::Instance()->GetPlayerEntity(), Game::GetPropertyId("Camera"_atm));
				temp.fieldOfView = newFOV;
				Game::SetProperty<GraphicsFeature::Camera>(Demo::PlayerManager::Instance()->GetPlayerEntity(), Game::GetPropertyId("Camera"_atm), temp);
				IO::Console::Instance()->Print("YO");
			}
		);

		m.def("SpawnCubeAt",
			[](Math::point pos)->void
			{
				Game::EntityCreateInfo info;
				info.immediate = true;
				info.templateId = Game::GetTemplateId("MovingEntity/cube"_atm);
				Game::Entity entity = Game::CreateEntity(info);
				Game::SetProperty(entity, Game::GetPropertyId("WorldTransform"_atm), Math::translation({ pos.x, pos.y, pos.z }));
				IO::Console::Instance()->Print("YO");
			}
		);
	}
}
