#ifndef QMETADATA_H
#define QMETADATA_H
#include <QVariantMap>
#include <QDateTime>
#include "qaudiodata.h"
class QMetaData
{
public:
    QMetaData(){}
    QMetaData(const QVariantMap& data);
    bool operator ==(const QMetaData& obj);
    QDateTime creationTime() const;
    QString title() const;
    QString majorBrand() const;
    QString copyRight() const;
    QStringList compatibleBrands() const;
    int minorVersion() const;
    int mediaType() const;

    QAudioData audioData() const;
    friend QDebug operator<<(QDebug dbg, const QMetaData &data);

private:
    QAudioData m_audioData;
    QDateTime m_creationTime;
    QString m_title;
    QString m_majorBrand;
    QString m_copyRight;
    QStringList m_compatibleBrands;
    int m_minorVersion;
    int m_mediaType;

};

#endif // QMETADATA_H
