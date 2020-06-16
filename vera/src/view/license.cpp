#include <view/license.hpp>
#include <QtPrintSupport/QtPrintSupport>
#include <core/boxes.hpp>

License::License(QWidget* parent)
    : QWizardPage(parent), topLabel(nullptr), registerButton(nullptr), evaluateButton(nullptr) {
        // Define title
        setTitle(tr("License Manager"));

        // Define pixmap watermark
        Boxes infos;
        setPixmap(QWizard::WatermarkPixmap, QPixmap(infos.getCollections().at(13)));

        // Update top label
        topLabel = new QLabel(tr("This manager will help you to register your copy  of "
                                "<i>Vera</i> &copy; Plateform; or start "
                                "evaluating the product."));
        topLabel->setWordWrap(true);

        // Update QRadioButton
        registerButton = new QRadioButton(tr("&Register your copy"));
        evaluateButton = new QRadioButton(tr("&Evaluate the product for 30 days"));
        registerButton->setChecked(true);

        // Define vertical layout
        QVBoxLayout* vLayout = new QVBoxLayout(this);
        vLayout->addWidget(topLabel);
        vLayout->addWidget(registerButton);
        vLayout->addWidget(evaluateButton);

        // Update layout
        setLayout(vLayout);
    }

License::~License() {}

int License::nextId() const {
    // Check if evalute button is checked
    if (evaluateButton->isChecked()) {
        // Return Evaluate ID
        return LicenseManager::Evaluates;
    }
    else {
        // Return Register ID
        return LicenseManager::Registers;
    }
}

Evaluate::Evaluate(QWidget* parent)
    : QWizardPage(parent), nameLabel(nullptr), emailLabel(nullptr), nameLineEdit(nullptr), emailLineEdit(nullptr) {
        // Define title
        setTitle(tr("Evaluate <i>Vera</i> &copy; Plateform"));
        
        // Define subtitle
        setSubTitle(tr("Please fill both fields. Make sure to provide a valid email address (e.g., tony.stark@example.com)."));

        // Update name labels
        nameLabel = new QLabel(tr("&Name :"));
        nameLineEdit = new QLineEdit(this);
        nameLabel->setBuddy(nameLineEdit);

        // Define email regex
        const QString emailRegExp = QStringLiteral(".+@.+");

        // Update email labels
        emailLabel = new QLabel(tr("&Email address :"));
        emailLineEdit = new QLineEdit(this);
        emailLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression(emailRegExp), this));
        emailLabel->setBuddy(emailLineEdit);

        // Register fields
        registerField("evaluate.name*", nameLineEdit);
        registerField("evaluate.email*", emailLineEdit);

        // Define grid layout
        QGridLayout *gLayout = new QGridLayout(this);
        gLayout->addWidget(nameLabel, 0, 0);
        gLayout->addWidget(nameLineEdit, 0, 1);
        gLayout->addWidget(emailLabel, 1, 0);
        gLayout->addWidget(emailLineEdit, 1, 1);

        // Update layout
        setLayout(gLayout);
    }

Evaluate::~Evaluate() {}

int Evaluate::nextId() const {
    // Return Conclusion ID
    return LicenseManager::Conclusions;
}

Register::Register(QWidget* parent)
    : QWizardPage(parent), nameLabel(nullptr), upgradeKeyLabel(nullptr), nameLineEdit(nullptr), upgradeKeyLineEdit(nullptr) {
        // Define title
        setTitle(tr("Register your copy of <i>Vera</i> &copy; Plateform"));
        
        // Define subtitle
        setSubTitle(tr("If you have an upgrade key, please fill in the appropriate field"));

        // Update name labels
        nameLabel = new QLabel(tr("&Name :"));
        nameLineEdit = new QLineEdit(this);
        nameLabel->setBuddy(nameLineEdit);

        // Update upgrade key label
        upgradeKeyLabel = new QLabel(tr("&Upgrade key :"));
        upgradeKeyLineEdit = new QLineEdit(this);
        upgradeKeyLabel->setBuddy(upgradeKeyLineEdit);

        // Register fields
        registerField("register.name*", nameLineEdit);
        registerField("register.upgradeKey", upgradeKeyLineEdit);

        // Define grid layout
        QGridLayout* gLayout = new QGridLayout(this);
        gLayout->addWidget(nameLabel, 0, 0);
        gLayout->addWidget(nameLineEdit, 0, 1);
        gLayout->addWidget(upgradeKeyLabel, 1, 0);
        gLayout->addWidget(upgradeKeyLineEdit, 1, 1);

        // Update layout
        setLayout(gLayout);
    }

Register::~Register() {}

int Register::nextId() const {
    // Check if upgrade key is empty
    if (upgradeKeyLineEdit->text().isEmpty()) {
        // Returns Details ID
        return LicenseManager::Details;
    }
    else {
        // Return Conclusion ID
        return LicenseManager::Conclusions;
    }
}

