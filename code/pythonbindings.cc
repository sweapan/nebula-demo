
#include "application/stdneb.h"
#include "pythonbindings.h"
#include "pybind11/pybind11.h"
#include "pybind11/operators.h"
#include "pybind11/cast.h"
#include "pybind11/embed.h"
#include "io/console.h"
#include "math/mat4.h"
#include "camera.h"

namespace Python
{
	namespace py = pybind11;

	PYBIND11_EMBEDDED_MODULE(example, m)
	{
		m.def("SetCameraPos",
			[](Math::vec3 pos)->void
			{
				//Singleton->camera.Setup({ 0, 5, -3 }, { 0,1,0 });
				IO::Console::Instance()->Print("YO");
			}
		);

		m.def("ChangeFOV",
			[]()->void
			{
				IO::Console::Instance()->Print("YO");
			}
		);

		m.def("SpawnCubeAt",
			[]()->void
			{
				IO::Console::Instance()->Print("YO");
			}
		);
	}
}
