#include <gtest.h>
#include "list.h"

TEST(list, can_create_list) {
	ASSERT_NO_THROW(List<double> abc);
	ASSERT_NO_THROW(List<double> abcd(5));
	List<double> abcd(5);
	ASSERT_NO_THROW(List<double> abcde(abcd));
	Node<double>* ptr = nullptr;
	ASSERT_NO_THROW(List<double> abcdef(ptr));
	ASSERT_NO_THROW(List<double> abcdefg({ {1.23}, {3.45}, {5.67} }));
}

TEST(list, size) {
	List<double> a(10);
	EXPECT_EQ(10, a.size());
	List<double> b;
	EXPECT_EQ(0, b.size());
	List<double> abcdefg({ {1.23}, {3.45}, {5.67} });
	EXPECT_EQ(3, abcdefg.size());
	Node<double>* ptr = nullptr;	 
	List<double> abcdef(ptr);
	EXPECT_EQ(0, abcdef.size());
}

TEST(list, push_front_and_get_node) {
	List<double> a;
	for (int i = 0; i < 10; i++) {
		a.push_front(9 - i);
	}
	EXPECT_EQ(9, a.get_node(9)->elem);
	EXPECT_EQ(0, a.get_node(0)->elem);
	EXPECT_EQ(5, a.get_node(5)->elem);
}

TEST(list, operator_square_brackets) {
	List<double> abcdefg({ {1.23}, {3.45}, {5.67} });
	EXPECT_EQ(1.23, abcdefg[0]);
	EXPECT_EQ(3.45, abcdefg[1]);
	EXPECT_EQ(5.67, abcdefg[2]);
}

TEST(list, insert_after) {
	List<double> abcdefg({ {1.23}, {3.45}, {5.67} });
	abcdefg.insert_after(abcdefg.get_node(2), 7.89);
	EXPECT_EQ(7.89, abcdefg[3]);
	List<double> a;
	ASSERT_ANY_THROW(a.insert_after(a.get_first(), 1));
}

TEST(list, erase_after) {
	List<double> a;
	for (int i = 0; i < 10; i++) {
		a.push_front(9 - i);
	}				
	a.erase_after(a.get_node(4));
	EXPECT_EQ(6, a[5]);
}

TEST(list, clear) {
	List<double> a;
	for (int i = 0; i < 10; i++) {
		a.push_front(9 - i);
	}
	a.clear();
	EXPECT_EQ(nullptr, a.get_first());
}

TEST(list, merge) {
	List<double> a;
	for (int i = 0; i < 10; i++) {
		a.push_front(9 - i);
	}
	List<double> b;
	for (int i = 0; i < 10; i++) {
		b.push_front(19 - i);
	}
	a.merge(b);
	EXPECT_EQ(9, a[9]);
	EXPECT_EQ(10, a[10]);
	EXPECT_EQ(19, a[19]);
	EXPECT_EQ(nullptr, b.get_first());
	List<double> c;
	List<double> d;
	ASSERT_NO_THROW(c.merge(d));
}

TEST(list, sort_merge) {
	List<double> l = { {1}, {3}, {9}, {27}, {1245}, {23454}, {233333}, {268184}, {300000} ,{1}, {4}, {10}, {28}, {1246}, {23455}, {233334}, {268185}, {300001} };
	l.merge_sort();
	EXPECT_EQ(1, l[1]);
	EXPECT_EQ(233333, l[12]);
	List<double> i = { {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9} ,{10}, {11}, {12}, {13}, {14}, {15}, {16}, {17} };
	i.merge_sort();
	EXPECT_EQ(1, i[0]);
	EXPECT_EQ(17, i[16]);
	i.reverse();
	i.merge_sort();
	EXPECT_EQ(1, i[0]);
	EXPECT_EQ(17, i[16]);
}

TEST(list, insert_sorted_element) {
	List<double> b = { {1}, {2}, {3}, {5} };
	b.sorted_insert(4);
	EXPECT_EQ(4, b[3]);
}

TEST(list, erase_last_duplicate) {
	List<double> d = { {5}, {1}, {2}, {3}, {5}, {5}, {3}, {2}, {1} };
	d.erase_last_duplicate(5);
	EXPECT_EQ(3, d[5]);
}

TEST(list, find_k_element_at_end) {
	List<int>e;
	for (int i = 1; i < 21; i++) {
		e.push_front(i);
	}
	EXPECT_EQ(3, e.at_end(3));
}

