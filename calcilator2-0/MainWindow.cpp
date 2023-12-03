#include "mainwindow.h"
#include "stylehelper.h"
#include "./ui_MainWindow.h"
#include <QStyleOption>
#include <QDebug>
#include <QStack>
#include <QString>
QString  virojenie;
QString global_key;
double num_first;
bool tochka = true;
bool Label2 = true;
bool FLAG2 = false;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setInterfaceStyle();

    //Соеденение кнопок connect
    //Кнопки
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_00, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    //Точка
    connect(ui->pushButton_tochka, SIGNAL(clicked()), this, SLOT(on_pushButton_dot_cliced()));

    // Процент и +/-
    connect(ui->pushButton_plusminus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_procent, SIGNAL(clicked()), this, SLOT(operations()));

    //Математические операции
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_mnoj, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_delit, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_levskob, SIGNAL(clicked()), this, SLOT(math_operations()));

    //PI and E
    connect(ui->pushButton_PI, SIGNAL(clicked()), this, SLOT(math_PI()));
    connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(math_e()));

    //Удаление
    connect(ui->pushButton_delte, SIGNAL(clicked()), this, SLOT(deleteF()));

    ui->pushButton_C->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

const double pi = acos(-1);
const double e = exp(1);
struct Leksema
{
    QChar type;
    double value;
};

double Gradus (double x)
{
    return x*M_PI/180;
}

double Sin(double x)
{
    return (round(sin(x)*1000000)/1000000);
}

double Cos(double x)
{
    return (round(cos(x)*1000000)/1000000);
}

double ctg(double x)
{
    return Cos(x) / Sin(x);
}

int getProritet(QChar i){
    if (i == '+' || i == '-') { return 1;}
    if(i == '*' || i == '/') { return 2;}
    if(i == '^' || i=='q' || i =='!') {return 3;}
    if(i == 's' || i =='c' || i == 't' || i=='g' || i == 'e' || i == 'l' || i =='o' || i=='m' ) {return 4;}
    else return 0;
}




