#include "reversepolish.h"
#include <QDebug>

ReversePolish::ReversePolish(const QString &midExp)
    : m_midExpression(midExp),m_suffixExpression()
{
    m_midExpression.remove(QRegExp("\\s*"));
}

QString ReversePolish::midExpression() const
{
    return m_midExpression;
}

double ReversePolish::calculateResult()
{
    if(m_suffixExpression.isEmpty()) {
        midExpToSuffixExp();
    }
    QVector<QVariant> temp;
    int len = m_suffixExpression.size();
    for (int i = 0; i < len; ++i) {
        Elem cur = m_suffixExpression[i];
        if (cur.m_type == Enum_Num) {
            qDebug() << __LINE__ << cur.m_value.toDouble();
            temp.push_back(cur.m_value.toDouble());
        } else if (cur.m_type == Enum_Symbol) {
            double data1 = temp.last().toDouble();
            temp.pop_back();
            double data2 = temp.last().toDouble();
            temp.pop_back();
            double result = 0.0;
            if (cur.m_value == '+') {
                result = data2 + data1;
            } else if (cur.m_value == '-') {
                result = data2 - data1;
            } else if (cur.m_value == '*') {
                result = data2 * data1;
            } else if (cur.m_value == '/') {
                result = data2 / data1;
            } else {
                qDebug() << "unknow symbol!";
                return 0;
            }
            qDebug() << __LINE__ << result;
            temp.push_back(result);
        }
    }
    return temp.last().toDouble();
}

void ReversePolish::midExpToSuffixExp()
{
    QVector<QChar> tempVec;
    int len = m_midExpression.size(); // 中缀表达式字符串长度
    int valueIndex = -1;
    for (int i = 0; i < len; ++i) {
        if ((m_midExpression[i] >= '0' && m_midExpression[i] <= '9')
                || m_midExpression[i] == '.') {
            if (valueIndex == -1) {
                valueIndex = i; // 获取数值的第一个字符下标
            }

        } else {
            if (valueIndex >= 0) { // 根据数值的第一个字符下标和遍历到第一个不是数值的下标，记录数值
                appendSuffixExp(Enum_Num, m_midExpression.mid(valueIndex, i - valueIndex));
                valueIndex = -1; // 重新遍历下一个数值的下标，初始化下标
            }
            if (m_midExpression[i] == '(') {
                tempVec.push_back(m_midExpression[i]);
            } else if (m_midExpression[i] == ')') {
                while (tempVec.last() != '(') {
                    appendSuffixExp(Enum_Symbol, tempVec.last());
                    tempVec.pop_back();
                }
                tempVec.pop_back();
            } else if (isTypeid(m_midExpression[i])) {
                if (tempVec.isEmpty() || priority(m_midExpression[i]) > priority(tempVec.last())) {
                      tempVec.push_back(m_midExpression[i]);
                } else {
                    while ((!tempVec.isEmpty()) && priority(m_midExpression[i]) <= priority(tempVec.last())) {
                        appendSuffixExp(Enum_Symbol, tempVec.last());
                        tempVec.pop_back();
                    }
                    tempVec.push_back(m_midExpression[i]);
                }
            } else {
                qDebug() << "input error!";
                m_suffixExpression.clear();
                return;
            }
        }
    }
    if (valueIndex >= 0) { // 根据数值的第一个字符下标和遍历到第一个不是数值的下标，记录数值
        appendSuffixExp(Enum_Num, m_midExpression.mid(valueIndex, len - valueIndex));
        valueIndex = -1; // 重新遍历下一个数值的下标，初始化下标
    }
    while (!tempVec.isEmpty()) {
        appendSuffixExp(Enum_Symbol, tempVec.last());
        tempVec.pop_back();
    }
    QString temp;
    for (int j = 0; j < m_suffixExpression.size(); ++j) {
        temp += m_suffixExpression[j].m_value;
        temp += " ";
    }
    qDebug() << temp;
}

void ReversePolish::appendSuffixExp(const ElemType &type,const QString elem)
{
    m_suffixExpression.append(Elem(type, elem));
}
