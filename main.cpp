#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString en = "qwertyuiop[]asdfghjkl;'zxcvbnm,./`1234567890-= !@#$%^&*()_+!\"№;%:?*()_+~QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>?\\|";
    QString ru = "йцукенгшщзхъфывапролджэячсмитьбю.ё1234567890-= !@#$%^&*()_+!\"№;%:?*()_+ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ,\\|";

    QFile source("./source.txt");
    if (!source.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    QFile Dictionary("./Dictionary.txt");
    if (!Dictionary.open(QIODevice::WriteOnly | QIODevice::Text))
        return 2;

    QString fline = "";
    QString sline;

    QTextStream in(&source);
    QTextStream out(&Dictionary);

    while (!in.atEnd()) {
        sline = in.readLine();

        QString lcfline = fline.toLower();
        QString lcsline = sline.toLower();

        if (fline != "" && lcfline != lcsline)
        {
            QString scfline = fline;
            scfline[0] = scfline[0].toUpper();

            for (int i = 0; i < lcfline.length(); i++)
            {
                lcfline.replace(i, 1, en[ru.indexOf(lcfline[i])]);
            }

            out << '\"' << lcfline << '\"' << '=' << '\"' << fline << '\"' << endl;
            out << '\"' << lcfline << '\"' << '=' << '\"' << scfline << '\"' << endl;
        }
        fline = sline;
    }

    source.close();
    Dictionary.close();

    return a.exec();
}
