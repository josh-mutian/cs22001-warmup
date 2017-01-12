#include "person.h"

bool str_isalpha(const string str)
{
    int size = str.size();
    for(int i = 0; i < size; i++)
        if((isalpha(str[i]) == 0) || (str[i] == ' '))
            return false;
    return true;
}

bool str_isalnum(const string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && (std::isdigit(*it) || std::isalpha(*it))) ++it;
    return !s.empty() && it == s.end();
}

Person::Person()
    : username(""), firstname(""), lastname(""), gender(""), age(0), tagline("")
{
}

Person::Person(string _username, string _firstname, string _lastname,
               string _gender, int _age, string _tagline)
    : username(_username), firstname(_firstname), lastname(_lastname),
      gender(_gender), age(_age), tagline(_tagline)
{
}

string Person::get_username()
{
    return username;
}
string Person::get_firstname()
{
    return firstname;
}
string Person::get_lastname()
{
    return lastname;
}
string Person::get_gender()
{
    return gender;
}
int Person::get_age()
{
    return age;
}
string Person::get_tagline()
{
    return tagline;
}
string Person::get_info()
{
    string ret = "";
    return ret;
}

bool Person::set_username(string _username)
{
    if (str_isalnum(_username) &&
        _username.length() <= 64 &&
        _username.length() > 0 &&
        isalpha(_username[0])) {
        username = _username;
        return true;
    } else {
        return false;
    }
}

bool Person::set_firstname(string _firstname)
{
    if (str_isalpha(_firstname) && _firstname.length() <= 64) {
        firstname = _firstname;
        return true;
    } else {
        return false;
    }
}


bool Person::set_lastname(string _lastname)
{
    if (str_isalpha(_lastname) && _lastname.length() <= 64) {
        lastname = _lastname;
        return true;
    } else {
        return false;
    }
}

bool Person::set_gender(string _gender)
{
    if (_gender == "m" || _gender == "f") {
        gender = _gender;
        return true;
    } else {
        return false;
    }
}

bool Person::set_age(int _age)
{
    if (_age >= 0 && _age < 128) {
        age = _age;
        return true;
    } else {
        return false;
    }
}
bool Person::set_tagline(string _tagline)
{
    if (_tagline.length() <= 512) {
        tagline = _tagline;
        return true;
    } else {
        return false;
    }
}


bool Person::set_info(string _username, string _firstname, string _lastname,
                      int _age, string _tagline)
{
    if (set_username(_username) &&
            set_firstname(_firstname) &&
            set_lastname(_lastname) &&
            set_age(_age) &&
            set_tagline(_tagline)) {
        return true;
    } else {
        return false;
    }
}

void Person::send_msg(Person &recipient, string msg)
{
    recipient.get_msg(msg);
}

void Person::get_msg(string msg)
{
    inbox.push(msg);
}

bool Person::read_msg()
{
    if (inbox.size() > 0) {
        cout << inbox.front();
        inbox.pop();
        return true;
    } else {
        return false;
    }
}
