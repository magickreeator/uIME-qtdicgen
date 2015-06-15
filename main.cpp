#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString en = "qwertyuiop[]asdfghjkl;'zxcvbnm,./`1234567890-= !@#$%^&*()_+!\"№;%:?*()_+~QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>?\\|";
    QString ru = "йцукенгшщзхъфывапролджэячсмитьбю.ё1234567890-= !@#$%^&*()_+!\"№;%:?*()_+ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ,\\|";

    QFile source("C:/Users/roman/Documents/build-qtdicgen-Desktop_Qt_5_4_1_MinGW_32bit-Release/release/source.txt");
    if (!source.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    QFile Dictionary("C:/Users/roman/Documents/build-qtdicgen-Desktop_Qt_5_4_1_MinGW_32bit-Release/release/Dictionary.txt");
    if (!Dictionary.open(QIODevice::WriteOnly | QIODevice::Text))
        return 2;

    QString fline = "";
    QString sline;

    QTextStream in(&source);
    QTextStream out(&Dictionary);

    while (!in.atEnd()) {
        sline = in.readLine();

        QString ucfline = fline.toUpper();
        QString ucsline = sline.toUpper();

        if (fline != "" && ucfline != ucsline)
        {
            QString scfline = fline;
            scfline[0] = scfline[0].toUpper();

            for (int i = 0; i < ucfline.length(); i++)
            {
                ucfline.replace(i, 1, en[ru.indexOf(ucfline[i])]);
            }

            out << '\"' << ucfline << '\"' << '=' << '\"' << fline << '\"' << endl;
            out << '\"' << ucfline << '\"' << '=' << '\"' << scfline << '\"' << endl;
        }
        fline = sline;
    }

    source.close();
    Dictionary.close();

    return a.exec();
}