bool Match(QStack<Leksema> & Stack_n, QStack<Leksema> & Stack_o, Leksema& chis)
{
    double b, a , c;
    a = Stack_n.top().value;
    Stack_n.pop();
    if (Stack_o.top().type == '+')
    {

        b = Stack_n.top().value;
        c = a + b;
        Stack_n.pop();
        chis.type = '0';
        chis.value = c;
        Stack_n.push(chis);
        Stack_o.pop();
        return 1;
    }
    if (Stack_o.top().type == '*')
    {
        b = Stack_n.top().value;
        c = a * b;
        Stack_n.pop();
        chis.type = '0';
        chis.value = c;
        Stack_n.push(chis);
        Stack_o.pop();
        return 1;
    }
    if (Stack_o.top().type == '-')
    {
        b = Stack_n.top().value;
        c = b - a;
        Stack_n.pop();
        chis.type = '0';
        chis.value = c;
        Stack_n.push(chis);
        Stack_o.pop();
        return 1;
    }
    if (Stack_o.top().type == '/')
    {
        b = Stack_n.top().value;
        if (a != 0)
        {
            c = b / a;
            Stack_n.pop();
            chis.type = '0';
            chis.value = c;
            Stack_n.push(chis);
            Stack_o.pop();
            return 1;
        }
        else
        // Нужно разобраться и сделать через try catch отлавить будет ошибку при делении на 0
        { return 0;}
    }
    if (Stack_o.top().type == '^')
    {
        if (FLAG2 == 1)
        {
            b = Stack_n.top().value;
            c = pow(b,a);
            Stack_n.pop();
            chis.type = '0';
            chis.value = - c;
            Stack_n.push(chis);
            Stack_o.pop();
            FLAG2 = 0;
            return 1;
        }
        else{
            b = Stack_n.top().value;
            c = pow(b,a);
            Stack_n.pop();
            chis.type = '0';
            chis.value = c;
            Stack_n.push(chis);
            Stack_o.pop();
            return 1;
        }

    }
    if (Stack_o.top().type == 's')
    {
        if (FLAG2 == 1)
        {
            c = Sin(Gradus(a));
            chis.type = '0';
            chis.value = - c;
            Stack_n.push(chis);
            Stack_o.pop();
            FLAG2 = 0;
            return 1;
        }
        else{
            c = Sin(Gradus(a));
            chis.type = '0';
            chis.value = c;
            Stack_n.push(chis);
            Stack_o.pop();
            return 1;
        }

    }
    if (Stack_o.top().type == 'c')
    {
        if (FLAG2 == 1)
        {
            c = Cos(Gradus(a));;
            chis.type = '0';
            chis.value = -c;
            Stack_n.push(chis);
            Stack_o.pop();
            FLAG2 = 0;
            return 1;
        }
        else{
            c = Cos(Gradus(a));;
            chis.type = '0';
            chis.value = c;
            Stack_n.push(chis);
            Stack_o.pop();
            return 1;
        }

    }
    if (Stack_o.top().type == 't')
    {
        if (Cos(Gradus(a)) == 0)
        {
            qDebug()<<"Тангенс не существует ";
            Stack_o.pop();
            return 0;
        }
        if (FLAG2 == 1)
        {
            c = tan(Gradus(a));
            chis.type = '0';
            chis.value = -c;
            Stack_n.push(chis);
            Stack_o.pop();
            FLAG2 = 0;
            return 1;
        }
        else{
            c = tan(Gradus(a));
            chis.type = '0';
            chis.value = c;
            Stack_n.push(chis);
            Stack_o.pop();
            return 1;
        }

    }
    if (Stack_o.top().type == 'g')
    {
        if (Sin(Gradus(a))==0)
        {
            qDebug()<<"Котангенс не существует ";
            Stack_o.pop();
            return 0;
            //ОШибка вывод на экран
        }
        if (FLAG2 == 1)
        {
            c = ctg(Gradus(a));
            chis.type = '0';
            chis.value = -c;
            Stack_n.push(chis);
            Stack_o.pop();
            FLAG2 = 0;
            return 1;
        }
        else{
            c = ctg(Gradus(a));
            chis.type = '0';
            chis.value = c;
            Stack_n.push(chis);
            Stack_o.pop();
            return 1;
        }

    }
    //Десятичный логорифм log10(a)
    if (Stack_o.top().type == 'l')
    {
        if (FLAG2 == 1)
        {
            c = log10(a);
            chis.type = '0';
            chis.value = - c;
            Stack_n.push(chis);
            Stack_o.pop();
            FLAG2 = 0;
            return 1;
        }
        else{
            c = log10(a);
            chis.type = '0';
            chis.value = c;
            Stack_n.push(chis);
            Stack_o.pop();
            return 1;
        }

    }
    if (Stack_o.top().type == 'q')
    {

        if (FLAG2 == 1)
        {
            c = pow(a,0.5);
            chis.type = '0';
            chis.value = -c;
            Stack_n.push(chis);
            Stack_o.pop();
            FLAG2 = 0;
            return 1;
        }
        else{
            c = pow(a,0.5);
            chis.type = '0';
            chis.value = c;
            Stack_n.push(chis);
            Stack_o.pop();
            return 1;
        }

    }
    if (Stack_o.top().type == 'o')
    {
        if (FLAG2 == 1)
        {
            c = log(a);
            chis.type = '0';
            chis.value = - c;
            Stack_n.push(chis);
            Stack_o.pop();
            FLAG2 =0;
            return 1;
        }
        else{
            c = log(a);
            chis.type = '0';
            chis.value = c;
            Stack_n.push(chis);
            Stack_o.pop();
            return 1;
        }
    }
    if (Stack_o.top().type == 'm')
    {
        if (FLAG2 == 1)
        {
            c = abs(a);
            chis.type = '0';
            chis.value = - c;
            Stack_n.push(chis);
            Stack_o.pop();
            FLAG2 = 0;
            return 1;
        }
        else{
            c = abs(a);
            chis.type = '0';
            chis.value = c;
            Stack_n.push(chis);
            Stack_o.pop();
            return 1;
        }

    }
    if (Stack_o.top().type == '!')
    {

        int count = 1;
        for (int i = 1; i<=a; i++)
        {

            count = count * i;

        }
        if (FLAG2 == 1)
        {
            c = count;
            chis.type = '0';
            chis.value = -c;
            Stack_n.push(chis);
            Stack_o.pop();
            FLAG2 = 0;
            return 1;
        }
        else{
            c = count;
            chis.type = '0';
            chis.value = c;
            Stack_n.push(chis);
            Stack_o.pop();
            return 1;
        }
    }
    return 0;
}