Detail::Detail(QWidget* parent)
    : QWizardPage(parent), companyLabel(nullptr), emailLabel(nullptr), postalLabel(nullptr), companyLineEdit(nullptr), emailLineEdit(nullptr), postalLineEdit(nullptr) {
        // Define title
        setTitle(tr("Fill In Your Details"));

        // Define subtitle
        setSubTitle(tr("Please fill all three fields. Make sure to provide a valid email address (e.g., tony.stark@example.com)"));

        // Update company label
        companyLabel = new QLabel(tr("&Company name :"));
        companyLineEdit = new QLineEdit(this);
        companyLabel->setBuddy(companyLineEdit);

        // Define email regex
        const QString emailRegExp = QStringLiteral(".+@.+");

        // Update email label
        emailLabel = new QLabel(tr("&Email address :"));
        emailLineEdit = new QLineEdit(this);
        emailLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression(emailRegExp)));
        emailLabel->setBuddy(emailLineEdit);

        // Update postal label
        postalLabel = new QLabel(tr("&Postal address :"));
        postalLineEdit = new QLineEdit(this);
        postalLabel->setBuddy(postalLineEdit);

        // Register fields
        registerField("details.company*", companyLineEdit);
        registerField("details.email*", emailLineEdit);
        registerField("details.postal*", postalLineEdit);

        // Define grid layout
        QGridLayout* gLayout = new QGridLayout(this);
        gLayout->addWidget(companyLabel, 0, 0);
        gLayout->addWidget(companyLineEdit, 0, 1);
        gLayout->addWidget(emailLabel, 1, 0);
        gLayout->addWidget(emailLineEdit, 1, 1);
        gLayout->addWidget(postalLabel, 2, 0);
        gLayout->addWidget(postalLineEdit, 2, 1);

        // Update layout
        setLayout(gLayout);
    }

Detail::~Detail() {}

int Detail::nextId() const {
    // Return Conclusion ID
    return LicenseManager::Conclusions;
}

Conclusion::Conclusion(QWidget* parent)
    : QWizardPage(parent), bottomLabel(nullptr), agreeCheckBox(nullptr) {
        // Define title
        setTitle(tr("Complete Your Registration"));

        // Define pixmap watermark
        Boxes infos;
        setPixmap(QWizard::WatermarkPixmap, QPixmap(infos.getCollections().at(13)));

        // Update label
        bottomLabel = new QLabel(this);
        bottomLabel->setWordWrap(true);

        // Update QCheckBox
        agreeCheckBox = new QCheckBox(tr("I agrre to the terms of the license"));

        // Register the fields
        registerField("conclusion.agree*", agreeCheckBox);

        // Define vertical layout
        QVBoxLayout* vLayout = new QVBoxLayout(this);
        vLayout->addWidget(bottomLabel);
        vLayout->addWidget(agreeCheckBox);

        // Update layout
        setLayout(vLayout);
    }

Conclusion::~Conclusion() {}

int Conclusion::nextId() const {
    // Return ID
    return -1;
}

void Conclusion::initializePage() {
    // Define license text
    QString text;

    // Check if page is visited
    if (wizard()->hasVisitedPage(LicenseManager::Evaluates)) {
        text = tr("<u>Evaluation License Agreement:</u> "
                    "You can use this software for 30 days and make one "
                    "backup, but you are not allowed to distribute it.");
    }
    else if (wizard()->hasVisitedPage(LicenseManager::Details)) {
        text = tr("<u>First-Time License Agreement:</u> "
                    "You can use this software subject to the license "
                    "you will receive by email.");
    }
    else {
        text = tr("<u>Upgrade License Agreement:</u> "
                    "This software is licensed under the terms of your "
                    "current license.");
    }

    // Set text
    bottomLabel->setText(text);
}

void Conclusion::setVisible(bool visible) {
    // Update view
    QWizardPage::setVisible(true);

    // Check if page is visible
    if (visible) {
        wizard()->setButtonText(QWizard::CustomButton1, tr("&Print"));
        wizard()->setOption(QWizard::HaveCustomButton1, true);
        connect(wizard(), &QWizard::customButtonClicked, this, &Conclusion::print);
    }
    else {
        wizard()->setOption(QWizard::HaveCustomButton1, false);
        disconnect(wizard(), &QWizard::customButtonClicked, this, &Conclusion::print);
    }
}

void Conclusion::print() {
    // Define printer
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QMessageBox::warning(this, tr("License"), tr("As an environmentally friendly measure, the license text will not actually be printed."));
    }
}

LicenseManager::LicenseManager(QWidget* parent)
    : QWizard(parent) {
        // Define window title
        setWindowTitle(tr("License Manager"));

        // Define page
        setPage(Licenses, new License());
        setPage(Evaluates, new Evaluate());
        setPage(Registers, new Register());
        setPage(Details, new Detail());
        setPage(Conclusions, new Conclusion());

        // Define start Id
        setStartId(Licenses);

        // Define option
        setOption(HaveHelpButton, true);
        connect(this, &QWizard::helpRequested, this, &LicenseManager::showHelp);
    }

LicenseManager::~LicenseManager() {}

void LicenseManager::showHelp() {
    // Define message
    static QString lastHelpMessage;
    QString message;

    switch(currentId()) {
        case Licenses:
            message = tr("The decision you make here will affect which page you get to see next.");
            break;
        case Evaluates:
            message = tr("Make sure to provide a valid email address, such as tony.stark@example.com.");
            break;
        case Registers:
            message = tr("If you don't provide an upgrade key, you will be asked to fill in your details.");
            break;
        case Details:
            message = tr("Make sure to provide a valid email address, such as tony.stark@example.com.");
            break;
        case Conclusions:
            message = tr("You must accept the terms and conditions of the license to proceed.");
            break;
            default:
                message = tr("This help is likely not to be of any help.");
                break;
    }

    if (lastHelpMessage == message) {
        message = tr("Sorry, I already gave what help I could. Maybe you should try asking a human?");
    }

    QMessageBox::information(this, tr("License Manager Help"), message);
    lastHelpMessage = message;
}