#pragma once
#include <string>
#include "glm\glm.hpp"

namespace Common {
	class FormattingHelper {
	private:
		FormattingHelper();
	public:
		~FormattingHelper();
	
		static std::string getFormattedVectorString(glm::vec3 vector);
	};
}