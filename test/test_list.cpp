#include <gtest.h>
#include "list.h"

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

