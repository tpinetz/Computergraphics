#include "FormattingHelper.h"

namespace Common {
	FormattingHelper::FormattingHelper() {

	}

	FormattingHelper::~FormattingHelper() {

	}

	std::string FormattingHelper::getFormattedVectorString(glm::vec3 vector) {
		return "(" + std::to_string(vector.x) + "," + std::to_string(vector.y) 
			+ "," + std::to_string(vector.z) + ")";
	}

}