#include <DYEngine\graphics\MaterialAttribute.h>

namespace DYE
{
	RenderPass::RenderPass()
	{

	}

	RenderPass::~RenderPass()
	{
		for (auto const& uniform : Uniforms)
		{
			delete uniform;
		}
	}

	std::vector<std::string> StringTokenizer(std::string str, std::string delim, bool igEmptyTok)
	{
		std::vector<std::string> ret;
		size_t start = 0;
		size_t end;

		while ((end = str.find_first_of(delim.c_str(), start)) != std::string::npos)
		{
			std::string sub = str.substr(start, end - start);
			if (sub == "" && igEmptyTok)
				;
			else
				ret.push_back(sub);
			start = end + 1;
		}

		std::string sub = str.substr(start, end);
		if (sub == "" && igEmptyTok)
			;
		else
			ret.push_back(sub);
		return ret;
	}
}