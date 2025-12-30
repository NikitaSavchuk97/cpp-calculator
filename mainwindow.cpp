#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализируем UI
    ui->l_result->setText("0");
    ui->l_formula->setText("");
    ui->l_memory->setText("");
    ui->tb_extra->hide();

    // Подключаем сигналы к слотам
    connect(ui->cmb_controller, SIGNAL(currentIndexChanged(int)),
            this, SLOT(on_cmb_controller_currentIndexChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Методы для установки текста
void MainWindow::SetInputText(const std::string& text)
{
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text)
{
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text)
{
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text)
{
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key)
{
    if (key.has_value()) {
        ui->tb_extra->setText(QString::fromStdString(key.value()));
        ui->tb_extra->show();
    } else {
        ui->tb_extra->hide();
    }
}

// Методы для установки callback-функций
void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb)
{
    digit_cb_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb)
{
    operation_cb_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb)
{
    control_cb_ = cb;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb)
{
    controller_cb_ = cb;
}

// Слоты для обработки нажатий кнопок
void MainWindow::on_cmb_controller_currentIndexChanged(int index)
{
    if (controller_cb_) {
        QString text = ui->cmb_controller->currentText();
        ControllerType type;

        if (text == "double") type = ControllerType::DOUBLE;
        else if (text == "float") type = ControllerType::FLOAT;
        else if (text == "uint8_t") type = ControllerType::UINT8_T;
        else if (text == "int") type = ControllerType::INT;
        else if (text == "int64_t") type = ControllerType::INT64_T;
        else if (text == "size_t") type = ControllerType::SIZE_T;
        else if (text == "Rational") type = ControllerType::RATIONAL;

        controller_cb_(type);
    }
}

void MainWindow::on_tb_zero_clicked() { if (digit_cb_) digit_cb_(0); }
void MainWindow::on_tb_one_clicked() { if (digit_cb_) digit_cb_(1); }
void MainWindow::on_tb_two_clicked() { if (digit_cb_) digit_cb_(2); }
void MainWindow::on_tb_three_clicked() { if (digit_cb_) digit_cb_(3); }
void MainWindow::on_tb_four_clicked() { if (digit_cb_) digit_cb_(4); }
void MainWindow::on_tb_five_clicked() { if (digit_cb_) digit_cb_(5); }
void MainWindow::on_tb_six_clicked() { if (digit_cb_) digit_cb_(6); }
void MainWindow::on_tb_seven_clicked() { if (digit_cb_) digit_cb_(7); }
void MainWindow::on_tb_eight_clicked() { if (digit_cb_) digit_cb_(8); }
void MainWindow::on_tb_nine_clicked() { if (digit_cb_) digit_cb_(9); }

void MainWindow::on_tb_add_clicked() { if (operation_cb_) operation_cb_(Operation::ADDITION); ui->l_result->setText(""); }
void MainWindow::on_tb_substract_clicked() { if (operation_cb_) operation_cb_(Operation::SUBTRACTION); ui->l_result->setText(""); }
void MainWindow::on_tb_multiplicate_clicked() { if (operation_cb_) operation_cb_(Operation::MULTIPLICATION); ui->l_result->setText(""); }
void MainWindow::on_tb_divide_clicked() { if (operation_cb_) operation_cb_(Operation::DIVISION); ui->l_result->setText(""); }
void MainWindow::on_tb_power_clicked() { if (operation_cb_) operation_cb_(Operation::POWER); ui->l_result->setText(""); }

void MainWindow::on_tb_equal_clicked() { if (control_cb_) control_cb_(ControlKey::EQUALS); }
void MainWindow::on_tb_reset_clicked() { if (control_cb_) control_cb_(ControlKey::CLEAR); }
void MainWindow::on_tb_negate_clicked() { if (control_cb_) control_cb_(ControlKey::PLUS_MINUS); }
void MainWindow::on_tb_backspace_clicked() { if (control_cb_) control_cb_(ControlKey::BACKSPACE); }
void MainWindow::on_tb_ms_clicked() { if (control_cb_) control_cb_(ControlKey::MEM_SAVE); }
void MainWindow::on_tb_mc_clicked() { if (control_cb_) control_cb_(ControlKey::MEM_CLEAR); }
void MainWindow::on_tn_mr_clicked() { if (control_cb_) control_cb_(ControlKey::MEM_LOAD); }
void MainWindow::on_tb_extra_clicked() { if (control_cb_) control_cb_(ControlKey::EXTRA_KEY); }