double Magic(QString str)
{
    QStack<Leksema> Stack_n;
    QStack<Leksema> Stack_o;
    Leksema oper;
    Leksema chis;
    int count_operation = 0;
    int count_chisl = 0;
    int count_skob = 0;
    bool FLAG = 0;
    for(int i = 0; i<str.length(); i++) // Считаем количество операций
    {
        // q - корень //g - ctg  //l - Десятичный логорифм // o - ln // m - модуль
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] =='(' || str[i] =='^' || str[i] == 's' || str[i]=='c' || str[i]=='t' || str[i]=='g' || str[i]=='l' || str[i]=='q' || str[i]=='o' || str[i]==
                                                                                                                                                                                                                                             'm' || str[i]=='!' )
            ++count_operation;
    }


    //Проверка на -

    ///////////////////////////////////////////////////////////////////////////////////////
    int i = 0;
    int index_oper = 0;
    bool Prov = 1;
    bool skobka = 1;
    int rar = 0;
    while (count_operation != 0)
    {

        if (str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '^' && str[i]!='s' && str[i]!='c' && str[i]!='t' && str[i] !='g' && str[i]!='l' && str[i]!='q' && str[i]!='o' && str[i]!='m' && str[i]!='!' )        {

            if (str[i] == '(')
            {
                oper.type = str[i];
                oper.value = 0;
                Stack_o.push(oper);
                --count_chisl;
                ++index_oper;
                if( i != 0)
                {
                    if(str[i-1]=='l' || str[i-1] == 's' || str[i-1] == 'c' || str[i-1] == 'c' || str[i-1] == 't' || str[i-1] == 'g' || str[i-1] == 'q' || str[i-1] == 'o' || str[i-1] == 'm' || str[i-1]=='!')
                    {
                        oper.type = '*';
                        oper.value = 0;
                        Stack_o.push(oper);
                        chis.type = '0';
                        chis.value = 1;
                        Stack_n.push(chis);
                    }
                }
            }

            if (str[i] == ')'){
                if (skobka == 1)
                { // Проверка на посленее число скобки
                    if (str.mid(index_oper, count_chisl) == 'P'){
                        chis.type = '0';
                        chis.value = pi;
                        Stack_n.push(chis);
                    }
                    if (str.mid(index_oper, count_chisl) == 'e'){
                        chis.type = '0';
                        chis.value = e;
                        Stack_n.push(chis);
                    }
                    else
                    {
                        if (str[i-1]==')'){}
                        else
                        {

                            chis.type = '0';
                            chis.value = str.mid(index_oper, i-index_oper).toDouble();
                            Stack_n.push(chis);


                        }
                    }
                }
                while (Stack_o.top().type!='(')
                {
                    Match(Stack_n, Stack_o, chis);
                    Prov = 0;
                    count_chisl--;
                }
                Stack_o.pop();
                --count_operation;
            }
            ++count_chisl;
            i++;
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        else
        {
            if (Stack_o.size() == 0){

                if (Prov!=0) { //Проверка нужна т.к после скобки не тянется никакое число за собой
                    // Проверка на число PI
                    if (str.mid(index_oper, count_chisl) == 'P'){
                        if (FLAG == 1)
                        {
                            chis.type = '0';
                            chis.value = -1 * pi;
                            Stack_n.push(chis);
                            FLAG =0;
                        }
                        else
                        {
                            chis.type = '0';
                            chis.value = pi;
                            Stack_n.push(chis);
                        }
                    }
                    if (str.mid(index_oper, count_chisl) == 'e'){
                        if (FLAG == 1)
                        {
                            chis.type = '0';
                            chis.value = -1 * e;
                            Stack_n.push(chis);
                            FLAG = 0;
                        }
                        else
                        {
                            chis.type = '0';
                            chis.value = e;
                            Stack_n.push(chis);
                        }
                    }
                    else
                    {
                        if (str[i] == 'P' || str[i]== 's' || str[i]=='c'|| str[i] == 't' || str[i] == 'g' || str[i]=='l' || str[i]=='q' || str[i]=='o' || str[i]=='m' ||str[i]=='!'){}
                        else
                        {
                            if (i>0)
                            {
                                if (str[i-1] =='P' || str[i-1]=='e'){}
                                else
                                {
                                    if (FLAG == 1)
                                    {
                                        if (str[i+1] != ')') {
                                            FLAG = 0;
                                            chis.type = '0';
                                            chis.value = str.mid(index_oper, count_chisl).toDouble();
                                            Stack_n.push(chis);
                                        }
                                        else
                                        {
                                            chis.type = '0';
                                            chis.value = str.mid(index_oper, count_chisl).toDouble() * -1;
                                            Stack_n.push(chis);
                                            FLAG = 0;
                                        }
                                    }
                                    else
                                    {
                                        chis.type = '0';
                                        chis.value = str.mid(index_oper, count_chisl).toDouble();
                                        Stack_n.push(chis);
                                    }

                                }
                            }
                            else
                            {
                                chis.type = '0';
                                chis.value = str.mid(index_oper, count_chisl).toDouble();
                                Stack_n.push(chis);
                            }
                        }
                    }
                }
                else{ Prov = 1;}

                // Если у меня операция!!!
                if ((str[i]== 's' || str[i]=='c'|| str[i] == 't' || str[i] == 'g' || str[i]=='l' || str[i]=='q' || str[i]=='o' || str[i]=='m' ||str[i]=='!') && (i>0) )
                {
                    if (str[i-1] =='-')
                    {
                        FLAG2 = 1;
                    }
                }
                if ((str[i]=='-') && (str[i+1] == 'c' || str[i+1] == 's' || str[i+1]=='t' || str[i+1]=='g' || str[i+1]=='l' || str[i+1] == 'q' || str[i+1] =='o' || str[i+1]=='m'|| str[i]=='m') ){}
                else{
                    qDebug()<<str[i+1];
                    oper.type = str[i];
                    oper.value = 0;
                    Stack_o.push(oper);
                }

                // Здесь где то должна быть провека на приоритет
                index_oper = i+1;
                ++i;
                --count_operation;
                count_chisl = 0;
                // Обработка последнего числа
                if (count_operation == 0 )
                {
                    chis.type = '0';
                    if (str.mid(index_oper, str.size()-i) == 'e')
                    {
                        chis.type = '0';
                        chis.value = e;
                        Stack_n.push(chis);
                    }
                    else if (str.mid(index_oper, str.size()-i) == 'P')
                    {
                        chis.type = '0';
                        chis.value = pi;
                        Stack_n.push(chis);
                    }
                    else
                    {
                        chis.value = str.mid(index_oper, str.size()-i).toDouble();
                        Stack_n.push(chis);
                    }
                }
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////
            else if (Stack_o.size()!= 0 && getProritet(str[i]) > getProritet(Stack_o.top().type))
            {
                if (Prov!=0) { //Проверка нужна т.к после скобки не тянется никакое число за собой
                    // Проверка на число PI
                    if (str.mid(index_oper, count_chisl) == 'P'){
                        if (FLAG == 1)
                        {
                            chis.type = '0';
                            chis.value = -1 * pi;
                            Stack_n.push(chis);
                            FLAG =0;
                        }
                        else
                        {
                            chis.type = '0';
                            chis.value = pi;
                            Stack_n.push(chis);
                        }
                    }
                    if (str.mid(index_oper, count_chisl) == 'e'){
                        if (FLAG == 1)
                        {
                            chis.type = '0';
                            chis.value = -1 * e;
                            Stack_n.push(chis);
                            FLAG = 0;
                        }
                        else
                        {
                            chis.type = '0';
                            chis.value = e;
                            Stack_n.push(chis);
                        }
                    }
                    else
                    {
                        if (str[i] == 'P' || str[i]== 's' || str[i]=='c'|| str[i] == 't' || str[i] == 'g' || str[i]=='l' || str[i]=='q' || str[i]=='o' || str[i]=='m' ||str[i]=='!'){}
                        else
                        {
                            if (i>0)
                            {
                                if (str[i-1] =='P' || str[i-1]=='e'){}
                                else
                                {
                                    if (FLAG == 1)
                                    {
                                        if (str[i+1] != ')') {
                                            FLAG = 0;
                                            chis.type = '0';
                                            chis.value = str.mid(index_oper, count_chisl).toDouble();
                                            Stack_n.push(chis);
                                        }
                                        else
                                        {
                                            chis.type = '0';
                                            chis.value = str.mid(index_oper, count_chisl).toDouble() * -1;
                                            Stack_n.push(chis);
                                            FLAG = 0;
                                        }
                                    }
                                    else
                                    {
                                        chis.type = '0';
                                        chis.value = str.mid(index_oper, count_chisl).toDouble();
                                        Stack_n.push(chis);
                                    }

                                }
                            }
                            else
                            {
                                chis.type = '0';
                                chis.value = str.mid(index_oper, count_chisl).toDouble();
                                Stack_n.push(chis);
                            }
                        }
                    }
                }
                else{ Prov = 1;}


                // Если у меня операция!!!
                if ((str[i]== 's' || str[i]=='c'|| str[i] == 't' || str[i] == 'g' || str[i]=='l' || str[i]=='q' || str[i]=='o' || str[i]=='m' ||str[i]=='!') && (i>0) )
                {
                    if (str[i-1] =='-')
                    {
                        FLAG2 = 1;
                    }
                }
                if ((str[i]=='-') && (str[i+1] == 'c' || str[i+1] == 's' || str[i+1]=='t' || str[i+1]=='g' || str[i+1]=='l' || str[i+1] == 'q' || str[i+1] =='o' || str[i+1]=='m'|| str[i]=='m') ){}
                else{
                    qDebug()<<str[i+1];
                    oper.type = str[i];
                    oper.value = 0;
                    Stack_o.push(oper);
                }
                // Здесь где то должна быть провека на приоритет
                index_oper = i+1;
                ++i;
                --count_operation;
                count_chisl = 0;
                // Обработка последнего числа
                if (count_operation == 0 )
                {
                    chis.type = '0';
                    if (str.mid(index_oper, str.size()-i) == 'e')
                    {
                        chis.type = '0';
                        chis.value = e;
                        Stack_n.push(chis);
                    }
                    else if (str.mid(index_oper, str.size()-i) == 'P')
                    {
                        chis.type = '0';
                        chis.value = pi;
                        Stack_n.push(chis);
                    }
                    else
                    {
                        chis.value = str.mid(index_oper, str.size()-i).toDouble();
                        Stack_n.push(chis);
                    }
                }
            }
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            else if (Stack_o.size()!= 0 && getProritet(str[i]) <= getProritet(Stack_o.top().type))
            {

                if (Prov!=0) { //Проверка нужна т.к после скобки не тянется никакое число за собой
                    // Проверка на число PI
                    if (str.mid(index_oper, count_chisl) == 'P'){
                        if (FLAG == 1)
                        {
                            chis.type = '0';
                            chis.value = -1 * pi;
                            Stack_n.push(chis);
                            FLAG =0;
                        }
                        else
                        {
                            chis.type = '0';
                            chis.value = pi;
                            Stack_n.push(chis);
                        }
                    }
                    if (str.mid(index_oper, count_chisl) == 'e'){
                        if (FLAG == 1)
                        {
                            chis.type = '0';
                            chis.value = -1 * e;
                            Stack_n.push(chis);
                            FLAG = 0;
                        }
                        else
                        {
                            chis.type = '0';
                            chis.value = e;
                            Stack_n.push(chis);
                        }
                    }
                    else
                    {
                        if (str[i] == 'P' || str[i]== 's' || str[i]=='c'|| str[i] == 't' || str[i] == 'g' || str[i]=='l' || str[i]=='q' || str[i]=='o' || str[i]=='m' ||str[i]=='!'){}
                        else
                        {
                            if (i>0)
                            {
                                if (str[i-1] =='P' || str[i-1]=='e'){}
                                else
                                {
                                    if (FLAG == 1)
                                    {
                                        if (str[i+1] != ')') {
                                            FLAG = 0;
                                            chis.type = '0';
                                            chis.value = str.mid(index_oper, count_chisl).toDouble();
                                            Stack_n.push(chis);
                                        }
                                        else
                                        {
                                            chis.type = '0';
                                            chis.value = str.mid(index_oper, count_chisl).toDouble() * -1;
                                            Stack_n.push(chis);
                                            FLAG = 0;
                                        }
                                    }
                                    else
                                    {
                                        chis.type = '0';
                                        chis.value = str.mid(index_oper, count_chisl).toDouble();
                                        Stack_n.push(chis);
                                    }

                                }
                            }
                            else
                            {
                                chis.type = '0';
                                chis.value = str.mid(index_oper, count_chisl).toDouble();
                                Stack_n.push(chis);
                            }
                        }
                    }
                }
                else{ Prov = 1;}



                if (Match(Stack_n, Stack_o, chis) == false){ qDebug()<<"Ошибка ";}
                //добавление операции после MATCH
                if ((str[i]== 's' || str[i]=='c'|| str[i] == 't' || str[i] == 'g' || str[i]=='l' || str[i]=='q' || str[i]=='o' || str[i]=='m' ||str[i]=='!') && (i>0) )
                {
                    if (str[i-1] =='-')
                    {
                        FLAG2 = 1;
                    }
                }
                if ((str[i]=='-') && (str[i+1] == 'c' || str[i+1] == 's' || str[i+1]=='t' || str[i+1]=='g' || str[i+1]=='l' || str[i+1] == 'q' || str[i+1] =='o' || str[i+1]=='m'|| str[i]=='m') ){}
                else{
                    qDebug()<<str[i+1];
                    oper.type = str[i];
                    oper.value = 0;
                    Stack_o.push(oper);
                }
                index_oper = i+1;
                ++i;
                --count_operation;
                count_chisl = 0;
                if (count_operation == 0 )
                {
                    chis.type = '0';
                    if (str.mid(index_oper, str.size()-i) == 'e')
                    {
                        chis.type = '0';
                        chis.value = e;
                        Stack_n.push(chis);
                    }
                    else if (str.mid(index_oper, str.size()-i) == 'P')
                    {
                        chis.type = '0';
                        chis.value = pi;
                        Stack_n.push(chis);
                    }
                    else
                    {
                        chis.value = str.mid(index_oper, str.size()-i).toDouble();
                        Stack_n.push(chis);
                    }
                }
                continue;
            }
        }


    }
    while (Stack_o.size() != 0){
        if (Match(Stack_n, Stack_o, chis) == false)
        {
            return 0.0000000404;
        }
        else
        {
            continue;
        }
    }
    qDebug()<<Stack_n.top().value;
    return Stack_n.top().value;
}





void MainWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);

}
// Установка стилей копкам
void MainWindow::setInterfaceStyle()
{
    this->setStyleSheet(StyleHelper::getMainWidetStyle());
    ui->pushButton_delit->setStyleSheet(StyleHelper::getStartButtonsStyle());
    ui->pushButton_ravno->setStyleSheet(StyleHelper::getStartButtonsStyle());
    ui->pushButton_minus->setStyleSheet(StyleHelper::getStartButtonsStyle());
    ui->pushButton_mnoj->setStyleSheet(StyleHelper::getStartButtonsStyle());
    ui->pushButton_plus->setStyleSheet(StyleHelper::getStartButtonsStyle());

    ui->pushButton_0->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton1->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton2->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton3->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_4->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_5->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_6->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_7->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_8->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_9->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_00->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_tochka->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_PI->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_e->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_cos->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_deg->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_plusminus->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_levskob->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_ln->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_log10->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_pow->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_modul->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_ctg->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_sin->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_sqr->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_tan->setStyleSheet(StyleHelper::getNumberButton());
    ui->pushButton_voskl->setStyleSheet(StyleHelper::getNumberButton());

    ui->pushButton_delte->setStyleSheet(StyleHelper::getUprav());
    ui->pushButton_procent->setStyleSheet(StyleHelper::getUprav());
    ui->pushButton_C->setStyleSheet(StyleHelper::getUprav());

}



