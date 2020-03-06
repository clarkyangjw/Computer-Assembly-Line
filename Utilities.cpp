#include "Utilities.h"

size_t Utilities::m_widthField{ 1 };

char Utilities::m_delimiter{ '\0' };

Utilities::Utilities() {

}

void Utilities::setFieldWidth(size_t width) {
	this->m_widthField = { width };
}

size_t Utilities::getFieldWidth() const {
	return this->m_widthField;
}

void Utilities::setDelimiter(const char delimiter) {
	m_delimiter = { delimiter };
}

const char Utilities::getDelimiter() const {
	return this->m_delimiter;
}

const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	std::string token{ "" };
	if (str.find(this->m_delimiter, next_pos) != std::string::npos) {									//checks if there is delimiter
		token = str.substr(next_pos, str.find(this->m_delimiter, next_pos) - next_pos);	//extracts token from str
		next_pos = str.find(this->m_delimiter, next_pos) + 1;												//update the next positon
		if (this->m_widthField < token.length()) {																	
			this->m_widthField = token.length();																	//update the width field
		}
		more = true;
	}
	else {
		token = str.substr(next_pos, str.length() - next_pos);												//if there is no delimiter left, extracts the rest string
		next_pos = str.length();
		more = false;
	}
	if ((str.find(this->m_delimiter) - next_pos) == 0) {														//checks if there is nothing between two delimiter
		throw "Error! There is nothing between two delimiter.";
	}
	return token;
}

const size_t Utilities::numDelimiter(const std::string& record)const {
	size_t count = 0, position = 0;
	while ((position = record.find(this->getDelimiter(), position)) != std::string::npos) {
		position++;
		count++;
	}
	return count == 0 ? 0 : count;
}


