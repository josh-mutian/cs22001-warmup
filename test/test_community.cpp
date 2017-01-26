#include "gtest/gtest.h"
#include "person.h"
#include "community.h"

// this class is used for testing public methods in class Community
class test_community: public ::testing::Test {
protected:
	Community community;
	Person p1;
	Person p2;
	Person p3;
};

// you should complete the following test cases
// you should add more if you see fit

// test get_name
TEST_F(test_community, get_name) {
	EXPECT_STREQ(community.get_name().c_str(), "");
	EXPECT_TRUE(community.set_name("testinggetname"));
	EXPECT_STREQ(community.get_name().c_str(), "testinggetname");
}

// test set_name
TEST_F(test_community, set_name) {
	//community name too long (129 characters)
	EXPECT_FALSE(community.set_name("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl"));
	//community name not alphanumerical
	EXPECT_FALSE(community.set_name("aaaa()"));
	//community name first digit is digit
	EXPECT_FALSE(community.set_name("2aabb"));
	//community name is empty
	EXPECT_FALSE(community.set_name(""));
	//exactly 128 characters will be accepted
	EXPECT_TRUE(community.set_name("a2222222ijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkla2222222ijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl"));
	EXPECT_STREQ(community.get_name().c_str(), "a2222222ijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkla2222222ijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl");
	EXPECT_TRUE(community.set_name("regular"));
	EXPECT_STREQ(community.get_name().c_str(), "regular");
}

// test add_person
TEST_F(test_community, add_person) {
	p1.set_username("test1");
	EXPECT_FALSE(community.get_member("test1").is_same_person(p1));
	EXPECT_TRUE(community.add_person(&p1));
	EXPECT_TRUE(community.get_member("test1").is_same_person(p1));
	//adding person who is already a member should return false
	EXPECT_FALSE(community.add_person(&p1));
}

// test get_all_usernames
//   there's no EXPERT functions for comparing non-built-in types, you need to
//   do some parsing by yourself
TEST_F(test_community, get_all_usernames) {
	p1.set_username("test1");
	p2.set_username("test2");
	p3.set_username("test3");
	list<string> ret_usr_names = community.get_all_usernames();
	EXPECT_TRUE(ret_usr_names.size() == 0);

	community.add_person(&p1);
	ret_usr_names = community.get_all_usernames();
	EXPECT_TRUE(ret_usr_names.size() == 1 && 
			    ret_usr_names.front() == "test1");

	community.add_person(&p2);
	community.add_person(&p3);
	ret_usr_names = community.get_all_usernames();
	// Find three names respectively.
	bool p1_found = false, p2_found = false, p3_found = false;
	for (list<string>::iterator it = ret_usr_names.begin();
		 it != ret_usr_names.end(); ++it) {
		if (*it == "test1") {
			p1_found = true;
		} else if (*it == "test2") {
			p2_found = true;
		} else if (*it == "test3") {
			p3_found = true;
		}
	}
	EXPECT_TRUE(ret_usr_names.size() == 3 && p1_found && p2_found && p3_found);
}

// test find_member by first name and age range
TEST_F(test_community, find_member) {
	// Find by first name.
	p1.set_username("test_1");
	p1.set_firstname("Frank");
	p1.set_age(12);
	EXPECT_TRUE(community.find_member("Frank").size() == 0);
	community.add_person(&p1);
	list<Person> members_found = community.find_member("Frank");
	EXPECT_TRUE(members_found.size() == 1 && 
			    members_found.front().is_same_person(p1));

	// Find by age range.
	members_found = community.find_member(0, 11);
	EXPECT_TRUE(members_found.size() == 0);
	members_found = community.find_member(0, 15);
	EXPECT_TRUE(members_found.size() == 1 && 
			    members_found.front().is_same_person(p1));
	members_found = community.find_member(0, 12);
	EXPECT_TRUE(members_found.size() == 1 && 
			    members_found.front().is_same_person(p1));
	members_found = community.find_member(12, 12);
	EXPECT_TRUE(members_found.size() == 1 && 
			    members_found.front().is_same_person(p1));
	members_found = community.find_member(12, 20);
	EXPECT_TRUE(members_found.size() == 1 && 
			    members_found.front().is_same_person(p1));
	members_found = community.find_member(13, 200);
	EXPECT_TRUE(members_found.size() == 0);
}

// test get_member
TEST_F(test_community, get_member) {
	p1.set_username("test1");
	EXPECT_FALSE(community.get_member("test1").is_same_person(p1));
	EXPECT_TRUE(community.add_person(&p1));
	EXPECT_TRUE(community.get_member("test1").is_same_person(p1));
}

// test send_msg
TEST_F(test_community, send_msg) {
	p1.set_username("test1");
	p2.set_username("test2");
	p3.set_username("test3");
	community.add_person(&p1);
	community.add_person(&p2);
	community.add_person(&p3);
	list<string> l;
	l.push_back("test1");
	l.push_back("test2");
	EXPECT_TRUE(community.send_msg(l, "test_msg\n"));
	/* eyeball test if messages are received correctly */
	p1.read_msg();
	p1.read_msg();
	p2.read_msg();
	p2.read_msg();
	p3.read_msg();

	/* check that if one of the target usernames is not found:
	 * 1. all targets that ARE found should receive the message
	 * 2. send_msg() should return false */
	l.push_back("test4");
	EXPECT_FALSE(community.send_msg(l, "test_msg\n"));
	p1.read_msg();
	p1.read_msg();
	p2.read_msg();
	p2.read_msg();
	p3.read_msg();
}

