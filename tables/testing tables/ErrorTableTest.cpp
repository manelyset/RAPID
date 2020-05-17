#include "UnitTest++.h"
#include "ErrorTable.h"

namespace {
    ErrorTable errorTable;


    TEST(message_search_test) {
        errorTable.insertError("error_0004", "error_0004_message");
        errorTable.insertError("error_0008", "error_0008_message");
        errorTable.insertError("error_0010", "error_0010_message");

        CHECK_EQUAL("error_0008_message", errorTable.getMessage("error_0008"));
        CHECK_EQUAL("0", errorTable.getMessage("error_0002"));

    }

}
