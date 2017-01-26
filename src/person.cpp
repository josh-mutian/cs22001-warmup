#include "person.h"

#include <string>

/**
 * checks if every character in a string is alphabetical
 * 
 * @param str - the string to be examined
 * @return - true if every character is alphabetic; false otherwise
 *
 */
bool str_isalpha(const string str)
{
    int size = str.size();
    for (int i = 0; i < size; i++) {
        if ((isalpha(str[i]) == 0) || (str[i] == ' ')) {
            return false;
        }
    }
    return true;
}

/**
 * checks if every character in a string is alphanumerical (either a number or 
 * a letter)
 * 
 * @param s - the string to be examined
 * @return - true if every character is alphanumerical; false otherwise
 *
 */
bool str_isalnum(const string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && (std::isdigit(*it) || std::isalpha(*it))) {
        ++it;
    }
    return !s.empty() && it == s.end();
}

/**
 * checks if a string is a valid username
 * 
 * @param _username - the string to be examined
 * @return - true if the string is a valid username; false otherwise
 *
 */
bool str_is_valid_username(const string _username)
{
    return str_isalnum(_username) &&
           _username.length() <= 64 &&
           _username.length() > 0 &&
           isalpha(_username[0]);
}

/**
 * checks if a string is a valid first name
 * 
 * @param _firstname - the string to be examined
 * @return - true if the string is a valid first name; false otherwise
 *
 */
bool str_is_valid_firstname(const string _firstname)
{
    return str_isalpha(_firstname) && _firstname.length() <= 64;
}

/**
 * checks if a string is a valid last name
 * 
 * @param _lastname - the string to be examined
 * @return - true if the string is a valid last name; false otherwise
 *
 */
bool str_is_valid_lastname(const string _lastname)
{
    return str_isalpha(_lastname) && _lastname.length() <= 64;
}

/**
 * checks if a string is a valid gender
 * 
 * @param _gender - the string to be examined
 * @return - true if the string is a valid gender; false otherwise
 *
 */
bool str_is_valid_gender(const string _gender)
{
    return _gender == "m" || _gender == "f";
}   

/**
 * checks if an integer is a valid age
 * 
 * @param _age - the integer to be examined
 * @return - true if the integer is a valid age; false otherwise
 *
 */
bool num_is_valid_age(const int _age)
{
    return _age >= 0 && _age < 128;
}

/**
 * checks if a string is a valid tagline
 * 
 * @param _tagline - the string to be examined
 * @return - true if the string is a valid tagline; false otherwise
 *
 */
bool str_is_valid_tagline(const string _tagline)
{
    return _tagline.length() <= 512;
}

/**
 * null Person constructor
 * 
 * Constructs a Person instance with all properties set to 0 or the empty string
 *
 */
Person::Person()
    : username(""), firstname(""), lastname(""), gender(""), age(0),
      tagline("")
{
}

/**
 * Person constructor
 * 
 * @param _username - initial username to be set for the constructed Person
 * @param _firstname - initial firstname to be set for the constructed Person
 * @param _lastname - initial lastname to be set for the constructed Person
 * @param _gender - initial gender to be set for the constructed Person
 * @param _age - initial age to be set for the constructed Person
 * @param _tagline - initial tagline to be set for the constructed Person
 *
 */
Person::Person(string _username, string _firstname, string _lastname,
               string _gender, int _age, string _tagline)
{
    if (str_is_valid_username(_username) && 
        str_is_valid_firstname(_firstname) && 
        str_is_valid_lastname(_lastname) && 
        num_is_valid_age(_age) && 
        str_is_valid_gender(_gender) && 
        str_is_valid_tagline(_tagline)) {
        username = _username;
        firstname = _firstname;
        lastname = _lastname;
        gender = _gender;
        age = _age;
        tagline = _tagline;
    } else {
        username = "";
        firstname = "";
        lastname = "";
        gender = "";
        age = 0;
        tagline = "";
    }
}

/**
 * checks if another Person has the same value set for all properties
 * 
 * @param p - the Person to be compared against
 * @return - true if p and this Person has the same value set for all 
 *           properties ;false otherwise
 *
 */
bool Person::is_same_person(Person p) 
{
    return username == p.get_username() &&
           firstname == p.get_firstname() &&
           lastname == p.get_lastname() &&
           age == p.get_age() &&
           gender == p.get_gender() &&
           tagline == p.get_tagline();
}

/**
 * checks if this Person is a "null" Person, i.e. has all properties set to 0 
 * or the empty string
 * 
 * @return - true if this Person has all properties set to 0 or the empty string
 *           ;false otherwise
 *
 */
bool Person::is_null_person()
{
    return username == "" && lastname == "" && firstname == "" &&
           age == 0 && gender == "" && tagline == "";
}

/**
 * getter method for username property
 * 
 * @return - retreived username value
 *
 */