// Кнопки 1234567890
void MainWindow::digits_numbers()
{

    QPushButton *button  = (QPushButton*)sender();

    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    double numbers;
    QString new_label;
    if (ui->label->text() == "0") {
        ui->label->clear();
        new_label = (ui->label->text() + button->text());
        ui->label->setText(new_label);
        ui->label_2->setText(new_label);
        virojenie += button->text();
    }
    else
    {
    new_label = (ui->label->text() + button->text());
    ui->label->setText(new_label);
    ui->label_2->setText(new_label);
    virojenie += button->text();
    }



}


// Функции .
void MainWindow::on_pushButton_dot_cliced()
{
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (tochka == 1)
    {
        ui->label->setText(ui->label->text()+ "." );
        virojenie += ".";
        tochka = false;
    }
}



void MainWindow::operations()
{
    QPushButton *button  = (QPushButton*)sender();
    double numbers;
    QString new_label;
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (button->text() == "+/-")
    {
        numbers = (ui->label->text()).toDouble();
        numbers *=-1;
        new_label = QString::number(numbers, 'g', 15);
        ui->label->setText(new_label);
        ui->label_2->setText(new_label);
        virojenie.prepend("-");
    }
    else if (button->text() == "%")
    {
        numbers = (ui->label->text()).toDouble();
        QString f = ui->label->text();
        ui->label_2->setText("%"+f);
        numbers *= 0.01;
        new_label = QString::number(numbers, 'g', 15);
        ui->label->setText(new_label);
        if (virojenie.contains('+') ||  virojenie.contains('-') || virojenie.contains('*') || virojenie.contains('/'))
        {
            double s  = (Magic(virojenie) *0.01);
            virojenie = QString::number(s, 'g', 15);
        }
        else {
            double s = virojenie.toDouble() * 0.01;
            virojenie = QString::number(s, 'g', 15);

        }

    }
}


