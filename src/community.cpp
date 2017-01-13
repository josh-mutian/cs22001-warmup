#include "community.h"

bool isNullPerson(Person p)
{
    //since only null person can have an empty username
    return p.get_username() == "";
}

Community::Community()
    : name(""), people(map<string,Person>())
{
}

Community::Community(string _name, map<string,Person> _people)
    : name(_name), people(_people)
{
}

string Community::get_name()
{
    return name;
}

bool Community::set_name(string _name)
{
    if (str_isalnum(_name) &&
        _name.length() <= 128 &&
        _name.length() > 0 &&
        isalpha(_name[0])) {
        name = _name;
        return true;
    } else {
        return false;
    }
}

bool Community::add_person(Person _person)
{
    const string username = _person.get_username();
    if (isNullPerson(get_member(username))) {
        people[username] = _person;
        return true;
    } else {
        return false;
    }
}

// return the person object for a given username
Person Community::get_member(string username)
{
    if (people.find(username) != people.end()) {
        return people[username];
    } else {
        return Person();
    }
}

list<string> Community::get_all_usernames()
{
    list<string> usernames;
    for (map<string,Person>::iterator it= people.begin(); it != people.end(); ++it) {
        usernames.push_back(it->first);
    }
    return usernames;
}

void Community::print_all_usernames()
{
    list<string> usernames = get_all_usernames();
    for (list<string>::iterator it= usernames.begin(); it != usernames.end(); ++it) {
        cout << *it << "; ";
    }
}

list<Person> Community::find_member(string firstname)
{
    list<Person> ret;
    for (map<string,Person>::iterator it= people.begin(); it != people.end(); ++it) {
        Person p = it->second;
        if (p.get_firstname() == firstname) {
            ret.push_back(p);
        }
    }
    return ret;
}

list<Person> Community::find_member(int age_lb, int age_ub)
{
    list<Person> ret;
    for (map<string,Person>::iterator it= people.begin(); it != people.end(); ++it) {
        Person p = it->second;
        int age = p.get_age();
        if (age <= age_ub && age >= age_lb) {
            ret.push_back(p);
        }
    }
    return ret;
}

bool Community::send_msg(list<string> usernames, string msg)
{
    bool ret = true;
    for (auto const& username : usernames) {
        Person p = get_member(username);
        if (!isNullPerson(p)) {
            p.get_msg(msg);
        } else {
            ret = false;
        }
    }
    return ret;
}

