#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <gtest/gtest.h>
#include <hustle/algorithm.hpp>

template <typename _Container, typename _Value>
void test_erase(_Container&       container,
                const _Container& expected,
                const _Value&     value) {
	hustle::erase(container, value);
	EXPECT_EQ(container, expected);
}

template <typename _Container, typename _Predicate>
void test_erase_if(_Container&       container,
                   const _Container& expected,
                   _Predicate        pred) {
	hustle::erase_if(container, pred);
	EXPECT_EQ(container, expected);
}

template <typename _Container, typename _Predicate>
void test_erase_if_not(_Container&       container,
                       const _Container& expected,
                       _Predicate        pred) {
	hustle::erase_if_not(container, pred);
	EXPECT_EQ(container, expected);
}

TEST(hustle, erase) {
	{
		std::vector<int> nums     = {1, 3, 7, 4, 5, 2, 9, 0, 5};
		std::vector<int> expected = {1, 3, 7, 4, 2, 9, 0};
		test_erase(nums, expected, 5);
	}
	{
		std::string text     = "Hello, World!";
		std::string expected = "Hell, Wrld!";
		auto        it       = text.begin();
		test_erase(text, expected, 'o');
	}
	{
		std::list<int> nums     = {1, 3, 7, 4, 5, 2, 9, 0, 5};
		std::list<int> expected = {1, 3, 7, 4, 2, 9, 0};
		test_erase(nums, expected, 5);
	}
	{
		std::map<int, std::string> values   = {{0, "a"}, {1, "b"}, {2, "c"}};
		std::map<int, std::string> expected = {{0, "a"}, {2, "c"}};
		test_erase(values, expected, 1);
	}
	{
		std::set<int> values   = {1, 2, 3, 4};
		std::set<int> expected = {1, 2, 4};
		test_erase(values, expected, 3);
	}
	{
		std::multimap<int, std::string> values = {{0, "a"}, {1, "b"}, {2, "c"}};
		std::multimap<int, std::string> expected = {{0, "a"}, {2, "c"}};
		test_erase(values, expected, 1);
	}
	{
		std::multiset<int> values   = {1, 2, 3, 4};
		std::multiset<int> expected = {1, 2, 4};
		test_erase(values, expected, 3);
	}
	{
		std::unordered_map<int, std::string> values = {
		    {0, "a"}, {1, "b"}, {2, "c"}};
		std::unordered_map<int, std::string> expected = {{0, "a"}, {2, "c"}};
		test_erase(values, expected, 1);
	}
	{
		std::unordered_set<int> values   = {1, 2, 3, 4};
		std::unordered_set<int> expected = {1, 2, 4};
		test_erase(values, expected, 3);
	}
	{
		std::unordered_multimap<int, std::string> values = {
		    {0, "a"}, {1, "b"}, {2, "c"}};
		std::unordered_multimap<int, std::string> expected = {{0, "a"},
		                                                      {2, "c"}};
		test_erase(values, expected, 1);
	}
	{
		std::unordered_multiset<int> values   = {1, 2, 3, 4};
		std::unordered_multiset<int> expected = {1, 2, 4};
		test_erase(values, expected, 3);
	}
	{
		std::deque<int> values   = {1, 2, 3, 4};
		std::deque<int> expected = {1, 2, 4};
		test_erase(values, expected, 3);
	}
}

TEST(hustle, erase_if) {
	{
		std::vector<int> nums     = {1, 3, 7, 4, 5, 2, 9, 0, 5};
		std::vector<int> expected = {1, 3, 7, 4, 2, 9, 0};
		test_erase_if(nums, expected, [](int n) { return n == 5; });
	}
	{
		std::string text     = "Hello, World!";
		std::string expected = "H, W!";
		test_erase_if(text, expected, ::islower);
	}
	{
		std::map<int, std::string> values   = {{0, "a"}, {1, "b"}, {2, "c"}};
		std::map<int, std::string> expected = {{0, "a"}, {2, "c"}};
		test_erase_if(values, expected, [](auto& it) { return it.first == 1; });
	}
	{
		std::set<int> values   = {1, 2, 3, 4};
		std::set<int> expected = {3, 4};
		test_erase_if(values, expected, [](auto i) { return i < 3; });
	}
	{
		std::unordered_map<int, std::string> values = {
		    {0, "a"}, {1, "b"}, {2, "c"}};
		std::unordered_map<int, std::string> expected = {{0, "a"}, {2, "c"}};
		test_erase_if(values, expected, [](auto& it) { return it.first == 1; });
	}
	{
		std::unordered_set<int> values   = {1, 2, 3, 4};
		std::unordered_set<int> expected = {3, 4};
		test_erase_if(values, expected, [](auto i) { return i < 3; });
	}
	{
		std::multimap<int, std::string> values = {{0, "a"}, {1, "b"}, {2, "c"}};
		std::multimap<int, std::string> expected = {{0, "a"}, {2, "c"}};
		test_erase_if(values, expected, [](auto& it) { return it.first == 1; });
	}
	{
		std::multiset<int> values   = {1, 2, 3, 4};
		std::multiset<int> expected = {3, 4};
		test_erase_if(values, expected, [](auto i) { return i < 3; });
	}
	{
		std::unordered_multimap<int, std::string> values = {
		    {0, "a"}, {1, "b"}, {2, "c"}};
		std::unordered_multimap<int, std::string> expected = {{0, "a"},
		                                                      {2, "c"}};
		test_erase_if(values, expected, [](auto& it) { return it.first == 1; });
	}
	{
		std::unordered_multiset<int> values   = {1, 2, 3, 4};
		std::unordered_multiset<int> expected = {3, 4};
		test_erase_if(values, expected, [](auto i) { return i < 3; });
	}
	{
		std::deque<int> values   = {1, 2, 3, 4};
		std::deque<int> expected = {1, 2, 4};
		test_erase_if(values, expected, [](auto i) { return i == 3; });
	}
}

TEST(hustle, erase_if_not) {
	{
		std::vector<int> nums     = {1, 3, 7, 4, 5, 2, 9, 0, 5};
		std::vector<int> expected = {5, 5};
		test_erase_if_not(nums, expected, [](int n) { return n == 5; });
	}
	{
		std::string text     = "Hello, World!";
		std::string expected = "elloorld";
		test_erase_if_not(text, expected, ::islower);
	}
}
