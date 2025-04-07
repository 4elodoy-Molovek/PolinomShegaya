//#include "gtest.h"
//#include "TreeTable.h"
//
//
//// Test case for adding an element
//TEST(TreeTableTest, AddElement) 
//{
//    TreeTable<int, std::string> table;
//
//    table.addElement(10, "Ten");
//    table.addElement(20, "Twenty");
//    table.addElement(5, "Five");
//
//    std::vector<std::pair<const int&, const std::string&>> elements;
//    table.getAllElements(elements);
//
//    ASSERT_EQ(elements.size(), 3);
//    ASSERT_EQ(elements[0].first, 5);
//    ASSERT_EQ(elements[1].first, 10);
//    ASSERT_EQ(elements[2].first, 20);
//}
//
//// Test case for adding an element with a duplicate key
//TEST(TreeTableTest, AddDuplicateElement) 
//{
//    TreeTable<int, std::string> table;
//
//    table.addElement(10, "Ten");
//
//    // Try to add a duplicate key
//    EXPECT_THROW(table.addElement(10, "Duplicate"), std::exception);
//}
//
//// Test case for searching an element
//TEST(TreeTableTest, FindElement) 
//{
//
//    TreeTable<int, std::string> table;
//
//    table.addElement(10, "Ten");
//    table.addElement(20, "Twenty");
//
//    EXPECT_EQ(*table.findElement(10), "Ten");
//    EXPECT_EQ(*table.findElement(20), "Twenty");
//    EXPECT_EQ(table.findElement(30), nullptr);  // Non-existent element
//}
//
//// Test case for deleting an element
//TEST(TreeTableTest, DeleteElement) 
//{
//    TreeTable<int, std::string> table;
//
//    table.addElement(10, "Ten");
//    table.addElement(20, "Twenty");
//    table.addElement(5, "Five");
//
//    table.deleteElement(10);
//
//    std::vector<std::pair<const int&, const std::string&>> elements;
//    table.getAllElements(elements);
//
//    ASSERT_EQ(elements.size(), 2);
//    ASSERT_EQ(elements[0].first, 5);
//    ASSERT_EQ(elements[1].first, 20);
//}
//
//// Test case for deleting an element and checking tree balance
//TEST(TreeTableTest, DeleteAndBalance) 
//{
//    TreeTable<int, std::string> table;
//
//    table.addElement(10, "Ten");
//    table.addElement(5, "Five");
//    table.addElement(20, "Twenty");
//    table.addElement(15, "Fifteen");
//
//    table.deleteElement(10);  // Deleting root element
//
//    std::vector<std::pair<const int&, const std::string&>> elements;
//    table.getAllElements(elements);
//
//    ASSERT_EQ(elements.size(), 3);
//    ASSERT_EQ(elements[0].first, 5);
//    ASSERT_EQ(elements[1].first, 15);
//    ASSERT_EQ(elements[2].first, 20);
//}
//
//// Test case for the tree being empty
//TEST(TreeTableTest, EmptyTree) 
//{
//    TreeTable<int, std::string> table;
//
//    std::vector<std::pair<const int&, const std::string&>> elements;
//    table.getAllElements(elements);
//
//    ASSERT_EQ(elements.size(), 0);
//}
//
//// Test case for a single element in the tree
//TEST(TreeTableTest, SingleElement) 
//{
//    TreeTable<int, std::string> table;
//
//    table.addElement(10, "Ten");
//
//    std::vector<std::pair<const int&, const std::string&>> elements;
//    table.getAllElements(elements);
//
//    ASSERT_EQ(elements.size(), 1);
//    ASSERT_EQ(elements[0].first, 10);
//    ASSERT_EQ(elements[0].second, "Ten");
//}
//
//// Test case for the tree's internal structure after insertion (rotation and balancing)
//TEST(TreeTableTest, InsertionBalanceTest) 
//{
//    TreeTable<int, std::string> table;
//
//    table.addElement(30, "Thirty");
//    table.addElement(20, "Twenty");
//    table.addElement(40, "Forty");
//    table.addElement(35, "Thirty-Five");
//
//    std::vector<std::pair<const int&, const std::string&>> elements;
//    table.getAllElements(elements);
//
//    ASSERT_EQ(elements.size(), 4);
//    ASSERT_EQ(elements[0].first, 20);
//    ASSERT_EQ(elements[1].first, 30);
//    ASSERT_EQ(elements[2].first, 35);
//    ASSERT_EQ(elements[3].first, 40);
//}
//
//// Test case for removing the last element (empty tree case)
//TEST(TreeTableTest, RemoveLastElement) 
//{
//    TreeTable<int, std::string> table;
//
//    table.addElement(10, "Ten");
//
//    table.deleteElement(10);
//
//    std::vector<std::pair<const int&, const std::string&>> elements;
//    table.getAllElements(elements);
//
//    ASSERT_EQ(elements.size(), 0);
//}
//
//// Test case for deleting an element from an empty tree
//TEST(TreeTableTest, DeleteFromEmptyTree) 
//{
//    TreeTable<int, std::string> table;
//
//    EXPECT_THROW(table.deleteElement(10), std::exception);
//}
//
//// Test case for deleting non-existent element
//TEST(TreeTableTest, DeleteNonExistentElement) 
//{
//    TreeTable<int, std::string> table;
//
//    table.addElement(10, "Ten");
//    table.addElement(20, "Twenty");
//
//    EXPECT_THROW(table.deleteElement(30), std::exception);  // Element does not exist
//}