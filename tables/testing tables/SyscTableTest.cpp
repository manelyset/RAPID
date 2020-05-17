#include "UnitTest++.h"
#include "FieldTable.h"
#include "SyscTable.h"
#include <queue>

namespace {
    FieldTable fieldTable_1, fieldTable_2, fieldTable_3;
    SyscTable syscTable;
    std::queue<std::__cxx11::string> requestQueue;

    TEST (test_isAdded_method) {
        fieldTable_1.insertField("device_ID", 4, "40A81");
        fieldTable_1.insertField("box_ID", 4, "3");
        fieldTable_1.insertField("cmd_code", 4, "0002");
        syscTable.insertSyscall("sysc_1", fieldTable_1);

        fieldTable_2.insertField("cmd_code", 4, "005A");
        syscTable.insertSyscall("sysc_2", fieldTable_2);

        fieldTable_3.insertField("box_ID", 4, "3");
        fieldTable_3.insertField("cmd_code", 4, "0015");
        syscTable.insertSyscall("sysc_3", fieldTable_3);

        CHECK_EQUAL(true, syscTable.isAdded("sysc_1"));
        CHECK_EQUAL(false, syscTable.isAdded("sysc_4"));

        requestQueue = syscTable.makeRequestQueue();

        CHECK_EQUAL("0A8100030002",requestQueue.front());
        requestQueue.pop();
        CHECK_EQUAL("005A", requestQueue.front());
        requestQueue.pop();
        CHECK_EQUAL("00030015", requestQueue.front());
        requestQueue.pop();
        CHECK(requestQueue.empty());

    }



}
