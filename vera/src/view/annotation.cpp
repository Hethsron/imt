#include <view/annotation.hpp>
#include <core/reader.hpp>

GeneralTab::GeneralTab(const QFileInfo& fileInfo, const QString& location, QWidget* parent)
    : QWidget(parent) {
        // Define label of file name
        QLabel* fileNameLabel = new QLabel(tr("File Name :"), this);
        QLineEdit* fileNameEdit = new QLineEdit(fileInfo.fileName(), this);

        // Define label of location
        QLabel* locationLabel = new QLabel(tr("Location :"), this);
        QLabel* locationValueLabel = nullptr;

        // Check if file exists
        if (fileInfo.exists()) {
            locationValueLabel = new QLabel(fileInfo.absoluteFilePath(), this);
        }
        else {
            QDir dir(location);
            locationValueLabel =  new QLabel(dir.filePath(fileInfo.fileName()), this);
        }

        locationValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

        // Define label of size
        QLabel* sizeLabel = new QLabel(tr("Size :"), this);
        qlonglong size = fileInfo.size() / 1024;
        QLabel *sizeValueLabel = new QLabel(tr("%1 K").arg(size), this);
        sizeValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

        // Define label of last read
        QLabel *lastReadLabel = new QLabel(tr("Last Read :"), this);
        QLabel* lastReadValueLabel = new QLabel(fileInfo.lastRead().toString(), this);
        lastReadValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

        // Define label of last modified
        QLabel* lastModifiedLabel = new QLabel(tr("Last Modified :"), this);
        QLabel* lastModifiedValueLabel = new QLabel(fileInfo.lastModified().toString(), this);
        lastModifiedValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

        // Define QVBoxLayout instance
        QVBoxLayout* vLayout = new QVBoxLayout(this);
        vLayout->addWidget(fileNameLabel);
        vLayout->addWidget(fileNameEdit);
        vLayout->addWidget(locationLabel);
        vLayout->addWidget(locationValueLabel);
        vLayout->addWidget(sizeLabel);
        vLayout->addWidget(sizeValueLabel);
        vLayout->addWidget(lastReadLabel);
        vLayout->addWidget(lastReadValueLabel);
        vLayout->addWidget(lastModifiedLabel);
        vLayout->addWidget(lastModifiedValueLabel);
        vLayout->addStretch(1);

        // Update layout
        setLayout(vLayout);
    }

GeneralTab::~GeneralTab() {}

SecurityTab::SecurityTab(const QFileInfo& fileInfo, QWidget* parent)
    : QWidget(parent) {
        // Define users and groups
        QGroupBox* ownerGroup = new QGroupBox(tr("Users And Groups Permissions"));
        
        // Define users label
        QLabel* usersLabel = new QLabel(tr("Users :"));
        QLabel* usersValueLabel = new QLabel(fileInfo.owner());
        usersValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        
        // Define groups label
        QLabel* groupsLabel = new QLabel(tr("Groups :"));
        QLabel* groupsValueLabel = new QLabel(fileInfo.group());
        groupsValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

        // Define permission group
        QGroupBox* permissionsGroup = new QGroupBox(tr("File System Permission"));

        // Define readable checkbox
        QCheckBox* readable = new QCheckBox(tr("Readable"));
        if (fileInfo.isReadable()) {
            readable->setChecked(true);
        }

        // Define writable checkbox
        QCheckBox* writable = new QCheckBox(tr("Writable"));
        if (fileInfo.isWritable()) {
            writable->setChecked(true);
        }

        // Define executable checkbox
        QCheckBox* executable = new QCheckBox(tr("Executable"));
        if (fileInfo.isExecutable()) {
            executable->setChecked(true);
        }

        // Define ower layout
        QVBoxLayout* ownerLayout = new QVBoxLayout(this);
        ownerLayout->addWidget(usersLabel);
        ownerLayout->addWidget(usersValueLabel);
        ownerLayout->addWidget(groupsLabel);
        ownerLayout->addWidget(groupsValueLabel);
        ownerGroup->setLayout(ownerLayout);

        // Define file system permission layout
        QVBoxLayout* permissionsLayout = new QVBoxLayout(this);
        permissionsLayout->addWidget(readable);
        permissionsLayout->addWidget(writable);
        permissionsLayout->addWidget(executable);
        permissionsGroup->setLayout(permissionsLayout);

        // Define vertical layout
        QVBoxLayout* vLayout = new QVBoxLayout(this);
        vLayout->addWidget(ownerGroup);
        vLayout->addWidget(permissionsGroup);
        vLayout->addStretch(1);

        // Update layout
        setLayout(vLayout);
    }

SecurityTab::~SecurityTab() {}

