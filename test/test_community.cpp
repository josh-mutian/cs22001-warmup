#include "gtest/gtest.h"
#include "person.h"
#include "community.h"

// this class is used for testing public methods in class Community
class test_community: public ::testing::Test {
protected:
	Community community;
};

// you should complete the following test cases
// you should add more if you see fit

// test get_name
TEST_F(test_community, get_name) {
	EXPECT_STREQ(community.get_name().c_str(), "");
	EXPECT_FALSE(community.set_name("testinggetname"));
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
}

// test get_all_usernames
//   there's no EXPERT functions for comparing non-built-in types, you need to
//   do some parsing by yourself
TEST_F(test_community, get_all_usernames) {
}

// test find_member by first name and age range
TEST_F(test_community, find_member) {
}

// test get_member
TEST_F(test_community, get_member) {
}

// test send_msg
TEST_F(test_community, send_msg) {
}

