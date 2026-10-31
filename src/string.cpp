#include "string.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

// helpers
int String::strlen(const char * s) {
    int count = 0;
    while (s[count] != '\0') {
        count++;
    }
    return count;
}

char * String::strcpy(char * dest, const char * src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char * String::strncpy(char * dest, const char * src, int n) {
    int i = 0;
    while (src[i] != '\0' && i < n) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int String::strcmp(const char * left, const char * right) {
    int i = 0;
    while (left[i] != '\0' && left[i] == right[i]) {
        i++;
    }
    return left[i] - right[i];
}

int String::strncmp(const char * left, const char * right, int n) {
    int i = 0;
    while (i < n && left[i] != '\0' && left[i] == right[i]) {
        i++;
    }
    if (i == n) {
        return 0;
    }
    return left[i] - right[i];
}

const char * String::strchr(const char * str, char c) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == c) {
            return &str[i];
        }
        i++;
    }
    if (c == '\0') {
        return &str[i];
    }
    return nullptr;
}

const char * String::strstr(const char * haystack, const char * needle) {
    if (needle[0] == '\0') {
        return haystack;
    }
    int i = 0;
    while (haystack[i] != '\0') {
        int j = 0;
        while (needle[j] != '\0' && haystack[i + j] == needle[j]) {
            j++;
        }
        if (needle[j] == '\0') {
            return &haystack[i];
        }
        i++;
    }
    return nullptr;
}

char * String::strcat(char * dest, const char * src) {
    int end = 0;
    while (dest[end] != '\0') {
        end++;
    }
    int i = 0;
    while (src[i] != '\0') {
        dest[end + i] = src[i];
        i++;
    }
    dest[end + i] = '\0';
    return dest;
}

char * String::strncat(char * dest, const char * src, int n) {
    int end = 0;
    while (dest[end] != '\0') {
        end++;
    }
    int i = 0;
    while (src[i] != '\0' && i < n) {
        dest[end + i] = src[i];
        i++;
    }
    dest[end + i] = '\0';
    return dest;
}

void String::reverse_cpy(char * dest, const char * src) {
    int len = strlen(src);
    int i = 0;
    while (i < len) {
        dest[i] = src[len - 1 - i];
        i++;
    }
    dest[len] = '\0';
}

char * String::strdup(const char * src) {
	int len = strlen(src) + 1;
	char * heap_str = new char[len];
	strcpy(heap_str, src);
	return heap_str;
}

// constructors
String::String(const char * s) {
    buf = strdup(s);
}

String::String(const String &s) {
    buf = strdup(s.buf);
}

String::String(String &&s) : buf(nullptr) {
    swap(s);
}

// length constructor

String::String(int length) {
	buf = new char[length+1];
}

// Swap
void String::swap(String &s) {
	std::swap(buf, s.buf);
}

// assignment
String &String::operator=(const String &s) {
	String temp(s);
    swap(temp);
    return *this;
}

String &String::operator=(String &&s) {
    swap(s);
    return *this;
}

// destructor
String::~String() {
    delete[] buf;
}

// size
int String::size() const {
    return strlen(buf);
}

// printing
void String::print(ostream &out) const {
    out << buf;
}

ostream &operator<<(ostream &out, const String &s) {
    s.print(out);
    return out;
}

// indexing
char &String::operator[](int index) {
    if (!in_bounds(index)) {
        cout << "ERROR: Index Out Of Bounds" << endl;
        return buf[0];
    }
    return buf[index];
}

const char &String::operator[](int index) const {
	if (!in_bounds(index)) {
		cout << "ERROR: Index Out Of Bounds" << endl;
		return buf[0];
	}
	return buf[index];
}


// comparisons
bool String::operator==(const String &s) const {
    return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(const String &s) const {
    return strcmp(buf, s.buf) != 0;
}

bool String::operator>(const String &s) const {
    return strcmp(buf, s.buf) > 0;
}

bool String::operator<(const String &s) const {
    return strcmp(buf, s.buf) < 0;
}

bool String::operator<=(const String &s) const {
    return strcmp(buf, s.buf) <= 0;
}

bool String::operator>=(const String &s) const {
    return strcmp(buf, s.buf) >= 0;
}

// searching
int String::indexOf(char c) const {
    const char * found = strchr(buf, c);
    if (found == nullptr) {
        return -1;
    }
    return found - buf;
}

int String::indexOf(const String &s) const {
    const char * found = strstr(buf, s.buf);
    if (found == nullptr) {
        return -1;
    }
    return found - buf;
}

// concatenation
String &String::operator+=(String s) {
    String result(size() + s.size());
	strcpy(result.buf, buf);
	strcat(result.buf, s.buf);
	swap(result);
    return *this;
}

String String::operator+(String s) const {
    String result(size() + s.size());
    strcpy(result.buf, buf);
	strcat(result.buf, s.buf);
    return result;
}

// reverse
String String::reverse() const {
    String result(size());
    reverse_cpy(result.buf, buf);
    return result;
}

// reading
void String::read(istream &in) {
    char temp[1024];
	in >> setw(1024) >> temp;
	delete[] buf;
	buf = strdup(temp);
}

istream &operator>>(istream &in, String &s) {
    s.read(in);
    return in;
}
