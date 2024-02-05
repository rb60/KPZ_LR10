#ifndef RESUME_H
#define RESUME_H
#include <QString>
#include <QDate>
#include <QList>
#include <QRegularExpression>

struct Experience
{
    Experience();
    Experience(    QDate fromDate,
              QDate toDate,
              QString companyName,
              QString position);
    QDate fromDate;
    QDate toDate;
    QString companyName;
    QString position;
};

class IResume
{
public:
    virtual void setName(QString name) = 0;
    virtual void setLastName(QString name) = 0;
    virtual void setSecondnName(QString name) = 0;
    virtual void setPosition(QString position) = 0;
    virtual void setPhone(QString phone) = 0;

    virtual QString getName() = 0;
    virtual QString getLastName() = 0;
    virtual QString getSecondnName() = 0;
    virtual QString getPosition() = 0;
    virtual QString getPhone() = 0;

    virtual void addExperience(Experience experience) = 0;
    virtual Experience getExperience(int index) = 0;
    virtual void removeExperience(int index) = 0;
    virtual int getExperienceCount() = 0;

    virtual QString toHTML() = 0;

    virtual ~IResume(){}

};


class Resume : public IResume
{
private:
    QString name;
    QString lastName;
    QString secondName;
    QString position;
    QString phone;
    QList<Experience> experiences;
public:
    void setName(QString name) override;
    void setLastName(QString lastName) override;
    void setSecondnName(QString secondName) override;
    void setPosition(QString position) override;
    void setPhone(QString phone) override;

    QString getName() override;
    QString getLastName() override;
    QString getSecondnName() override;
    QString getPosition() override;
    QString getPhone() override;

    void addExperience(Experience experience) override;
    Experience getExperience(int index) override;
    void removeExperience(int index) override;
    int getExperienceCount() override;

    QString toHTML() override;

    ~Resume() override{}

};

class ResumeProxy : public IResume
{
private:
    IResume* base;
public:
    ResumeProxy(IResume* base);
    IResume *getBase();

    void setName(QString name) override;
    void setLastName(QString lastName) override;
    void setSecondnName(QString secondName) override;
    void setPosition(QString position) override;
    void setPhone(QString phone) override;

    QString getName() override;
    QString getLastName() override;
    QString getSecondnName() override;
    QString getPosition() override;
    QString getPhone() override;

    void addExperience(Experience experience) override;
    Experience getExperience(int index) override;
    void removeExperience(int index) override;
    int getExperienceCount() override;

    QString toHTML() override;

    ~ResumeProxy() override {}
};

#endif // RESUME_H
