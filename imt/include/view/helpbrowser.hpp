#ifndef HELPBROWSER_HPP
#define HELPBROWSER_HPP

/**
 *	\file			helpbrowser.hpp
 *	\brief			Header of HelpBrowser class
 *
 *					This header contains an useful class to manage application help browser view
 *
 *  \details        System :                IMT GUI
 *                  Component Name :        imt
 *                  Status :                Version 1.0.0 Release 1
 *                  Language :              C++
 * 
 *                  Platform Dependencies:  GNU/Linux, Windows, MacOS
 * 
 *  \copyright      GPLv3+ : GNU GPL version 3 or later
 *                  Licencied Material - Property of IMT ATLANTIQUE
 *                  © Copyright - UHA - ENSISA 2020
 * 
 *	\author			Hethsron Jedaël BOUEYA (hethsron-jedael.boueya@uha.fr)
 * 
 * 	\bug			No known bug to date
 *  \date 			21th May 2020
 */

#include <QtWidgets/QTextBrowser>
#include <QtHelp/QHelpEngine>
#include <QtCore/QtCore>

class HelpBrowser : public QTextBrowser
{
    public:
        /**
         * @fn      HelpBrowser
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       heg         QHelpEngine instance
         * @param[in]       parent      QWidget parent instance
         */
        explicit HelpBrowser(QHelpEngine* heg, QWidget* parent = nullptr);

        /**
         * @fn      ~HelpBrowser
         * @brief   Destructor of class
         */
        virtual ~HelpBrowser();

        /**
         * @fn      loadResource
         * @brief   Virtual function that load resources for QTexBrowser view
         *          This function is called when the document is loaded and for each image in the document
         * 
         * @param[in]       type        Type of resource to be loaded
         * @param[in]       url         Uniform resource locator
         * @return          QVariant that stores a QByteArray with the contents of the file
         */
        virtual QVariant loadResource(int type, const QUrl& url) override;

    private:
        QHelpEngine* helpEngine;                /*!< QHelpEgine instance that provides access to contents and indices of the help engine */
};

#endif // ! HELPBROWSER_HPP