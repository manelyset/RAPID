#include "UnitTest++.h"
#include "FieldTable.h"
#include "SyscTable.h"
#include "TagDB.h"
#include <queue>

namespace {
    FieldTable fieldTable_1, fieldTable_2, fieldTable_3;
    SyscTable generalSyscTable, localSyscTable;
    TagDB database;
    std::queue<std::__cxx11::string> requestQueue;

    TEST (test_isAdded_method) {
        fieldTable_1.insertField("device_ID", 4);
        fieldTable_1.insertField("box_ID", 4);
        fieldTable_1.insertField("cmd_code", 4, "0002");
        generalSyscTable.insertSyscall("sysc_1", fieldTable_1);

        fieldTable_2.insertField("cmd_code", 4, "005A");
        generalSyscTable.insertSyscall("sysc_2", fieldTable_2);

        fieldTable_3.insertField("box_ID_3", 4);
        fieldTable_3.insertField("cmd_code", 4, "0015");
        generalSyscTable.insertSyscall("sysc_3", fieldTable_3);

        database.insertSyscallTag("IS_IN_BOX", "sysc_1");
        database.insertSyscallTag("IS_IN_BOX", "sysc_3");
        database.insertFieldTag("BOX", "sysc_1", "box_ID");
        database.insertFieldTag("BOX", "sysc_3", "box_ID_3");
        database.insertFieldTag("DEVICE", "sysc_1", "device_ID");

        localSyscTable = database.getSyscalls("IS_IN_BOX", generalSyscTable);

        CHECK_EQUAL(2, localSyscTable.getSize());

        database.setFieldValues("BOX", "3", localSyscTable);
        database.setFieldValues("DEVICE", "0A81", localSyscTable);

        requestQueue = localSyscTable.makeRequestQueue();

        CHECK_EQUAL("0A8100030002",requestQueue.front());
        requestQueue.pop();
        CHECK_EQUAL("00030015", requestQueue.front());
        requestQueue.pop();
        CHECK(requestQueue.empty());



    }


}
