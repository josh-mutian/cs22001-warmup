#include "community.h"

/**
 * null Community constructor
 * 
 * Constructs a Community instance with empty name and empty people collection
 *
 */
Community::Community()
    : name(""), people(map<string,Person*>())
{
}

/**
 * Person constructor
 * 
 * @param _name - initial name to be set for the constructed Community
 * @param _people - initial people collection to be set for the constructed Community
 *
 */
Community::Community(string _name, map<string,Person*> _people)
    : name(_name), people(_people)
{
}

/**
 * getter method for name property
 * 
 * @return - retreived name value
 *
 */
string Community::get_name()
{
    return name;
}

/**
 * setter method for name property
 * 
 * @param _name - the new name to be set
 * @return - true if the new name is valid and set successfully; false otherwise
 *
 */
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

/**
 * add a Person to this Community
 * 
 * @param _person - the Person to be added
 * @return - true if _person is not yet a member of this Community and adding is
             successful; false otherwise
 *
 */
bool Community::add_person(Person *_person)
{
    const string username = (*_person).get_username();
    if (get_member(username).is_null_person()) {
        people[username] = _person;
        return true;
    } else {
        return false;
    }
}

/**
 * find a member by username
 * 
 * @param username - username of the target member
 * @return - target member; return null Person if target username is not found
 *
 */
Person Community::get_member(string username)
{
    if (people.find(username) != people.end()) {
        return *(people[username]);
    } else {
        return Person();
    }
}

/**
 * find a member pointer by username
 * 
 * @param username - username of the target member
 * @return - target member pointer; return null if target username is not found
 *
 */
Person* Community::get_member_pointer(string username)
{
    if (people.find(username) != people.end()) {
        return people[username];
    } else {
        return NULL;
    }
}


/**
 * return a list of the usernames of all members
 * 
 * @return - the resulting list of usernames
 *
 */
list<string> Community::get_all_usernames()
{
    list<string> usernames;
    for (map<string,Person*>::iterator it = people.begin(); 
         it != people.end(); ++it) {
        usernames.push_back(it->first);
    }
    return usernames;
}

/**
 * print out the usernames of all members
 * 
 * @return - void
 *
 */
void Community::print_all_usernames()
{
    list<string> usernames = get_all_usernames();
    for (list<string>::iterator it= usernames.begin(); 
         it != usernames.end(); ++it) {
        cout << *it << "; ";
    }
}

/**
 * find members by first name
 * 
 * @param firstname - target first name
 * @return - a list of all Person's having the target first name
 *
 */
list<Person> Community::find_member(string firstname)
{
    list<Person> ret;
    for (map<string,Person*>::iterator it = people.begin(); 
         it != people.end(); ++it) {
        Person p = *(it->second);
        if (p.get_firstname() == firstname) {
            ret.push_back(p);
        }
    }
    return ret;
}

/**
 * find members by age range
 * 
 * @param age_lb - age lower bound
 * @param age_ub - age upper bound
 * @return - a list of all Person's within the target age range
 *
 */
list<Person> Community::find_member(int age_lb, int age_ub)
{
    list<Person> ret;
    for (map<string,Person*>::iterator it = people.begin(); 
         it != people.end(); ++it) {
        Person p = *(it->second);
        int age = p.get_age();
        if (age <= age_ub && age >= age_lb) {
            ret.push_back(p);
        }
    }
    return ret;
}

/**
 * send message to a set of members
 * 
 * @param usernames - a list of the usernames of the target members
 * @param msg - the message
 * @return - false if any of the target members is not found; true otherwise
 *
 */
bool Community::send_msg(list<string> usernames, string msg)
{
    bool ret = true;
    for (auto const& username : usernames) {
        Person *p = get_member_pointer(username);
        if (p) {
            (*p).get_msg(msg);
        } else {
            ret = false;
        }
    }
    return ret;
}