// Меняю эту функцию

void MainWindow::math_operations()
{
    QPushButton *button  = (QPushButton*)sender();
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    QString new_label;
    QString proverka = ui->label->text();
    if ((proverka.right(1).at(0) == '+'  || proverka.right(1).at(0) == '*' || proverka.right(1).at(0) == '/') && (proverka.right(1).at(0) != '-')){}
    else if (ui->label->text()=='0'){
        ui->label->clear();
        if (button->text()=='-')
        {
            new_label = (ui->label->text() + button->text());
            ui->label->setText(new_label);
            ui->label_2->setText(new_label);
            tochka = 1;
            virojenie += '-';
        }
        else{}
    }
    else {
        new_label = (ui->label->text() + button->text());
        ui->label->setText(new_label);
        ui->label_2->setText(new_label);
        tochka = 1;
        virojenie += button->text();
    }
}


void MainWindow::math_PI()
{
    QPushButton *button  = (QPushButton*)sender();
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (ui->label->text()=='0')
    {
        ui->label->clear();
        ui->label_2->clear();
        double numbers;
        QString new_label;
        ui->label->setText(ui->label->text()+"π");
        ui->label_2->setText(ui->label_2->text()+"π");
        virojenie += "P";
    }
    else
    {
        double numbers;
        QString new_label;
        ui->label->setText(ui->label->text()+"π");
        ui->label_2->setText(ui->label_2->text()+"π");
        virojenie += "P";
    }

}


