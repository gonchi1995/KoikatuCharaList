#ifndef MYSTANDARDITEM_H
#define MYSTANDARDITEM_H

#include <QStandardItem>

class MyStandardItem : public QStandardItem
{
public:
    MyStandardItem();

private:
    QString m_url;

public:
    inline QString getUrl() const {return m_url;}
    inline void setUrl(QString url) {m_url = url;}

};

#endif // MYSTANDARDITEM_H