string Person::get_username()
{
    return username;
}

/**
 * getter method for first name property
 * 
 * @return - retreived first name value
 *
 */
string Person::get_firstname()
{
    return firstname;
}

/**
 * getter method for last name property
 * 
 * @return - retreived last name value
 *
 */
string Person::get_lastname()
{
    return lastname;
}

/**
 * getter method for gender property
 * 
 * @return - retreived gender value
 *
 */
string Person::get_gender()
{
    return gender;
}

/**
 * getter method for age property
 * 
 * @return - retreived age value
 *
 */
int Person::get_age()
{
    return age;
}

/**
 * getter method for username property
 * 
 * @return - retreived username value
 *
 */
string Person::get_tagline()
{
    return tagline;
}

/**
 * returns a string containing all information of this Person
 * 
 * @return - a formatted string of a Person's information
 *
 */
string Person::get_info()
{
    string ret = string("username: ") + username +
                 string(", firstname: ") + firstname +
                 string(", lastname: ") + lastname +
                 string(", age: ") + to_string(age) +
                 string(", gender: ") + gender +
                 string(", tagline: ") + tagline;
    return ret;
}

/**
 * setter method for username property
 * 
 * @param _username - the new username to be set
 * @return - true if the new username is valid and set successfully; false 
 *           otherwise
 *
 */
bool Person::set_username(string _username)
{
    if (str_is_valid_username(_username)) {
        username = _username;
        return true;
    } else {
        return false;
    }
}

/**
 * setter method for first name property
 * 
 * @param _firstname - the new first name to be set
 * @return - true if the new first name is valid and set successfully; false 
 *           otherwise
 *
 */
bool Person::set_firstname(string _firstname)
{
    if (str_is_valid_firstname(_firstname)) {
        firstname = _firstname;
        return true;
    } else {
        return false;
    }
}

/**
 * setter method for last name property
 * 
 * @param _lastname - the new last name to be set
 * @return - true if the new last name is valid and set successfully; false 
 *           otherwise
 *
 */
bool Person::set_lastname(string _lastname)
{
    if (str_is_valid_lastname(_lastname)) {
        lastname = _lastname;
        return true;
    } else {
        return false;
    }
}

/**
 * setter method for gender property
 * 
 * @param _gender - the new gender to be set
 * @return - true if the new gender is valid and set successfully; false 
 *           otherwise
 *
 */
bool Person::set_gender(string _gender)
{
    if (str_is_valid_gender(_gender)) {
        gender = _gender;
        return true;
    } else {
        return false;
    }
}

/**
 * setter method for age property
 * 
 * @param _username - the new age to be set
 * @return - true if the new age is valid and set successfully; false 
 *           otherwise
 *
 */
bool Person::set_age(int _age)
{
    if (num_is_valid_age(_age)) {
        age = _age;
        return true;
    } else {
        return false;
    }
}

/**
 * setter method for tagline property
 * 
 * @param _tagline - the new tagline to be set
 * @return - true if the new tagline is valid and set successfully; false 
 *           otherwise
 *
 */
bool Person::set_tagline(string _tagline)
{
    if (str_is_valid_tagline(_tagline)) {
        tagline = _tagline;
        return true;
    } else {
        return false;
    }
}

/**
 * setter method for all information at once
 * 
 * @param _username - the new username to be set
 * @param _firstname - the new firstname to be set
 * @param _lastname - the new lastname to be set
 * @param _age - the new age to be set
 * @param _gender - the new gender to be set
 * @param _tagline - the new tagline to be set
 * @return - true if all new values are valid and set successfully; false 
 *           otherwise
 *
 */
bool Person::set_info(string _username, string _firstname, string _lastname,
                      int _age, string _gender, string _tagline)
{
    bool valid_usr = set_username(_username);
    bool valid_first = set_firstname(_firstname);
    bool valid_last = set_lastname(_lastname);
    bool valid_age = set_age(_age);
    bool valid_gender = set_gender(_gender);
    bool valid_tag = set_tagline(_tagline);
    return valid_usr && valid_first && valid_last && valid_age && 
           valid_gender && valid_tag;
}

/**
 * send a message to another Person
 * 
 * @param recipient - the recipient of the message
 * @param msg - the message
 * @return - void
 *
 */
void Person::send_msg(Person &recipient, string msg)
{
    recipient.get_msg(msg);
}

/**
 * receive a message
 * 
 * @param msg - the message to be received
 * @return - void
 *
 */
void Person::get_msg(string msg)
{
    inbox.push(msg);
}

/**
 * read a message from inbox
 * 
 * @return - true if there is a queuing message; false if the inbox is empty
 *
 */
bool Person::read_msg()
{
    if (inbox.size() > 0) {
        cout << inbox.front();
        inbox.pop();
        return true;
    } else {
        cout << "Inbox is empty. Cannot read any message.\n";
        return false;
    }
}