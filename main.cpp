#include <QMainWindow>
#include <QApplication>

#include <QBoxLayout>

#include <QFileDialog>

#include <QWidget>
#include <QVariant>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


class Creator : public QMainWindow {

public:
    // UI
    QWidget *window{};
    QVBoxLayout *mainLayout{};
        QHBoxLayout *NameLayout{};
            QLabel *NameLabel{};
            QLineEdit *NameEdit{};
        QHBoxLayout *IconLayout{};
            QLabel *IconLabel{};
            QLineEdit *IconPathEdit{};
            QPushButton *IconFileDialogButton{};
        QHBoxLayout *ExecLayout{};
            QLabel *ExecLabel{};
            QLineEdit *ExecEdit{};
        QWidget* spacer{};
        QHBoxLayout *SubmitLayout{};
            QPushButton *SubmitButton{};

    // Functions
    void setIconPath() {
        QString path = QFileDialog::getOpenFileName(this,
                                            "Choose Icon",
                                            "/",
                                            "Images (*.png *.xpm *.jpg, *.ico);;"
                                            "Only icons (*.ico);;"
                                            "All files (*.*)");
        IconPathEdit->clear();
        IconPathEdit->setText(path);
    }

    void ConfirmCreation(){

    }

    explicit Creator(QWidget *parent = nullptr) : QMainWindow(parent){
        this->setObjectName(QString::fromUtf8("Desktop Link Creator"));
        setupUi(this);
    }

    void setupUi(QMainWindow *MainWindow){
        window = new QWidget(MainWindow);
        mainLayout = new QVBoxLayout();
        window->setLayout(mainLayout);

        NameLayout = new QHBoxLayout();
        NameLabel = new QLabel("Name:");
        NameLayout-> addWidget(NameLabel);
        NameEdit = new QLineEdit();
        NameLayout-> addWidget(NameEdit);

        mainLayout-> addLayout(NameLayout);

        IconLayout = new QHBoxLayout();
        IconLabel = new QLabel("Icon:");
        IconLayout-> addWidget(IconLabel);
        IconPathEdit = new QLineEdit();
        IconLayout-> addWidget(IconPathEdit);
        IconFileDialogButton = new QPushButton("choose...");
        IconLayout->addWidget(IconFileDialogButton);

        mainLayout-> addLayout(IconLayout);

        ExecLayout = new QHBoxLayout();
        ExecLabel = new QLabel("Executable:");
        ExecLayout-> addWidget(ExecLabel);
        ExecEdit = new QLineEdit();
        ExecLayout-> addWidget(ExecEdit);

        mainLayout-> addLayout(ExecLayout);

        spacer = new QWidget();
        spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        mainLayout-> addWidget(spacer);

        SubmitLayout = new QHBoxLayout();
        SubmitButton = new QPushButton("Create");
        SubmitLayout-> setAlignment(Qt::AlignRight);
        SubmitLayout-> addWidget(SubmitButton);

        mainLayout-> addLayout(SubmitLayout);

        setCentralWidget(window);

        setupSignals();
    }

    void setupSignals() const {
        QObject::connect(IconFileDialogButton, &QPushButton::clicked, this, &Creator::setIconPath);
        QObject::connect(SubmitButton, &QPushButton::clicked, this, &Creator::ConfirmCreation);
    }

};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Creator creator;
    creator.show();
    return QApplication::exec();
}