void MainWindow::math_e()
{
    QPushButton *button  = (QPushButton*)sender();
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (ui->label->text()=='0')
    {
        ui->label->clear();
        ui->label_2->clear();
        double numbers;
        QString new_label;
        ui->label->setText(ui->label->text()+"e");
        ui->label_2->setText(ui->label_2->text()+"e");
        virojenie += "e";
    }
    else
    {
    double numbers;
    QString new_label;
    ui->label->setText(ui->label->text()+"e");
    ui->label_2->setText(ui->label_2->text()+"e");
    virojenie += "e";
    }
}

void MainWindow::deleteF()
{

    QString string;
    string = ui->label->text();
    string.remove(string.size()-1,1);
    ui->label->setText(string);
    ui->label_2->setText(string);
    virojenie.remove(virojenie.size()-1,1);
}

void MainWindow::on_pushButton_ravno_clicked()
{

    double s = Magic(virojenie);
    qDebug()<<virojenie;
    if (Magic(virojenie) == 0.0000000404) { ui->label->setText("Ошибка!!!");}
    else
    {
        QString str;
        str = QString::number(s, 'g', 15);
        virojenie = QString::number(s, 'g', 15);
        ui->label->setText(str);
        Label2 = false;
    }

}


void MainWindow::on_pushButton_C_clicked()
{
    if (ui->pushButton_C->isChecked())
    {
        ui->label->setText("");
        ui->label_2->setText("");
        virojenie = "";
        ui->pushButton_C->setChecked(false);

    }
}

void MainWindow::on_pushButton_ln_clicked()
{
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (ui->label->text() == '0')
    {
        ui->label->clear();
        ui->label_2->clear();
        ui->label->setText(ui->label->text() + "(");
        ui->label_2->setText(ui->label_2->text() + "(");
        virojenie +="(";
    }
    else
    {
        ui->label->setText(ui->label->text() + "(");
        ui->label_2->setText(ui->label_2->text() + "(");
        virojenie +="(";
    }
    qDebug()<<virojenie;
}


void MainWindow::on_pushButton_log10_clicked()
{

    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (ui->label->text() == '0')
    {
        ui->label->clear();
        ui->label_2->clear();
        ui->label->setText(ui->label->text() + "log10");
        ui->label_2->setText(ui->label_2->text() + "log10");
        virojenie +="l";
    }
    else
    {
        ui->label->setText(ui->label->text() + "log10");
        ui->label_2->setText(ui->label_2->text() + "log10");
        virojenie +="l";
    }
}



