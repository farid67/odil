#define BOOST_TEST_MODULE CGetRequest
#include <boost/test/unit_test.hpp>

#include "odil/message/CGetRequest.h"
#include "odil/DataSet.h"
#include "odil/DataSet.h"
#include "odil/message/Message.h"
#include "odil/registry.h"

#include "../../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<odil::message::CGetRequest>
{
    odil::DataSet command_set;
    odil::DataSet query;

    Fixture()
    {
        this->command_set.add(
            "CommandField", {odil::message::Message::Command::C_GET_RQ});
        this->command_set.add("MessageID", {1234});
        this->command_set.add("AffectedSOPClassUID",
            {odil::registry::PatientRootQueryRetrieveInformationModelGET});
        this->command_set.add(
            "Priority", {odil::message::Message::Priority::MEDIUM});

        this->query.add("PatientName", {"Doe^John"});
        this->query.add("StudyDescription", {"Brain"});
        this->query.add("QueryRetrieveLevel", {"STUDY"});
    }

    virtual void check(odil::message::CGetRequest const & message)
    {
        BOOST_CHECK_EQUAL(
            message.get_command_field(),
            odil::message::Message::Command::C_GET_RQ);
        BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(),
            odil::registry::PatientRootQueryRetrieveInformationModelGET);
        BOOST_CHECK(message.has_data_set());
        BOOST_CHECK(message.get_data_set() == this->query);
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    odil::message::CGetRequest const message(
        1234, odil::registry::PatientRootQueryRetrieveInformationModelGET,
        odil::message::Message::Priority::MEDIUM, this->query);
    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set, this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    this->command_set.as_int("CommandField") = {
        odil::message::Message::Command::C_ECHO_RQ};
    this->check_message_constructor_throw(this->command_set, this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingAffectSOPClass, Fixture)
{
    this->command_set.remove("AffectedSOPClassUID");
    this->check_message_constructor_throw(this->command_set, this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingPriority, Fixture)
{
    this->command_set.remove("Priority");
    this->check_message_constructor_throw(this->command_set, this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorEmptyQuery, Fixture)
{
    odil::DataSet empty;
    this->check_message_constructor_throw(this->command_set, empty);
}
