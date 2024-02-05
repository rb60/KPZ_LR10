#include "resume.h"
#include <QRegularExpression>

Experience::Experience()
{

}

Experience::Experience(QDate fromDate, QDate toDate, QString companyName, QString position)
{
    this->fromDate = fromDate;
    this->toDate = toDate;
    this->companyName = companyName;
    this->position = position;
}

void Resume::setName(QString name)
{
    this->name = name;
}

void Resume::setLastName(QString lastName)
{
    this->lastName = lastName;
}

void Resume::setSecondnName(QString secondName)
{
    this->secondName = secondName;
}

void Resume::setPosition(QString position)
{
    this->position = position;
}

void Resume::setPhone(QString phone)
{
    this->phone = phone;
}

QString Resume::getName()
{
    return name;
}

QString Resume::getLastName()
{
    return lastName;
}

QString Resume::getSecondnName()
{
    return secondName;
}

QString Resume::getPosition()
{
    return position;
}

QString Resume::getPhone()
{
    return phone;
}

void Resume::addExperience(Experience experience)
{
    experiences.append(experience);
}

Experience Resume::getExperience(int index)
{
    if(index >= 0 && index < experiences.size())
    {
        return experiences[index];
    }
    return Experience();
}

void Resume::removeExperience(int index)
{
    if(index >= 0 && index < experiences.size())
    {
        experiences.remove(index);
    }
}

int Resume::getExperienceCount()
{
    return experiences.size();
}

QString Resume::toHTML()
{
    QString result =  "<!DOCTYPE html>"
           "<html>"
           "<head>"
           "<meta charset=\"utf-8\">"
           "</head>"
           "<body>"
           "    <h1>Resume</h1>"
           "    <div>"
           "            <span>Name: " + name + "</span>"
           "    </div>"
           "    <div>"
           "            <span>Last name: " + lastName + "</span>"
           "    </div>"
           "    <div>"
           "            <span>Second name: " + secondName + "</span>"
           "    </div>"
           "    <div>"
           "            <span>Position: " + position + "</span>"
           "    </div>"
           "    <div>"
           "            <span>Phone: " + phone + "</span>"
           "    </div>"
           "    <h2>Experience</h2>";

    for (int i  = 0; i < experiences.size(); i++)
    {
        result += "    <div>"
                  "            <span>From: " + experiences[i].fromDate.toString("yyyy/MM/dd") + "</span>"
                  "    </div>"
                  "    <div>"
                  "            <span>To: " + experiences[i].toDate.toString("yyyy/MM/dd") + "</span>"
                  "    </div>"
                  "    <div>"
                  "            <span>Company: " + experiences[i].companyName + "</span>"
                  "    </div>"
                  "    <div>"
                  "            <span>Position: " + experiences[i].position + "</span>"
                  "    </div>"
                  "    <br>";
    }
    result += "</body>"
              "</html>";
    return result;
}

ResumeProxy::ResumeProxy(IResume *base)
{
    this->base = base;
}

IResume *ResumeProxy::getBase()
{
    return base;
}

void ResumeProxy::setName(QString name)
{
    base->setName(name);
}

void ResumeProxy::setLastName(QString lastName)
{
    base->setLastName(lastName);
}

void ResumeProxy::setSecondnName(QString secondName)
{
    base->setSecondnName(secondName);
}

void ResumeProxy::setPosition(QString position)
{
    base->setPosition(position);
}

void ResumeProxy::setPhone(QString phone)
{
    phone = phone.replace(QRegularExpression("\\s+"), "");
    base->setPhone(phone);
}

QString ResumeProxy::getName()
{
    return base->getName();
}

QString ResumeProxy::getLastName()
{
    return base->getLastName();
}

QString ResumeProxy::getSecondnName()
{
    return base->getSecondnName();
}

QString ResumeProxy::getPosition()
{
    return base->getPosition();
}

QString ResumeProxy::getPhone()
{
    return base->getPhone();
}

void ResumeProxy::addExperience(Experience experience)
{
    if(experience.fromDate < experience.toDate && !experience.companyName.isEmpty() && !experience.position.isEmpty())
    {
        base->addExperience(experience);
    }
}

Experience ResumeProxy::getExperience(int index)
{
    return base->getExperience(index);
}

void ResumeProxy::removeExperience(int index)
{
    base->removeExperience(index);
}

int ResumeProxy::getExperienceCount()
{
    base->getExperienceCount();
}

QString ResumeProxy::toHTML()
{
    if (base->getName().isEmpty())
    {
        return  "<!DOCTYPE html>"
               "<html>"
               "<head>"
               "<meta charset=\"utf-8\">"
               "</head>"
               "<body>"
               "<span style=\"color: red; font-size: 32px;\">Name is empty</span>"
               "</body>"
               "</html>";
    }

    if (base->getLastName().isEmpty())
    {
        return  "<!DOCTYPE html>"
               "<html>"
               "<head>"
               "<meta charset=\"utf-8\">"
               "</head>"
               "<body>"
               "<span style=\"color: red; font-size: 32px;\">Last Name is empty</span>"
               "</body>"
               "</html>";
    }

    if (base->getSecondnName().isEmpty())
    {
        return  "<!DOCTYPE html>"
               "<html>"
               "<head>"
               "<meta charset=\"utf-8\">"
               "</head>"
               "<body>"
               "<span style=\"color: red; font-size: 32px;\">Secondn Name is empty</span>"
               "</body>"
               "</html>";
    }

    if (base->getPosition().isEmpty())
    {
        return  "<!DOCTYPE html>"
               "<html>"
               "<head>"
               "<meta charset=\"utf-8\">"
               "</head>"
               "<body>"
               "<span style=\"color: red; font-size: 32px;\">Position is empty</span>"
               "</body>"
               "</html>";
    }


    QRegularExpression regex("\\d{10}");
    QRegularExpressionMatch match = regex.match(base->getPhone());
    if(!match.hasMatch())
    {
        return  "<!DOCTYPE html>"
               "<html>"
               "<head>"
               "<meta charset=\"utf-8\">"
               "</head>"
               "<body>"
               "<span style=\"color: red; font-size: 32px;\">Wrong number format</span>"
               "</body>"
               "</html>";
    }
    base->setPhone(match.captured(0));

    return base->toHTML();
}
