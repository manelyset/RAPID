#include "UnitTest++.h"
#include "FieldTable.h"

namespace {
    FieldTable fieldTable;


    TEST (making_a_request) {
        fieldTable.insertField("device_ID", 4);
        fieldTable.insertField("box_ID", 4); //inserting default values
        fieldTable.insertField("cmd_code", 4, "0002");

        fieldTable.setValue("device_ID", "40A81"); //longer then size
        fieldTable.setValue("box_ID", "3"); //shorter then size

        std::__cxx11::string request = fieldTable.makeRequest();

        CHECK_EQUAL("0A8100030002", fieldTable.makeRequest());
    }
}
