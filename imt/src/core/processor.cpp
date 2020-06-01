#include <core/processor.hpp>

Processor::Processor()
    : QObject() {}

Processor::~Processor() {}

QJsonObject Processor::write(const QString& cfg) const {
    QDir dir(cfg);
    
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

QList<QStringList> Processor::deepRead(const QString& cfg) const {
    QList<QStringList> assets;

    // Define root directory
    QDir root(cfg);

    // Check if root directory exists
    if (root.exists()) {
        // Get and sort inner directory in list
        QStringList list = root.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDir::Name);

        // Define activity pattern
        QString act = QString("^(a\\d+)$");

        // Define activity regex
        QRegularExpression actReg(act, QRegularExpression::CaseInsensitiveOption);

        // Define activity iterator
        QStringListIterator actIterator(list);
        while (actIterator.hasNext()) {
            const QString actStr = actIterator.next();
            QRegularExpressionMatch actMatch = actReg.match(actStr);

            // Check if finded key match with given pattern regex
            if (actMatch.hasMatch()) {
                // Define child directory
                QDir child(root.filePath(actStr));

                // Check if child directory exists
                if (child.exists()) {
                    // Define asset
                    QStringList asset;

                    // Cet and sort inner directory in list
                    QStringList ls = child.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDir::Name);

                    // Define subject pattern
                    QString subj = QString("^(s\\d+)$");

                    // Define subject regex
                    QRegularExpression subjReg(subj, QRegularExpression::CaseInsensitiveOption);

                    // Define subject iterator
                    QStringListIterator subjIterator(ls);
                    while (subjIterator.hasNext()) {
                        const QString subjStr = subjIterator.next();
                        QRegularExpressionMatch subjMatch = subjReg.match(subjStr);

                        // Check if finded key match with given pattern regex
                        if (subjMatch.hasMatch()) {

                            // Append subject in subjects list
                            asset.append(child.filePath(subjStr));
                        }
                    }

                    // Append subjects list in activities list
                    assets.append(asset);
                }
            }
        }
    }

    return assets;
}