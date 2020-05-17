#include "UnitTest++.h"
#include "RetcodeTable.h"

namespace {
    RetcodeTable retcodeTable;

    TEST(ID_search_test) {

        retcodeTable.insertRetcode(4, "error_0004");
        retcodeTable.insertRetcode(8, "error_0008");
        retcodeTable.insertRetcode(10, "error_0010");


        CHECK_EQUAL("error_0010", retcodeTable.getId(10));

        retcodeTable.insertRetcode(8, "error_0082");
        CHECK_EQUAL("error_0008", retcodeTable.getId(8));

    }

}

