#include <string>

class Utilities {
	/**
 * Splits a given string to an array of strings using a provided delimited 'c'. python style.
 */
public:
	static std::string* split(char c, std::string str) {
		// first count the number of times the delimeter char appears in the string
		// to determine the size of the output array.
		int numOfChars = 0;
		int right = str.find(c);
		int left = 0;

		while (right != std::string::npos) {
			numOfChars++;
			left = right;
			right = str.find(c, left + 1);
		}

		// number of delimiters + 1 = number of values
		std::string *frags = new std::string[numOfChars + 1];

		// cut the values in between the delimiters
		// right boundary = the next delimeter
		// left boundary = prev  right boundary + 1	
		right = str.find(c);
		left = 0;

		int i = 0;
		for (; i < numOfChars; i++) {
			frags[i] = str.substr(left, right - left);
			left = right + 1;
			right = str.find(c, left);
		}

		// cut last value until the end (no more delimeters)
		frags[i] = str.substr(left);

		return frags;
	}
};