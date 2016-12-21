#include "qtcontactdetailview.h"
#include "qtcontactform.h"
#include "qterrordialog.h"
#include "errorinfo.h"
#include <QDebug>

#include <string>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGroupBox>

QtContactDetailView::QtContactDetailView(AddressBookModel& model, 
                    QWidget *parent) : 
                    QGroupBox("Contact Details", parent),
                    dataSource(model),
                    contactForm(new QtContactForm())
{

    contactForm->firstNameField->setReadOnly(true);
    contactForm->lastNameField->setReadOnly(true);
    contactForm->addressField->setReadOnly(true);
    contactForm->phoneNumberField->setReadOnly(true);
    contactForm->emailField->setReadOnly(true);

    setLayout(contactForm);
    setFlat(false);
    
}

void QtContactDetailView::displayContact(Contact::ContactId id)
{
    Contact c;
    //InDisplayContact no value is returned
    qDebug()<<"InDisplayContact";
    qDebug()<<id;
    ErrorInfo getContactErrorStatus = dataSource.getContact(id, c);

    if(getContactErrorStatus.code != ERR_OK)
    {
        //could not fetch the contact
        //simply clear the fields
        clear();
        return;
    }
    else
    {

      /*  contactForm->firstNameField->setText(c.firstName.c_str());
        contactForm->lastNameField->setText(c.lastName.c_str());
        contactForm->addressField->setText(c.address.c_str());
        contactForm->phoneNumberField->setText(c.phoneNumber.c_str());
        contactForm->emailField->setText(c.email.c_str());

            contactForm->phoneNumberField->setText(QString::number( c.phoneNumber);
        */

        contactForm->firstNameField->setText(c.firstName);
                contactForm->lastNameField->setText(c.lastName);
                contactForm->addressField->setText(c.address);
              contactForm->phoneNumberField->setText(QString::number(c.phoneNumber));
                contactForm->emailField->setText(c.email);
    }
}

void QtContactDetailView::clear()
{
    contactForm->clear();
}