void MainWindow::on_pushButton_sqr_clicked()
{
    if (ui->label->text() == '0')
    {
        ui->label->clear();
        ui->label_2->clear();
        ui->label->setText("√" + ui->label->text());
        ui->label_2->setText("√" + ui->label_2->text());
        virojenie +='q';
    }
    else if(ui->label->text().right(1).at(0) == '+' || ui->label->text().right(1).at(0) == '-' || ui->label->text().right(1).at(0) == '*' || ui->label->text().right(1).at(0) == '/')
    {
        ui->label->setText(ui->label->text() + "√");
        ui->label_2->setText(ui->label_2->text() + "√");
        virojenie +='q';
    }
    else
    {
        ui->label->setText("√" + ui->label->text());
        ui->label_2->setText("√" + ui->label_2->text());
        virojenie +='q';
    }
}




void MainWindow::on_pushButton_sin_clicked()
{
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (ui->label->text() == '0')
    {
        ui->label->clear();
        ui->label_2->clear();
        ui->label->setText(ui->label->text() + "sin");
        ui->label_2->setText(ui->label_2->text() + "sin");
        virojenie +="s";
    }
    else
    {
        ui->label->setText(ui->label->text() + "sin");
        ui->label_2->setText(ui->label_2->text() + "sin");
        virojenie +="s";
    }
}


void MainWindow::on_pushButton_cos_clicked()
{
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (ui->label->text() == '0')
    {
        ui->label->clear();
        ui->label_2->clear();
        ui->label->setText(ui->label->text() + "cos");
        ui->label_2->setText(ui->label_2->text() + "cos");
        virojenie +="c";
    }
    else
    {
        ui->label->setText(ui->label->text() + "cos");
        ui->label_2->setText(ui->label_2->text() + "cos");
        virojenie +="c";
    }
}


void MainWindow::on_pushButton_tan_clicked()
{
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (ui->label->text() == '0')
    {
        ui->label->clear();
        ui->label_2->clear();
        ui->label->setText(ui->label->text() + "tan");
        ui->label_2->setText(ui->label_2->text() + "tan");
        virojenie +="t";
    }
    else
    {
        ui->label->setText(ui->label->text() + "tan");
        ui->label_2->setText(ui->label_2->text() + "tan");
        virojenie +="t";
    }
}

void MainWindow::on_pushButton_ctg_clicked()
{
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (ui->label->text() == '0')
    {
        ui->label->clear();
        ui->label_2->clear();
        ui->label->setText(ui->label->text() + "cot");
        ui->label_2->setText(ui->label_2->text() + "cot");
        virojenie +="g";
    }
    else
    {
        ui->label->setText(ui->label->text() + "cot");
        ui->label_2->setText(ui->label_2->text() + "cot");
        virojenie +="g";
    }
}


void MainWindow::on_pushButton_deg_clicked()
{
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (ui->label->text() == '0')
    {
        ui->label->clear();
        ui->label_2->clear();
        ui->label->setText(ui->label->text() + "ln");
        ui->label_2->setText(ui->label_2->text() + "ln");
        virojenie +="o";
    }
    else
    {
        ui->label->setText(ui->label->text() + "ln");
        ui->label_2->setText(ui->label_2->text() + "ln");
        virojenie +="o";
    }
}


void MainWindow::on_pushButton_modul_clicked()
{
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (ui->label->text() == '0')
    {
        ui->label->clear();
        ui->label_2->clear();
        ui->label->setText(ui->label->text() + "abs");
        ui->label_2->setText(ui->label_2->text() + "abs");
        virojenie +="m";
    }
    else
    {
        ui->label->setText(ui->label->text() + "abs");
        ui->label_2->setText(ui->label_2->text() + "abs");
        virojenie +="m";
    }
}

void MainWindow::on_pushButton_voskl_clicked()
{
    if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
    if (ui->label->text() == '0')
    {
        ui->label->clear();
        ui->label_2->clear();
        ui->label->setText(ui->label->text() + "!");
        ui->label_2->setText(ui->label_2->text() + "!");
        virojenie +="!";
    }
    else
    {
        ui->label->setText(ui->label->text() + "!");
        ui->label_2->setText(ui->label_2->text() + "!");
        virojenie +="!";
    }

}



