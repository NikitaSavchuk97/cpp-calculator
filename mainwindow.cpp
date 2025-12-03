#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QDebug>

// ==================== КОНСТРУКТОР И ДЕСТРУКТОР ====================
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Устанавливаем начальные значения
    SetText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}

MainWindow::~MainWindow() {
    delete ui;
}

// ==================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ====================
QString MainWindow::OpToString(Operation op) {
    switch(op) {
    case Operation::NO_OPERATION: return "";
    case Operation::ADDITION: return "+";
    case Operation::DIVISION: return "÷";
    case Operation::MULTIPLICATION: return "×";
    case Operation::SUBTRACTION: return "−";
    case Operation::POWER: return "^";
    }
    return "";
}

QString MainWindow::RemoveTrailingZeroes(const QString& text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString& text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

// ==================== ОСНОВНЫЕ ФУНКЦИИ РАБОТЫ С ЧИСЛАМИ ====================
void MainWindow::SetText(const QString& text) {
    QString normalized = NormalizeNumber(text);
    input_number_ = normalized;
    ui->l_result->setText(normalized);
    active_number_ = input_number_.toDouble();
}

void MainWindow::AddText(const QString& suffix) {
    QString new_text = input_number_ + suffix;
    SetText(new_text);
}

void MainWindow::SetOperation(Operation op) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }

    current_operation_ = op;

    // Обновляем формулу
    QString formula_text = QString("%1 %2").arg(
        QString::number(calculator_.GetNumber()),
        OpToString(op)
        );
    ui->l_formula->setText(formula_text);

    // Сбрасываем ввод для нового числа
    input_number_ = "";
}

// ==================== СЛОТЫ ДЛЯ ЦИФРОВЫХ КНОПОК ====================
void MainWindow::on_tb_zero_clicked()
{
    AddText("0");
}

void MainWindow::on_tb_one_clicked()
{
    AddText("1");
}

void MainWindow::on_tb_two_clicked()
{
    AddText("2");
}

void MainWindow::on_tb_three_clicked()
{
    AddText("3");
}

void MainWindow::on_tb_four_clicked()
{
    AddText("4");
}

void MainWindow::on_tb_five_clicked()
{
    AddText("5");
}

void MainWindow::on_tb_six_clicked()
{
    AddText("6");
}

void MainWindow::on_tb_seven_clicked()
{
    AddText("7");
}

void MainWindow::on_tb_eight_clicked()
{
    AddText("8");
}

void MainWindow::on_tb_nine_clicked()
{
    AddText("9");
}

// ==================== СЛОТЫ ДЛЯ ОПЕРАЦИЙ ====================
void MainWindow::on_tb_add_clicked()
{
    SetOperation(Operation::ADDITION);
    ui->l_result->setText("");
}

void MainWindow::on_tb_substract_clicked()
{
    SetOperation(Operation::SUBTRACTION);
    ui->l_result->setText("");
}

void MainWindow::on_tb_multiplicate_clicked()
{
    SetOperation(Operation::MULTIPLICATION);
    ui->l_result->setText("");
}

void MainWindow::on_tb_divide_clicked()
{
    SetOperation(Operation::DIVISION);
    ui->l_result->setText("");
}

void MainWindow::on_tb_power_clicked()
{
    SetOperation(Operation::POWER);
    ui->l_result->setText("");
}

void MainWindow::on_tb_equal_clicked()
{
    if (current_operation_ == Operation::NO_OPERATION) {
        return;
    }

    // Обновляем формулу
    QString formula_text = QString("%1 %2 %3 =").arg(
        QString::number(calculator_.GetNumber()),
        OpToString(current_operation_),
        QString::number(active_number_)
        );
    ui->l_formula->setText(formula_text);

    // Выполняем операцию
    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(active_number_);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(active_number_);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(active_number_);
        break;
    case Operation::DIVISION:
        calculator_.Div(active_number_);
        break;
    case Operation::POWER:
        calculator_.Pow(active_number_);
        break;
    case Operation::NO_OPERATION:
        break;
    }

    // Обновляем результат
    active_number_ = calculator_.GetNumber();
    ui->l_result->setText(QString::number(active_number_));
    input_number_ = "";
    current_operation_ = Operation::NO_OPERATION;
}

// ==================== СЛОТЫ ДЛЯ СПЕЦИАЛЬНЫХ КНОПОК ====================
void MainWindow::on_tb_comma_clicked()
{
    if (!input_number_.contains('.')) {
        AddText(".");
    }
}

void MainWindow::on_tb_negate_clicked()
{
    if (input_number_.startsWith("-")) {
        SetText(input_number_.mid(1));
    } else {
        SetText("-" + input_number_);
    }
}

void MainWindow::on_tb_backspace_clicked()
{
    if (!input_number_.isEmpty()) {
        input_number_.chop(1);
        SetText(input_number_);
    }
}

// ==================== СЛОТЫ ДЛЯ ПАМЯТИ ====================
void MainWindow::on_tb_ms_clicked()
{
    memory_value_ = active_number_;
    has_memory_ = true;
    ui->l_memory->setText("M");
}

void MainWindow::on_tb_mc_clicked()
{
    memory_value_ = 0.0;
    has_memory_ = false;
    ui->l_memory->setText("");
}

void MainWindow::on_tn_mr_clicked()
{
    if (has_memory_) {
        active_number_ = memory_value_;
        ui->l_result->setText(QString::number(active_number_));
        input_number_ = "";
    }
}

// ==================== СЛОТ ДЛЯ ОЧИСТКИ ====================
void MainWindow::on_tb_reset_clicked()
{
    current_operation_ = Operation::NO_OPERATION;
    ui->l_formula->setText("");
    SetText("0");
}
