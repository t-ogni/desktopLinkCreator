#include <QMainWindow>
#include <QApplication>

#include <QBoxLayout>

#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include<QMessageBox>

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


class Creator : public QMainWindow {

public:
    explicit Creator(QWidget *parent = nullptr) : QMainWindow(parent){
        this->setObjectName(QString::fromUtf8("Desktop Link Creator"));
        setupUi(this);
    }
private:
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

private slots:
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
        if(NameEdit->text().isEmpty()){
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Warning");
            msgBox.setText("Name is required");
            msgBox.exec();
            return;
        }

        QString filename = QDir::homePath() + "/.local/share/applications/" + NameEdit->text() + ".desktop";
        QFile file(filename);
        if (file.exists()) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Warning");
            msgBox.setText("desktop with that name already exists");
            msgBox.setInformativeText("What i must do with that file?");
            msgBox.addButton("Overwrite", QMessageBox::AcceptRole);
            msgBox.addButton("Discard", QMessageBox::RejectRole);
            if(msgBox.exec() != QMessageBox::AcceptRole)
                return;
        }
        QString filedata = QString("[Desktop Entry]\n"
                           "Categories=optional\n"
                           "Comment=optional\n"
                           "Exec='%1'\n"
                           "Icon=%2\n"
                           "Name=%3\n"
                           "Terminal=false\n"
                           "Type=Application\n").arg(ExecEdit->text()).arg(IconPathEdit->text()).arg(NameEdit->text());

        QMessageBox msgBox;
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << filedata << Qt::endl;
            msgBox.setIcon(QMessageBox::Icon::NoIcon);
            msgBox.setWindowTitle("Created");
            msgBox.setText("desktop entry was created!");
        } else {
            msgBox.setIcon(QMessageBox::Icon::Critical);
            msgBox.setWindowTitle("Failed");
            msgBox.setText("file failed to create!");
        }
        file.close();
        msgBox.exec();
    }

public:
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