void MainWindow::keyPressEvent(QKeyEvent *e)
{
     QString str = ui->label->text();
    double labelNumber, num_second;
    QString new_label, str2;
    num_second = ui->label->text().toDouble();
    str2 = ui->label->text();
    if(e->key() == Qt::Key_1){
        if (str[0] == '0')
        {
            str.clear();
            ui->label->setText("1");
            ui->label_2->setText("1");
            virojenie +="1";
        }
        else { ui->label->setText(ui->label->text() + "1"); virojenie +="1";  ui->label_2->setText(ui->label_2->text() + "1"); }
    }
    if(e->key() == Qt::Key_2){
        if (str[0] == '0')
        {
            str.clear();
            ui->label->setText("2");
            ui->label_2->setText("2");
            virojenie +="2";
        }
        else { ui->label->setText(ui->label->text() + "2"); virojenie +="2"; ui->label_2->setText(ui->label_2->text() + "2");}
    }
    if(e->key() == Qt::Key_3){
        if (str[0] == '0')
        {
            str.clear();
            ui->label->setText("3");
            ui->label_2->setText("3");
            virojenie +="3";
        }
        else { ui->label->setText(ui->label->text() + "3"); virojenie +="3"; ui->label_2->setText(ui->label_2->text() + "3");}
    }
    if(e->key() == Qt::Key_4){
        if (str[0] == '0')
        {
            str.clear();
            ui->label->setText("4");
            ui->label_2->setText("4");
            virojenie +="4";
        }
        else { ui->label->setText(ui->label->text() + "4"); virojenie +="4"; ui->label_2->setText(ui->label_2->text() + "4");}
    }
    if(e->key() == Qt::Key_5){
        if (str[0] == '0')
        {
            str.clear();
            ui->label->setText("5");
            ui->label_2->setText("5");
            virojenie +="5";
        }
        else {ui->label->setText(ui->label->text() + "5"); virojenie +="5"; ui->label_2->setText(ui->label_2->text() + "5");}
    }
    if(e->key() == Qt::Key_6){
        if (str[0] == '0')
        {
            str.clear();
            ui->label->setText("6");
            ui->label_2->setText("6");
            virojenie +="6";
        }
        else {ui->label->setText(ui->label->text() + "6"); virojenie +="6"; ui->label_2->setText(ui->label_2->text() + "6");}
    }
    if(e->key() == Qt::Key_7){
        if (str[0] == '0')
        {
            str.clear();
            ui->label->setText("7");
            ui->label_2->setText("7");
            virojenie +="7";
        }
        else { ui->label->setText(ui->label->text() + "7"); virojenie +="7"; ui->label_2->setText(ui->label_2->text() + "7");}
    }
    if(e->key() == Qt::Key_8){
        if (str[0] == '0')
        {
            str.clear();
            ui->label->setText("8");
            ui->label_2->setText("8");
            virojenie +="8";
        }
        else { ui->label->setText(ui->label->text() + "8"); virojenie +="8"; ui->label_2->setText(ui->label_2->text() + "8");}
    }
    if(e->key() == Qt::Key_9){
        if (str[0] == '0')
        {
            str.clear();
            ui->label->setText("9");
            ui->label_2->setText("9");
            virojenie +="9";
        }
        else { ui->label->setText(ui->label->text() + "9"); virojenie +="9"; ui->label_2->setText(ui->label_2->text() + "9");}
    }
    if(e->key() == Qt::Key_0){
        if (str[0] == '0')
        {
            str.clear();
            ui->label->setText("0");
            ui->label_2->setText("0");
            virojenie +="0";
        }
        else { ui->label->setText(ui->label->text() + "0"); virojenie +="0"; ui->label_2->setText(ui->label_2->text() + "0");}
    }
    if(e->key() == Qt::Key_Plus){
        ui->label->setText(ui->label->text()+"+");
        ui->label_2->setText(ui->label_2->text()+"+");
        virojenie += "+";
        tochka =true ;
    }
    if(e->key() == Qt::Key_Minus){
        ui->label->setText(ui->label->text()+"-");
        ui->label_2->setText(ui->label_2->text()+"-");
        virojenie += "-";
        tochka =true ;

    }
    if(e->key() == Qt::Key_Asterisk){
        ui->label->setText(ui->label->text()+"*");
        ui->label_2->setText(ui->label_2->text()+"*");
        virojenie += "*";
        tochka =true ;
    }
    if(e->key() == Qt::Key_Slash){
        ui->label->setText(ui->label->text()+"/");
        ui->label_2->setText(ui->label_2->text()+"/");
        virojenie += "/";
        tochka =true ;
    }

    if ((e->key() == Qt::Key_Period) ||(e->key() == Qt::Key_Delete)){
        if (Label2 == false) { ui->label_2->setText(ui->label->text()); Label2 = true; }
        if (tochka == 1)
        {
            ui->label->setText(ui->label->text()+ "." );
            ui->label_2->setText(ui->label_2->text() +".");
            virojenie += ".";
            tochka = false;
        }
    }


    if (e->key() == Qt::Key_Backspace){
        QString string;
        string = ui->label->text();
        string.remove(string.size()-1,1);
        ui->label->setText(string);
        ui->label_2->setText(string);
        virojenie.remove(virojenie.size()-1,1);
    }

    if((e->key() == Qt::Key_Equal ||(e->key() == Qt::Key_Return)))
    {
        double s = Magic(virojenie);
        if (Magic(virojenie) == 0.0000000404) { ui->label->setText("Ошибка!!!");}
        else
        {
            QString str;
            str = QString::number(s, 'g', 15);
            virojenie = QString::number(s, 'g', 15);
            ui->label->setText(str);
            Label2 = false;
        }
    }

    if (e->key() == Qt::Key_ParenLeft){
        ui->label->setText(ui->label->text()+"(");
        ui->label_2->setText(ui->label_2->text()+"(");
        virojenie += "(";
    }
    if (e->key() == Qt::Key_ParenRight){
        ui->label->setText(ui->label->text()+")");
        ui->label_2->setText(ui->label_2->text()+")");
        virojenie += ")";
    }
}













