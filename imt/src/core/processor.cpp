#include <core/processor.hpp>

Processor::Processor() {}

Processor::~Processor() {}

QJsonObject Processor::write(const QString& filename) const {
    QDir dir(filename);
    
    // Define QJsonObject instance
	QJsonObject obj;

    // Check if given directory exists
    if (dir.exists()) {
        // Set entry lists to find
        QStringList list = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDir::Name);

        // Define pattern of regex
		QString pattern = QString("^(Ambiant(s)?|Annotation(s)?|Kinect|Robot(s)?|Wearable(s)?|Xsens)$");
		
        // Define regex
        QRegularExpression re(pattern, QRegularExpression::CaseInsensitiveOption);

        QStringListIterator iterator(list);
        while(iterator.hasNext()) {
            const QString str = iterator.next();
            QRegularExpressionMatch match = re.match(str);

            // Check if finded directory match with regex
            if (match.hasMatch()) {
                
                // Save configuration data
                obj[str] = dir.filePath(str);
            }
        }
    }

    // Returns configuration data
    return obj;
}

// QString Processor::read(const QJsonDocument& cfg, const QString& pattern) const {
//     return nullptr;
// }