DetailsTab::DetailsTab(const QFileInfo& fileInfo, QWidget* parent)
    : QWidget(parent), titleValueLabel(nullptr), videoRangeValueLabel(nullptr), descriptionValueLabel(nullptr), storage(QJsonDocument()), status(false) {
        // Define file name
        const QString fileName = fileInfo.absoluteFilePath();

        // Define file stream
        QFile file(fileName);

        // Check if file exists
        if (file.exists()) {
            // Check if file is open on readonly
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                // Read data configuration
                const QString data = file.readAll();

                // Close file stream
                file.close();

                storage = QJsonDocument::fromJson(data.toUtf8());
                // Check if config file is empty
                if (!storage.isEmpty()) {
                    // Update status
                    status = true;
                }
            }
        }
        
        // Define group box
        QGroupBox* contentsGroup = new QGroupBox(tr("Contents"));
        
        // Define title
        QLabel* titleLabel = new QLabel(tr("Title :"));
        if (status) {
            titleValueLabel = new QLineEdit(Reader::release(storage, QString("^(Title)$")), this);
        }
        else {
            titleValueLabel = new QLineEdit(this);
        }
        titleValueLabel->setToolTip(tr("Content title"));

        // Define video range
        QLabel* videoRangeLabel = new QLabel(tr("Video Range :"));
        if (status) {
            videoRangeValueLabel = new QLineEdit(Reader::release(storage, QString("^(Range)$")), this);
        }
        else {
            videoRangeValueLabel = new QLineEdit(this);
        }
        videoRangeValueLabel->setToolTip(tr("hh:mm:ss - hh:mm:ss"));

        // Define description
        QLabel* descriptionLabel = new QLabel(tr("Description :"));
        if (status) {
            descriptionValueLabel = new QTextEdit(Reader::release(storage, QString("^(Description)$")), this);
        }
        else {
            descriptionValueLabel = new QTextEdit(this);
        }
        descriptionValueLabel->setToolTip(tr("Content description"));

        // Define contents layout
        QVBoxLayout* contentsLayout = new QVBoxLayout(this);
        contentsLayout->addWidget(titleLabel);
        contentsLayout->addWidget(titleValueLabel);
        contentsLayout->addWidget(videoRangeLabel);
        contentsLayout->addWidget(videoRangeValueLabel);
        contentsLayout->addWidget(descriptionLabel);
        contentsLayout->addWidget(descriptionValueLabel);
        contentsGroup->setLayout(contentsLayout);

        // Define vertical layout
        QVBoxLayout* vLayout = new QVBoxLayout(this);
        vLayout->addWidget(contentsGroup);
        vLayout->addStretch(1);

        // Update layout
        setLayout(vLayout);
    }

DetailsTab::~DetailsTab() {}

QJsonDocument DetailsTab::get() const {
    // Define Json object
    QJsonObject obj;
    obj["Title"] = titleValueLabel->text();
    obj["Range"] = videoRangeValueLabel->text();
    obj["Description"] = descriptionValueLabel->toPlainText();
    
    // Update storage
    return QJsonDocument(obj);
}

Annotation::Annotation(const QString& fileName, const QJsonDocument& cfg, QWidget* parent)
    : QDialog(parent), details(nullptr), config(cfg), location(QString()), name(fileName) {
        // Define location
        location = Reader::release(config, QString("^(Annotation(s)?)$"));
        
        // Define directory
        QDir dir(location);

        // Check if directory exists
        if (dir.exists()) {
            QFileInfo fileInfo(dir.filePath(fileName));
            details = new DetailsTab(fileInfo, this);

            // Define QTabWidget instance
            widget = new QTabWidget(this);
            widget->addTab(new GeneralTab(fileInfo, location), tr("General"));
            widget->addTab(new SecurityTab(fileInfo), tr("Security"));
            widget->addTab(details, tr("Details"));

            // Define button
            button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            connect(button, &QDialogButtonBox::accepted, this, &Annotation::write);
            connect(button, &QDialogButtonBox::rejected, this, &QDialog::close);

            // Define vertical layout
            QVBoxLayout* vLayout = new QVBoxLayout(this);
            vLayout->addWidget(widget);
            vLayout->addWidget(button);

            // Update title
            setWindowTitle(tr("Annotations"));
        }
    }

Annotation::~Annotation() {}

void Annotation::write() {
    // Define file Name
    QDir dir(location);

    // Check if location exists
    if (dir.exists() && !name.isEmpty()) {
        QFile file(dir.filePath(name));

        // Check if file is not open on writeonly
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate)) {
            QMessageBox::information(this->widget, 
                        tr("Unable to save annotation file"), 
                        file.errorString());
            return;
        }

        // Write Json file
        file.write(details->get().toJson());

        // Close file stream
        file.close();

        // Close dialog
        this->reject();
    }
}