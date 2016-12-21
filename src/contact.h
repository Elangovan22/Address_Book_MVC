#ifndef CORE_CONTACT_H
#define CORE_CONTACT_H

/************************************************************
    Class: Contact

    Author: Phil Grohe

    Data structure to hold a single address book contact's
    info.
************************************************************/

#include <QString>
#include <vector>

class Contact 
{
    public:

        typedef std::vector<Contact> ContactRecordSet;
        typedef unsigned int ContactId;
        static const ContactId INVALID_ID = 0;

        ContactId id;
        QString firstName;
        QString lastName;
        long long  phoneNumber;
        QString address;
        QString email;

        Contact():id(0), firstName(), lastName(), phoneNumber(), email(){ }
        bool isValidToAdd() const;
       // bool isEmpty() const;

};

#endif
