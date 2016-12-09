/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef __NCREATEREQUEST_H__
#define __NCREATEREQUEST_H__

#include "odil/message/Request.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief C-NCreate-RQ message.
class NCreateRequest: public Request
{
public:
    /**
     * @brief Create an NCreate request with given Message ID and
     * affected SOP class UID.
     */
    NCreateRequest(
        Value::Integer message_id,
        Value::String const & affected_sop_class_uid);

    /**
     * @brief Create a C-NCreate-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-NCreate-RQ.
     */
    NCreateRequest(Message const & message);

    /// @brief Destructor.
    virtual ~NCreateRequest();
    
    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(
        message_id, registry::MessageID)

    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
            affected_sop_class_uid, registry::AffectedSOPClassUID)

    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(
            affected_sop_instance_uid, registry::AffectedSOPInstanceUID)

    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
            attribute_list, registry::AttributeIdentifierList)

};

}

}

#endif // __NCREATEREQUEST_H__
