#include "contact.h"
#include "qtcontactform.h"
#include "qteditcontactdialog.h"
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>


QtEditContactDialog::QtEditContactDialog(Contact &c, 
                                        QWidget *parent,
                                        Qt::WindowFlags f) :
                                        QDialog(parent, f),
                                        contactForm(new QtContactForm()),
                                        contactToEdit(c)
{
    QVBoxLayout *mainContainer = new QVBoxLayout();
    mainContainer->addLayout(contactForm);

    QHBoxLayout *buttonContainer = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Cancel");
    buttonContainer->addWidget(okButton);
    buttonContainer->addWidget(cancelButton);
    mainContainer->addLayout(buttonContainer);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    fillForm();
    setLayout(mainContainer);
    setWindowTitle("Edit Contact");
}

void QtEditContactDialog::fillForm()
{
    contactForm->firstNameField->setText(contactToEdit.firstName);
    contactForm->lastNameField->setText(contactToEdit.lastName);
    contactForm->addressField->setText(contactToEdit.address);
    contactForm->phoneNumberField->setText(QString::number(contactToEdit.phoneNumber));
    contactForm->emailField->setText(contactToEdit.email);

}

void QtEditContactDialog::accept()
{
    contactToEdit.firstName = contactForm->firstNameField->text();
    contactToEdit.lastName = contactForm->lastNameField->text();
    contactToEdit.address = contactForm->addressField->text();
    contactToEdit.phoneNumber = contactForm->phoneNumberField->text().toLongLong();
    contactToEdit.email = contactForm->emailField->text();

    QDialog::accept();

}
