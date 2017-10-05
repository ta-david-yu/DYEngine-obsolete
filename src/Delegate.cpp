#include <DYEngine\utilities\Delegate.h>

namespace DYE
{
	int test(int input)
	{
		return input;
	}

	Delegate<int, int> testDelegate(test);
}