#include "yaffut.h"

#include "Common/List.h"

struct ListElement : public Common::List<ListElement>::Element
{
	ListElement(int i)
		: Common::List<ListElement>::Element(*this)
		, value(i)
	{
	}

	int value;
};

struct ListTest
{
	ListElement one = 1;
	ListElement two = 2;
	ListElement three = 3;
};

TEST(ListTest, should_construct_empty_list)
{
	Common::List<ListElement> list;
	EXPECT_TRUE(list.IsEmpty());
	// Here I would rather say EXPECT_EQ(nullptr, list.GetFirst()) but there
	// is an ambiguity error when using the stream put operator and nullptr_t.
	EXPECT_TRUE(!list.GetFirst());
	EXPECT_TRUE(!list.GetLast());
}

TEST(ListTest, should_add_and_remove_items)
{
	Common::List<ListElement> list;

	list.Add(one);
	list.Add(two);
	list.Add(three);

	EXPECT_TRUE(!list.IsEmpty());

	EXPECT_EQ(&one, list.GetFirst());
	EXPECT_EQ(&three, list.GetLast());

	list.Remove(three);

	EXPECT_EQ(&two, list.GetLast());

	list.Remove(two);

	EXPECT_EQ(&one, list.GetLast());

	list.Remove(one);

	EXPECT_TRUE(list.IsEmpty());
}

TEST(ListTest, should_not_add_element_that_is_already_in_list)
{
	Common::List<ListElement> list;

	list.Add(one);
	list.Add(one);

	EXPECT_EQ(&one, list.GetFirst());
	EXPECT_TRUE(!list.GetNext());
}

TEST(ListTest, should_remove_item_from_list_when_item_is_destructed)
{
	Common::List<ListElement> list;
	{
		ListElement temp(0);
		list.Add(temp);
	}

	EXPECT_TRUE(list.IsEmpty());
	EXPECT_TRUE(!list.GetFirst());
}

TEST(ListTest, should_not_remove_item_that_is_not_in_list)
{
	Common::List<ListElement> list;

	list.Remove(one);

	EXPECT_TRUE(list.IsEmpty());

	list.Add(one);
	list.Remove(two);

	EXPECT_EQ(&one, list.GetFirst());
}

TEST(ListTest, should_iterate_over_list_items)
{
	Common::List<ListElement> list;

	list.Add(one);
	list.Add(two);
	list.Add(three);

	int expected = 1;

	for (ListElement* it = list.GetFirst(); it != nullptr; it = list.GetNext())
	{
		EXPECT_EQ(expected++, it->value);
	}

	for (ListElement* it = list.GetLast(); it != nullptr; it = list.GetPrevious())
	{
		EXPECT_EQ(--expected, it->value);
	}

	for (const auto& i : list)
	{
		EXPECT_EQ(expected++, i.value);
	}
}
