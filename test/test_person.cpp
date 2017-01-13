#include "gtest/gtest.h"
#include "person.h"

// this class is used for testing public methods in class Person
class test_person: public ::testing::Test {
protected:
	Person person;
	Person recipient;
};

// test get_username and set_username
TEST_F(test_person, test_username) {
	//user name too long
	EXPECT_FALSE(person.set_username("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklm"));
	//user name not alphanumerical
	EXPECT_FALSE(person.set_username("aaaa()"));
	//user name first digit is digit
	EXPECT_FALSE(person.set_username("2aabb"));
	//user name is empty
	EXPECT_FALSE(person.set_username(""));
	//exactly 64 characters will be accepted
	EXPECT_TRUE(person.set_username("a2222222ijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl"));
	EXPECT_STREQ(person.get_username().c_str(), "a2222222ijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl");
}

// test get_firstname and set_firstname
TEST_F(test_person, test_firstname) {
	//first name too long
	EXPECT_FALSE(person.set_firstname("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	//first name not alphabetical
	EXPECT_FALSE(person.set_firstname("aaaa2"));
	//empty will be accepted
	EXPECT_TRUE(person.set_firstname(""));
	EXPECT_STREQ(person.get_firstname().c_str(), "");
	//exactly 64 characters will be accepted
	EXPECT_TRUE(person.set_firstname("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	EXPECT_STREQ(person.get_firstname().c_str(), "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}

// test get_lastname and set_lastname
TEST_F(test_person, test_lastname) {
	//last name too long
	EXPECT_FALSE(person.set_lastname("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	//last name not alphabetical
	EXPECT_FALSE(person.set_lastname("aaaa2"));
	//empty will be accepted
	EXPECT_TRUE(person.set_lastname(""));
	EXPECT_STREQ(person.get_lastname().c_str(), "");
	//exactly 64 characters will be accepted
	EXPECT_TRUE(person.set_lastname("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	EXPECT_STREQ(person.get_lastname().c_str(), "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}

/**you may need to write more test functions.
 *  What we provide here is just for your reference
 */

// test get_age and set_age
//   test_person is the name of class your inherit from the base Test class
//   test_age is the name of this test case, which will show up in the test
//     results
//   make sure you cover every subroutine and branches
//   here we test edge cases of invalid ages
//   also, we test the get_age() method
//   avoid using ASSERT_FALSE here; if there is something wrong in ASSERT,
//   it will abort the whole testing which will hinder the grading process
TEST_F(test_person, test_age) {
	EXPECT_FALSE(person.set_age(-1));
	EXPECT_FALSE(person.set_age(300));
	EXPECT_TRUE(person.set_age(0));
	EXPECT_EQ(person.get_age(), 0);
	EXPECT_TRUE(person.set_age(127));
	EXPECT_EQ(person.get_age(), 127);
	EXPECT_FALSE(person.set_age(128));
}

// test get_tagline and set_tagline
TEST_F(test_person, test_tagline) {
	//tagline is too long (at 513 characters)
	EXPECT_FALSE(person.set_tagline("513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513characters"));
	EXPECT_TRUE(person.set_tagline("1qz*3"));
	EXPECT_STREQ(person.get_tagline().c_str(), "1qz*3");
	//empty will be accepted
	EXPECT_TRUE(person.set_tagline(""));
	EXPECT_STREQ(person.get_tagline().c_str(), "");
}

// test get_info and set_info
TEST_F(test_person, test_info) {
	EXPECT_TRUE(person.set_info("validusername", "validfirstname", "validlastname", 30, "f", "validtagline"));
	//test get_info
	EXPECT_STREQ(person.get_info().c_str(), "username: validusername, firstname: validfirstname, lastname: validlastname, age: 30, gender: f, tagline: validtagline");
	//verify that valid entries of set_info could go through even if other entries are invalid
	EXPECT_FALSE(person.set_info("username", "*illegalfirstname", "lastname", 20, "m", "tagline"));
	EXPECT_STREQ(person.get_username().c_str(), "username");
	EXPECT_STREQ(person.get_lastname().c_str(), "lastname");
	EXPECT_STREQ(person.get_tagline().c_str(), "tagline");
	EXPECT_EQ(person.get_age(), 20);
	//verify that all types of invalid entries can be recognized
	EXPECT_FALSE(person.set_info("*illegalusername", "firstname", "lastname", 20, "m", "tagline"));
	EXPECT_FALSE(person.set_info("username", "firstname", "*illegallastname", 20, "m", "tagline"));
	EXPECT_FALSE(person.set_info("username", "firstname", "lastname", 20, "m", "513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513charactersintotal513characters"));
	EXPECT_FALSE(person.set_info("username", "firstname", "lastname", 128, "m", "tagline"));
	EXPECT_FALSE(person.set_info("username", "firstname", "lastname", 25, "notagender", "tagline"));
	//test get_info
	EXPECT_STREQ(person.get_info().c_str(), "username: username, firstname: firstname, lastname: lastname, age: 25, gender: m, tagline: tagline");
}

// test send_msg and read_msg
//   to make your code shorter, we suggest combining these tests together; you
//   can also separate them into several test cases
TEST_F(test_person, test_msg) {
	//eye ball testing
	person.send_msg(recipient, "test_message1\n");
	recipient.read_msg();
	recipient.read_msg();
	person.send_msg(recipient, "test_message2\n");
	person.send_msg(recipient, "test_message3\n");
	recipient.read_msg();
	recipient.read_msg();
	recipient.read_msg();
}

