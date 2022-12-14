#include "../src/AVLTree.hpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("BST Insert", "[flag]")
{
	AVLTree tree;   // Create a Tree object 
	tree.Insert("Angi", "00000000");
	tree.Insert("Nic", "11111111");
	tree.Insert("Nicco", "22222222");
	tree.Insert("Nigel", "33333333");
	tree.Insert("Naren", "44444444");
	tree.Insert("Poopy", "55555555");
	tree.Insert("Yay", "66666666");
	std::vector<string> actualOutput = tree.PrintInorder();
	std::vector<string> expectedOutput = {"Angi", "Nic", "Nicco", "Nigel", "Naren", "Poopy", "Yay"};
	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(actualOutput == expectedOutput);

	/*std::vector<string> actualOutputPre = tree.PrintPreorder();
	std::vector<string> expectedOutputPre = {"Nic", "Angi", "Nigel", "Naren", "Nicco"};
	REQUIRE(expectedOutputPre.size() == actualOutputPre.size());
	REQUIRE(actualOutputPre == expectedOutputPre);*/
}