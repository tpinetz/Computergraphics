#pragma once
#include "MainHeaders.h"

namespace Common {
	class FormattingHelper {
	private:
		FormattingHelper();
	public:
		~FormattingHelper();
	
		static std::string getFormattedVectorString(glm::vec3 vector);
	};
}