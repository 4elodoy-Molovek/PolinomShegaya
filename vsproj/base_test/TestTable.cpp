#include <..\gtest\gtest.h>
#include <memory>
#include "Table.h"
#include "HashTableOne.h"
#include "HashTableTwo.h"
#include "LinearArrayTable.h"
#include "LinearListTable.h"
#include "SortedArrayTable.h"
#include "TreeTable.h"

class TableTest : public ::testing::TestWithParam<std::shared_ptr<Table<std::string, int>>>
{
protected:
    std::shared_ptr<Table<std::string, int>> table;

    void SetUp() override { table = GetParam(); }
};

TEST_P(TableTest, table_Can_Add_Element)
{
    EXPECT_NO_THROW(table->addElement("one", 1));
}

TEST_P(TableTest, table_Can_Not_Add_Element_With_Existing_Key)
{
    table->addElement("one", 1);
    EXPECT_ANY_THROW(table->addElement("one", 2));
}

TEST_P(TableTest, table_Can_Find_Added_Element)
{
    table->addElement("one", 1);
    EXPECT_EQ(1, table->findElement("one"));
}

TEST_P(TableTest, table_Can_Not_Find_Non_Existant_Element)
{
    EXPECT_ANY_THROW(table->findElement("two"));
}

TEST_P(TableTest, table_Can_Delete_Element)
{
    table->addElement("one", 1);
    table->deleteElement("one");
    EXPECT_ANY_THROW(table->findElement("one"));
}

TEST_P(TableTest, table_Can_Not_Delete_Non_Existant_Element)
{
    EXPECT_ANY_THROW(table->findElement("two"));
}

INSTANTIATE_TEST_CASE_P
(
    TableImplementations,
    TableTest,
    ::testing::Values
    (
        std::make_shared<HashTableOne<std::string, int>>(),
        std::make_shared<HashTableTwo<std::string, int>>(),
        std::make_shared<LinearArrayTable<std::string, int>>(),
        std::make_shared<LinearListTable<std::string, int>>(),
        std::make_shared<SortedArrayTable<std::string, int>>(),
        std::make_shared<TreeTable<std::string, int>>()
    )
);
