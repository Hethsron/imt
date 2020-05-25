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

        // Define iterator
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

QString Processor::read(const QJsonDocument& cfg, const QString& pattern) const {
    QJsonObject obj = cfg.object();

    // Define distinguished name
    QString pathname;

    // Check if QJsonObject instance is empty
    if (!obj.isEmpty()) {
        // Set entry list to compare
        QStringList list = obj.keys();

        // Define regex
        QRegularExpression re(pattern, QRegularExpression::CaseInsensitiveOption);

        // Define iterator
        QStringListIterator iterator(list);
        while(iterator.hasNext()) {
            const QString str = iterator.next();
            QRegularExpressionMatch match = re.match(str);

            // Check if finded key match with given pattern regex
            if (match.hasMatch()) {

                // Save distinguished name
                pathname = obj.take(str).toString();

                // Leave loop
                break;
            }
        }
    }

    return pathname;
}