#ifndef LICENSE_HPP
#define LICENSE_HPP

/**
 *	\file			license.hpp
 *	\brief			Header of LicenseManager class
 *
 *					This header contains useful class to manage application license
 *
 *  \details        System :                Vera GUI
 *                  Component Name :        vera
 *                  Status :                Version 1.0.0 Release 1
 *                  Language :              C++
 * 
 *                  Platform Dependencies:  GNU/Linux, Windows, MacOS
 * 
 *  \copyright      GPLv3+ : GNU GPL version 3 or later
 *                  Licencied Material - Property of IMT ATLANTIQUE
 *                  © Copyright - UHA - ENSISA 2020
 * 
 *  \author         Hethsron Jedaël BOUEYA (hethsron-jedael.boueya@uha.fr)
 * 
 *  \bug            No known bug to date
 *  \date           21th May 2020
 */

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

class License : public QWizardPage
{
    public:
        /**
         * @fn      License
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent          QWidget instance
         */
        explicit License(QWidget* parent = nullptr);

        /**
         * @fn      ~License
         * @brief   Destructor of class
         */
        virtual ~License();

        /**
         * @fn      nextId
         * @brief   Virtual function that is called to find out which page to show when the user clicks the Next button
         * 
         * @return          ID of the next page, or -1 if no page follows
         */
        virtual int nextId() const override;

    private:
        QLabel* topLabel;                   /*!< QLabel instance */
        QRadioButton* registerButton;       /*!< QRadioButton register instance */
        QRadioButton* evaluateButton;       /*!< QRadioButton evaluate instance */
};

class Evaluate : public QWizardPage
{
    public:
        /**
         * @fn      Evaluate
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent          QWidget instance
         */
        explicit Evaluate(QWidget* parent = nullptr);
        
        /**
         * @fn      ~Evaluate
         * @brief   Destructor of class
         */
        virtual ~Evaluate();

        /**
         * @fn      nextId
         * @brief   Virtual function that is called to find out which page to show when the user clicks the Next button
         * 
         * @return          ID of the next page, or -1 if no page follows
         */
        virtual int nextId() const override;

    private:
        QLabel* nameLabel;                  /*!< QLabel name instance */
        QLabel* emailLabel;                 /*!< QLabel email instance */
        QLineEdit* nameLineEdit;            /*!< QLineEdit name instance */
        QLineEdit* emailLineEdit;           /*!< QLineEdit email instance */
};

class Register : public QWizardPage
{
    public:
        /**
         * @fn      Register
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent          QWidget instance
         */
        explicit Register(QWidget* parent = nullptr);

        /**
         * @fn      ~Register
         * @brief   Destructor of class
         */
        virtual ~Register();

        /**
         * @fn      nextId
         * @brief   Virtual function that is called to find out which page to show when the user clicks the Next button
         * 
         * @return          ID of the next page, or -1 if no page follows
         */
        virtual int nextId() const override;

    private:
        QLabel* nameLabel;                  /*!< QLabel name instance */
        QLabel* upgradeKeyLabel;            /*!< QLabel upgrade key instance */
        QLineEdit* nameLineEdit;            /*!< QLineEdit name instance */
        QLineEdit* upgradeKeyLineEdit;      /*!< QLineEdit upgrade key instance */
};

class Detail : public QWizardPage
{
    public:
        /**
         * @fn      Detail
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent          QWidget instance
         */
        explicit Detail(QWidget* parent = nullptr);

        /**
         * @fn      ~Detail
         * @brief   Destructor of class
         */
        virtual ~Detail();

        /**
         * @fn      nextId
         * @brief   Virtual function that is called to find out which page to show when the user clicks the Next button
         * 
         * @return          ID of the next page, or -1 if no page follows
         */
        virtual int nextId() const override;

    private:
        QLabel* companyLabel;               /*!< QLabel company instance */
        QLabel* emailLabel;                 /*!< QLabel email instance */
        QLabel* postalLabel;                /*!< QLabel postal instance */
        QLineEdit* companyLineEdit;         /*!< QLineEdit company instance */
        QLineEdit* emailLineEdit;           /*!< QLineEdit email instance */
        QLineEdit* postalLineEdit;          /*!< QLineEdit postal instance */
};

class Conclusion : public QWizardPage
{
    Q_OBJECT

    public:
        /**
         * @fn      Conclusion
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent          QWidget instance
         */
        explicit Conclusion(QWidget* parent = nullptr);

        /**
         * @fn      ~Conclusion
         * @brief   Destructor of class
         */
        virtual ~Conclusion();

        /**
         * @fn      nextId
         * @brief   Virtual function that is called to find out which page to show when the user clicks the Next button
         * 
         * @return          ID of the next page, or -1 if no page follows
         */
        virtual int nextId() const override;

        /**
         * @fn      initializePage
         * @brief   Virtual function that is called to prepare the page just before it is shown either as a result
         */
        virtual void initializePage() override;

        /**
         * @fn      setVisible
         * @brief   Virtual function that is called to set the widget to visible status
         * 
         * @param[in]       visible         Status
         */
        virtual void setVisible(bool visible) override;

    private slots:
        /**
         * @fn      print
         * @brief   Virtual function that references License printing
         */
        virtual void print();

    private:
        QLabel* bottomLabel;                /*!< QLabel Bottom label instance */
        QCheckBox* agreeCheckBox;           /*!< QCheckBox agree instance */
};

class LicenseManager : public QWizard
{
    Q_OBJECT

    public:
        enum
        {
            Licenses,                       /*!< ID of License page */
            Evaluates,                      /*!< ID of Evaluate page */
            Registers,                      /*!< ID of Register page */
            Details,                        /*!< ID of Details page */
            Conclusions                     /*!< ID of conclusion page */
        };

        /**
         * @fn      LicenseManager
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent          QWidget instance
         */
        explicit LicenseManager(QWidget* parent = nullptr);

        /**
         * @fn      ~LicenseManager
         * @brief   Destructor of class
         */
        virtual ~LicenseManager();

    private slots:
        /**
         * @fn      showHelp
         * @brief   Virtual function that shows Help window
         */
        virtual void showHelp();
};

#endif // ! LICENSE_HPP