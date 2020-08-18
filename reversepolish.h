#ifndef REVERSEPOLISH_H
#define REVERSEPOLISH_H
#include <QString>
#include <QVector>

class ReversePolish
{
public:
    ReversePolish(const QString &midExp);
    /**
     * @brief midExpression 获取中缀表达式
     * @return 返回中缀表达式
     */
    QString midExpression() const;
    /**
     * @brief calculateResult 计算表达式的值
     * @return 返回double的值
     */
    double calculateResult();
private:
    /**
     * @brief The ElemType enum 字符串类型
     */
    enum ElemType{
        Enum_Num,
        Enum_Symbol
    };
    /**
     * @brief appendSuffixExp 向后缀表达式追加字符串
     * @param type 字符串类型
     * @param elem 字符串
     */
    void appendSuffixExp(const ElemType &type, const QString elem);
    /**
     * @brief isTypeid 判断是否为操作符
     * @param elem 字符串
     * @return 是否为操作符
     */
    bool isTypeid(const QChar &elem)
    {
        if (elem == '-' || elem == '+' || elem == '*' || elem == '/') {
            return true;
        } else {
            return false;
        }
    }
    /**
     * @brief priority 确认操作符的优先级
     * @param elem 操作符
     * @return 优先级
     */
    int priority(const QChar &elem)
    {
        if (elem == '-' || elem == '+') {
            return 1;
        } else if (elem == '*' || elem == '/') {
            return 2;
        }
        return -1;
    }
    /**
     * @brief midExpToSuffixExp 中缀表达式转后缀表达式
     */
    void midExpToSuffixExp();
private:

    /**
     * @brief The Elem struct 字符串特定对象
     */
    struct Elem{
        /**
         * @brief m_type 字符串类型
         */
        ElemType m_type;
        /**
         * @brief m_value 字符串值
         */
        QString m_value;
        Elem(const ElemType &type, const QString &value)
            : m_type(type),
              m_value(value)
        {

        };
    };

    /**
     * @brief m_midExpression 中缀表达式
     */
    QString m_midExpression;
    /**
     * @brief m_suffixExpression 后缀表达式
     */
    QVector<Elem> m_suffixExpression;
};
#endif // REVERSEPOLISH_H
