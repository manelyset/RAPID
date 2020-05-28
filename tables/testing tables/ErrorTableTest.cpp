#include "UnitTest++.h"
#include "ErrorTable.h"
#include "../../TreeNode.h"

namespace {
    ErrorTable errorTable;


    TEST(message_search_test) {
        TreeNode err0004 = TreeNode("error_0004_message");
        TreeNode err0008 = TreeNode("error_0008_message");
        TreeNode err0010 = TreeNode("error_0010_message");

        errorTable.insertError("error_0004", &err0004);
        errorTable.insertError("error_0008", &err0008);
        errorTable.insertError("error_0010", &err0010);


        CHECK_EQUAL("error_0008_message", (*errorTable.getTree("error_0008")).getMessage());
        CHECK_EQUAL((TreeNode*)nullptr, errorTable.getTree("error_0002"));

    }

}
