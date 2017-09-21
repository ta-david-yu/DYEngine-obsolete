#include <DYEngine\interfaces\IApplication.h>

namespace DYE
{
	void IApplication::init()
	{
		m_pCore = new Core();
	}
}