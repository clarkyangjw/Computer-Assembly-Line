// Name: Jiawei Yang
// Seneca Student ID: 121134183
// Seneca email: jyang210@myseneca.ca
// Date of completion: October 25, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

class Utilities {
	static size_t m_widthField;
	static char m_delimiter;

public:
	Utilities();
	void setFieldWidth(size_t);
	size_t getFieldWidth() const;
	static void setDelimiter(const char);
	const char getDelimiter() const;
	const std::string extractToken(const std::string& , size_t& , bool& );
	const size_t numDelimiter(const std::string&)const;

};

#endif
