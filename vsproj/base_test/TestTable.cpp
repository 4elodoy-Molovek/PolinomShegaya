#include <..\gtest\gtest.h>
#include <memory>
#include "Table.h"
#include "HashTableOne.h"
#include "HashTableTwo.h"
#include "LinearArrayTable.h"
#include "LinearListTable.h"
#include "SortedArrayTable.h"
#include "TreeTable.h"

class TableTest : public ::testing::TestWithParam<std::shared_ptr<Table>>
{
protected:
    std::shared_ptr<Table> table;

    void SetUp() override { table = GetParam(); }
};

TEST_P(TableTest, table_Can_Add_Element)
{
    Polynomial pol;

    EXPECT_NO_THROW(table->addElement("pol", pol));
}

TEST_P(TableTest, table_Can_Find_Added_Element)
{
    Polynomial pol;

    table->addElement("pol", pol);
    EXPECT_EQ(pol, table->findElement("pol"));
}

TEST_P(TableTest, table_Can_Delete_Element)
{
    Polynomial pol;

    table->addElement("pol", pol);
    EXPECT_EQ(pol, table->findElement("pol"));

    table->deleteElement("pol");
    EXPECT_ANY_THROW(table->findElement("pol"));
}

INSTANTIATE_TEST_CASE_P
(
    TableImplementations,
    TableTest,
    ::testing::Values
    (
        std::make_shared<HashTableOne>(),
        std::make_shared<HashTableTwo>(),
        std::make_shared<LinearArrayTable>(),
        std::make_shared<LinearListTable>(),
        std::make_shared<SortedArrayTable>(),
        std::make_shared<TreeTable>()
    )
);
