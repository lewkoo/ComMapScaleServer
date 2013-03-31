#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <QFile>
#include <QTextStream>

class DataLogger
{
public:
    static const QString LOG_PATH;
    static const char DELIM;

public:
    DataLogger(QString clientId);

private:
    QFile posFile;
    QFile vwFile;
    QFile clickFile;
    QTextStream posFileOut;
    QTextStream vwFileOut;
    QTextStream clickFileOut;
    QString clientId;

public:
    void closeFiles ();
    void writePos (QString time, QString lat, QString lon, QString topLeftLat, QString topLeftLon, QString botRightLat, QString botRightLon, QString scale);
    void writeVw (QString time, QString lat, QString lon, QString topLeftLat, QString topLeftLon, QString botRightLat, QString botRightLon, QString scale);
    void writeClick(QString time, QString lat, QString lon, QString topLeftLat, QString topLeftLon, QString botRightLat, QString botRightLon, QString scale, QString iconType);
    void writeClick(QString time, QString iconType );

private:
    void createFiles ();

};

#endif // DATALOGGER_H
