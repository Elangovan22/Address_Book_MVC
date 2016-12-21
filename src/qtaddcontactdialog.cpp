#include "contact.h"
#include "qtaddcontactdialog.h"
#include <QtWidgets/QDialog>
#include <QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

QtAddContactDialog::QtAddContactDialog(Contact &c, QWidget *parent, Qt::WindowFlags f) :
            QDialog(parent, f), contactForm(new QtContactForm()), outContact(c)
{
    QVBoxLayout *mainContainer = new QVBoxLayout();
    mainContainer->addLayout(contactForm);

    QHBoxLayout *buttonContainer = new QHBoxLayout();
    QPushButton *addButton = new QPushButton("Add");
    QPushButton *cancelButton = new QPushButton("Cancel");
    
    buttonContainer->addWidget(addButton);
    buttonContainer->addWidget(cancelButton);
    mainContainer->addLayout(buttonContainer);

    connect(addButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setLayout(mainContainer);
    setWindowTitle("New Contact");
}

void QtAddContactDialog::accept()
{
    outContact.firstName = contactForm->firstNameField->text();
    outContact.lastName = contactForm->lastNameField->text();
    outContact.address = contactForm->addressField->text();
    outContact.phoneNumber = contactForm->phoneNumberField->text().toLongLong();
    outContact.email = contactForm->emailField->text();

    QDialog::accept();
}
